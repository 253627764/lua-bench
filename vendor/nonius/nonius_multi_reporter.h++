#pragma once

#include <nonius.h++>
#include <tuple>
#include <utility>
#include <type_traits>

namespace nonius {

	namespace nonius_detail {
		using swallow = int[];

		template <std::size_t... I, typename F, typename T>
		decltype(auto) apply(std::index_sequence<I...>, F&& fx, T&& over) {
			return fx(std::get<I>(over)...);
		}

		template <typename F, typename T>
		decltype(auto) apply(F&& fx, T&& over) {
			using Tu = std::decay_t<T>;
			return apply(std::make_index_sequence<std::tuple_size<Tu>::value>(), std::forward<F>(fx), std::forward<T>(over));
		}

		template <std::size_t... I, typename F, typename T>
		decltype(auto) apply_each(std::index_sequence<I...>, F&& fx, T&& over) {
			void(swallow{ 0, (fx(std::get<I>(over)), 0)... });
		}

		template <typename F, typename T>
		void apply_each(F&& fx, T&& over) {
			using Tu = std::decay_t<T>;
			return apply_each(std::make_index_sequence<std::tuple_size<Tu>::value>(), std::forward<F>(fx), std::forward<T>(over));
		}
	}

	template <typename... Reporters>
	struct multi_reporter : reporter {
		std::tuple<Reporters...> reporters;

		template <typename... Tn>
		multi_reporter(Tn&&... argn) : reporters(std::forward<Tn>(argn)...) {}

		virtual std::string description() {
			std::string str;
			nonius_detail::apply_each([&]( auto& reporter ) {
				str += reporter.description();
			}, reporters);
			return "multi reporter: " + str;
		};

		virtual void configure(configuration& cfg) override {
			do_configure(cfg);
		}

	private:
		virtual void do_configure(configuration& cfg) override {
			// TODO: this is kind of silly.
			// We should replace extensions where possible,
			// but that would require the reporter to know more about itself
			// asides from the description
			nonius_detail::apply_each([&](auto& reporter) {
				configuration independentcfg = cfg;
				if (!independentcfg.output_file.empty()) {
					if (std::is_same<std::decay_t<decltype(reporter)>, csv_reporter>::value) {
						independentcfg.output_file.append(".csv");
					}
					else if (std::is_same<std::decay_t<decltype(reporter)>, html_reporter>::value) {
						independentcfg.output_file.append(".html");
					}
					else if (std::is_same<std::decay_t<decltype(reporter)>, junit_reporter>::value) {
						independentcfg.output_file.append(".junit");
					}
					else if (std::is_same<std::decay_t<decltype(reporter)>, standard_reporter>::value) {
						independentcfg.output_file.append(".txt");
					}
				}
				reporter.configure(independentcfg);
			}, reporters);
		}

		virtual void do_warmup_start() override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.warmup_start();
			}, reporters);
		}
		virtual void do_warmup_end(int iterations) override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.warmup_end(iterations);
			}, reporters);
		}

		virtual void do_estimate_clock_resolution_start() override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.estimate_clock_resolution_start();
			}, reporters);
		}
		virtual void do_estimate_clock_resolution_complete(environment_estimate<fp_seconds> estimate) override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.estimate_clock_resolution_complete(estimate);
			}, reporters);
		}

		virtual void do_estimate_clock_cost_start() override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.estimate_clock_cost_start();
			}, reporters);
		}
		virtual void do_estimate_clock_cost_complete(environment_estimate<fp_seconds> estimate) override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.estimate_clock_cost_complete(estimate);
			}, reporters);
		}

		virtual void do_suite_start() override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.suite_start();
			}, reporters);
		}
		virtual void do_benchmark_start(std::string const& name) override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.benchmark_start(name);
			}, reporters);
		}

		virtual void do_measurement_start(execution_plan<fp_seconds> plan) override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.measurement_start(plan);
			}, reporters);
		}
		virtual void do_measurement_complete(std::vector<fp_seconds> const& samples) override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.measurement_complete(samples);
			}, reporters);
		}

		virtual void do_analysis_start() override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.analysis_start();
			}, reporters);
		} // TODO make generic?
		virtual void do_analysis_complete(sample_analysis<fp_seconds> const& analysis) override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.analysis_complete(analysis);
			}, reporters);
		}

		virtual void do_benchmark_failure(std::exception_ptr error) override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.benchmark_failure(error);
			}, reporters);
		}
		virtual void do_benchmark_complete() override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.benchmark_complete();
			}, reporters);
		}
		virtual void do_suite_complete() override {
			nonius_detail::apply_each([&](auto& reporter) {
				reporter.suite_complete();
			}, reporters);
		}

	};

	template <typename... Reporters>
	multi_reporter<std::decay_t<Reporters>...> multi_report( Reporters&&... reporters ) {
		return multi_reporter<std::decay_t<Reporters>...>(std::forward<Reporters>(reporters)...);
	}
}
