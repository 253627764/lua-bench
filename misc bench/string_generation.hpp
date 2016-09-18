#pragma once

#include <random>
#include <string>
#include <vector>
#include <unordered_map>

std::default_random_engine& benchmark_rng_engine() {
	static std::default_random_engine rng(std::random_device{}());
	return rng;
}

std::string random_string(std::size_t length, std::function<char(void)> rand_char) {
	std::string str(length, 0);
	std::generate_n(str.begin(), length, rand_char);
	return str;
}

template <typename OutIt>
void generate_random_strings(std::size_t n, OutIt it)
{
	static const std::vector<char> ch_set = {
		'0','1','2','3','4',
		'5','6','7','8','9',
		'A','B','C','D','E','F',
		'G','H','I','J','K',
		'L','M','N','O','P',
		'Q','R','S','T','U',
		'V','W','X','Y','Z',
		'a','b','c','d','e','f',
		'g','h','i','j','k',
		'l','m','n','o','p',
		'q','r','s','t','u',
		'v','w','x','y','z',
		'_'
	};
	std::uniform_int_distribution<std::size_t> dist(0, ch_set.size() - 1);
	std::uniform_int_distribution<std::size_t> lengthdist(4, 10);
	auto genchar = [&dist]() { return ch_set[dist(benchmark_rng_engine())]; };
	for (std::size_t i = 0; i < n; ++i) {
		auto len = lengthdist(benchmark_rng_engine());
		*it = std::pair<std::string, std::size_t>(random_string(len, genchar), i);
		++it;
	}
}

std::vector<std::pair<std::string, std::size_t>> generate_strings(std::size_t n) {
	std::vector<std::pair<std::string, std::size_t>> storage;
	storage.reserve(n);
	generate_random_strings(n, std::back_inserter(storage));
	storage.shrink_to_fit();
	return storage;
}

const std::pair<std::string, std::size_t>& target_string(std::size_t n, const std::vector<std::pair<std::string, std::size_t>>& strings) {
	static std::unordered_map<std::size_t, std::size_t> targets;

	auto it = targets.find(n);
	if (it != targets.cend()) {
		return strings[it->second];
	}
	std::uniform_int_distribution<std::size_t> dist(0, n);
	std::size_t targetindex = dist(benchmark_rng_engine());
	targets.insert(it, { n, targetindex });
	const std::pair<std::string, std::size_t>& target = strings[targetindex];
	return target;
}

const std::vector<std::pair<std::string, std::size_t>> generated_strings = generate_strings(50000);

