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

struct basic_stateful {
	int storage;

	basic_stateful();
};

int basic_call(int x);

basic basic_return(int x);
