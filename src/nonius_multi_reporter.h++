#pragma once

#include <nonius.h++>

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
			
			return apply(std::make_index_sequence<std::tuple_size<Tu>(), std::forward<F>(fx), std::forward<T>(over));
		}
	}

	template <typename... Reporters>
	struct multi_reporter : reporter {
		std::tuple<Reporters...> reporters;

		template <typename... Tn>
		multi_repoter(Tn&&... argn) : reporters(std::forward<Tn>(argn)...) {}

		virtual std::string description() {
			std::string str;
			nonius_detail::apply([&]( auto& reporter ) {
				str += reporter.description();
			}, reporters);
			return "multi reporter: " + str;
		};

	private:
		virtual void do_configure(configuration& cfg) override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_configure(cfg);
			}, reporters);
		}

		virtual void do_warmup_start() override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_warmup_start();
			}, reporters);
		}
		virtual void do_warmup_end(int iterations) override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_warmup_end(iterations);
			}, reporters);
		}

		virtual void do_estimate_clock_resolution_start() override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_estimate_clock_resolution_start();
			}, reporters);
		}
		virtual void do_estimate_clock_resolution_complete(environment_estimate<fp_seconds> estimate) override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_estimate_clock_resolution_complete(estimate);
			}, reporters);
		}

		virtual void do_estimate_clock_cost_start() override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_estimate_clock_cost_start();
			}, reporters);
		}
		virtual void do_estimate_clock_cost_complete(environment_estimate<fp_seconds> estimate) override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_estimate_clock_cost_complete(estimate);
			}, reporters);
		}

		virtual void do_suite_start() override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_suite_start();
			}, reporters);
		}
		virtual void do_benchmark_start(std::string const& name) override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_benchmark_start(name);
			}, reporters);
		}

		virtual void do_measurement_start(execution_plan<fp_seconds> plan) override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_measurement_start(plan);
			}, reporters);
		}
		virtual void do_measurement_complete(std::vector<fp_seconds> const& samples) override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_measurement_complete(samples);
			}, reporters);
		}

		virtual void do_analysis_start() override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_analysis_start();
			}, reporters);
		} // TODO make generic?
		virtual void do_analysis_complete(sample_analysis<fp_seconds> const& analysis) override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_analysis_complete(analysis);
			}, reporters);
		}

		virtual void do_benchmark_failure(std::exception_ptr error) override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_benchmark_failure(error);
			}, reporters);
		}
		virtual void do_benchmark_complete() override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_benchmark_complete();
			}, reporters);
		}
		virtual void do_suite_complete() override {
			nonius_detail::apply([&](auto& reporter) {
				reporter.do_suite_complete();
			}, reporters);
		}

	};

	template <typename... Reporters>
	multi_reporter<std::decay_t<Reporters>...> multi_report( Reporters&&... reporters ) {
		return multi_reporter<std::decay_t<Reporters>...>(std::forward<Reporters>(reporters)...);
	}
}
