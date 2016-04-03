#pragma once

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
};

inline int basic_call(int x) {
	return x;
}
