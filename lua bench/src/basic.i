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

int basic_call(int x);
