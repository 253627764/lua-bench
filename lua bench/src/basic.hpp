#pragma once

#include <tuple>
#include <string>

struct basic {
	int var;

	basic() : var() {

	}

	int get() const {
		return var;
	}

	void set(int x) {
		var = x;
	}

	std::tuple<int, std::string> multi_return(int a, std::string b) {
		return{ a, b };
	}
};

inline int basic_call(int x) {
	return x;
}

inline std::string basic_multi_param(std::string a, bool x) {
	if (x) {
		return a;
	}
	return a + " (not true)";
}

inline std::tuple<std::string, std::string> basic_multi_return(std::string a) {
	return { a, " (not true)" };
}
