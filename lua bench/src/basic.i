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

struct basic_var {
	int var0;
	int var1;
	int var2;
	int var3;
	int var4;

	basic_var();
};

struct basic_var_complex {
	int var0;
	int var1;
	int var2;
	int var3;
	int var4;
	int var5;
	int var6;
	int var7;
	int var8;
	int var9;
	int var10;
	int var11;
	int var12;
	int var13;
	int var14;
	int var15;
	int var16;
	int var17;
	int var18;
	int var19;
	int var20;
	int var21;
	int var22;
	int var23;
	int var24;
	int var25;
	int var26;
	int var27;
	int var28;
	int var29;
	int var30;
	int var31;
	int var32;
	int var33;
	int var34;
	int var35;
	int var36;
	int var37;
	int var38;
	int var39;
	int var40;
	int var41;
	int var42;
	int var43;
	int var44;
	int var45;
	int var46;
	int var47;
	int var48;
	int var49;

	basic_var_complex();
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
