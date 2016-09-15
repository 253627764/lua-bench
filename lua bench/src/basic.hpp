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

struct basic_var {
	int var0 = 500;
	int var1 = 500;
	int var2 = 500;
	int var3 = 500;
	int var4 = 500;

	basic_var() = default;
};

struct basic_var_complex {
	int var0 = 500;
	int var1 = 500;
	int var2 = 500;
	int var3 = 500;
	int var4 = 500;
	int var5 = 500;
	int var6 = 500;
	int var7 = 500;
	int var8 = 500;
	int var9 = 500;
	int var10 = 500;
	int var11 = 500;
	int var12 = 500;
	int var13 = 500;
	int var14 = 500;
	int var15 = 500;
	int var16 = 500;
	int var17 = 500;
	int var18 = 500;
	int var19 = 500;
	int var20 = 500;
	int var21 = 500;
	int var22 = 500;
	int var23 = 500;
	int var24 = 500;
	int var25 = 500;
	int var26 = 500;
	int var27 = 500;
	int var28 = 500;
	int var29 = 500;
	int var30 = 500;
	int var31 = 500;
	int var32 = 500;
	int var33 = 500;
	int var34 = 500;
	int var35 = 500;
	int var36 = 500;
	int var37 = 500;
	int var38 = 500;
	int var39 = 500;
	int var40 = 500;
	int var41 = 500;
	int var42 = 500;
	int var43 = 500;
	int var44 = 500;
	int var45 = 500;
	int var46 = 500;
	int var47 = 500;
	int var48 = 500;
	int var49 = 500;

	basic_var_complex() = default;
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
