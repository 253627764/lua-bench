#pragma once

#include <tuple>
#include <string>

struct basic {
	int var = 500;

	basic() = default;
	basic(int x) : var(x) {}

	int get() const {
		return var;
	}

	void set(int x) {
		var = x;
	}
};

struct basic_stateful {
	int storage;

	int operator()(int i) {
		storage = i;
		return storage;
	}
};

struct complex_base_a {
	int a = 250;

	virtual int a_func() const {
		return a;
	}
};

struct complex_base_b {
	int b = 500;

	virtual int b_func() const {
		return b;
	}
};

struct complex_ab : complex_base_a, complex_base_b {
	int ab = 2500;

	virtual int a_func() const override {
		return ab;
	}

	virtual int b_func() const override {
		return ab;
	}

	int ab_func() const {
		return ab;
	}
};

inline int basic_call(int x) {
	return x;
}

inline basic basic_return(int x) {
	return basic(x);
}

inline std::tuple<int, int> basic_multi_return(int i) {
	return { i, i * 2 };
}
