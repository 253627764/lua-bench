#define NONIUS_RUNNER
#include <nonius.h++>

#include "string_generation.hpp"
#include "ordered.hpp"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <iostream>

template <typename Fx>
struct pair_first : Fx {
	using Fx::Fx;

	template <typename A, typename B>
	decltype(auto) operator()(A&& a, B&& b) const {
		return static_cast<const Fx&>(*this)(a.first, b.first);
	}
};

NONIUS_PARAM(size, 15000u)

NONIUS_BENCHMARK("std::find_if, vector", [](nonius::chronometer meter) {
	auto n = meter.param<size>();
	std::vector<std::pair<std::string, std::size_t>> storage(generated_strings.cbegin(), std::next(generated_strings.cbegin(), n));
	const std::pair<std::string, std::size_t>& target = generated_strings[n - 1];
	volatile std::size_t s = 0;
	meter.measure([&]() {
		auto it = std::find_if(storage.cbegin(), storage.cend(), [&](const auto& val) { return val.first == target.first; });
		s += it->second;
		return s;
	});
	std::cout << s << std::endl;
})

NONIUS_BENCHMARK("std::find_if, list", [](nonius::chronometer meter) {
	auto n = meter.param<size>();
	std::list<std::pair<std::string, std::size_t>> storage(generated_strings.cbegin(), std::next(generated_strings.cbegin(), n));
	const std::pair<std::string, std::size_t>& target = generated_strings[n - 1];
	volatile std::size_t s = 0;
	meter.measure([&]() {
		auto it = std::find_if(storage.cbegin(), storage.cend(), [&](const auto& val) { return val.first == target.first; });
		s += it->second;
		return s;
	});
	std::cout << s << std::endl;
})

NONIUS_BENCHMARK("ordered.find, ordered<vector>", [](nonius::chronometer meter) {
	auto n = meter.param<size>();
	ordered_container<std::vector<std::pair<std::string, std::size_t>>, pair_first<std::less<>>, pair_first<std::equal_to<>>> storage(generated_strings.cbegin(), std::next(generated_strings.cbegin(), n));
	const std::pair<std::string, std::size_t>& target = generated_strings[n - 1];
	volatile std::size_t s = 0;
	meter.measure([&]() {
		auto it = storage.find(target);
		s += it->second;
		return s;
	});
	std::cout << s << std::endl;
})

NONIUS_BENCHMARK("ordered.find, ordered<list>", [](nonius::chronometer meter) {
	auto n = meter.param<size>();
	ordered_container<std::list<std::pair<std::string, std::size_t>>, pair_first<std::less<>>, pair_first<std::equal_to<>>> storage(generated_strings.cbegin(), std::next(generated_strings.cbegin(), n));
	const std::pair<std::string, std::size_t>& target = generated_strings[n - 1];
	volatile std::size_t s = 0;
	meter.measure([&]() {
		auto it = storage.find(target);
		s += it->second;
		return s;
	});
	std::cout << s << std::endl;
})

NONIUS_BENCHMARK("map.find, map", [](nonius::chronometer meter) {
	auto n = meter.param<size>();
	std::map<std::string, std::size_t, std::less<>> storage(generated_strings.cbegin(), std::next(generated_strings.cbegin(), n));
	const std::pair<std::string, std::size_t>& target = generated_strings[n - 1];
	volatile std::size_t s = 0;
	meter.measure([&]() {
		auto it = storage.find(target.first);
		s += it->second;
		return s;
	});
	std::cout << s << std::endl;
})

NONIUS_BENCHMARK("unordered_map.find, unordered_map", [](nonius::chronometer meter) {
	auto n = meter.param<size>();
	std::unordered_map<std::string, std::size_t> storage(generated_strings.cbegin(), std::next(generated_strings.cbegin(), n));
	const std::pair<std::string, std::size_t>& target = generated_strings[n - 1];
	volatile std::size_t s = 0;
	meter.measure([&]() {
		auto it = storage.find(target.first);
		s += it->second;
		return s;
	});
	std::cout << s << std::endl;
})
