%module lb
%{
#include "basic.hpp"
%}

struct basic {
	int var;

	basic();

	int get() const;

	void set(int x);
};

struct complex_base_a {
	int a;

	int a_func() const;
};

struct complex_base_b {
	int b;

	int b_func() const;
};

struct complex_ab : complex_base_a, complex_base_b {
	int ab;

	int a_func() const;

	int b_func() const;

	int ab_func() const;
};

struct basic_stateful {
	int storage;

	basic_stateful();
};

int basic_call(int x);

basic basic_return(int x);
