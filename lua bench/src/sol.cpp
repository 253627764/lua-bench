#define SOL_NO_EXCEPTIONS

#include <sol.hpp>
#include "lua bench.hpp"
#include "basic.hpp"
#include "basic_lua.hpp"

namespace lb {

	void sol_global_string_get_measure(nonius::chronometer& meter) {
		sol::state lua;
		lua["value"] = 24;
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua.get<int>("value");
				x += v;
			}
			return x;
		});
	}

	void sol_global_string_set_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua.set("value", i);
			}
		});
	}

	void sol_table_get_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.create_table("warble", 0, 0, "value", 24);
		sol::table t = lua["warble"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = t["value"];
				x += v;
			}
			return x;
		});
	}

	void sol_table_set_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.create_table("warble", 0, 0);
		sol::table x = lua["warble"];
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				x.set("value", i);
		});
	}

	void sol_chained_get_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.create_table("ulahibe", 0, 0, "warble", lua.create_table(0, 0, "value", 24));
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["ulahibe"]["warble"]["value"];
				x += v;
			}
			return x;
		});
	}

	void sol_chained_set_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.create_table("ulahibe", 0, 0, "warble", lua.create_table(0, 0, "value", 24));
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				lua["ulahibe"]["warble"]["value"] = i;
		});
	}

	void sol_c_function_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.set_function("f", sol::c_call<decltype(&basic_call), &basic_call>);
		std::string code = repeated_code("f(i)");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_lua_function_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.script(R"(function f (i)
			return i;
		end)");
		sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f.call<int>(i);
				x += v;
			}
			return x;
		});
	}

	void sol_c_through_lua_function_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.set_function("f", sol::c_call<decltype(&basic_call), &basic_call>);
		sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f.call<int>(i);
				x += v;
			}
			return x;
		});
	}

	void sol_member_function_call_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.new_usertype<basic>("basic",
			"get", sol::c_call<decltype(&basic::get), &basic::get>,
			"set", sol::c_call<decltype(&basic::set), &basic::set>
		);
		lua.script("b = basic:new()");
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_member_variable_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.new_usertype<basic>("basic",
			"var0", &basic::var,
			"var1", &basic::var,
			"var2", &basic::var,
			"var3", &basic::var,
			"var4", &basic::var
		);
		lua.script("b = basic:new()");
		std::string code = repeated_code(
			"b.var0 = i\n"
			"x = b.var0\n"
			"b.var4 = i\n"
			"x = b.var4\n"
			"b.var1 = i\n"
			"x = b.var1\n"
			"b.var3 = i\n"
			"x = b.var3\n"
			"b.var2 = i\n"
			"x = b.var2\n"
		);
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_member_variable_complex_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.new_usertype<basic>("basic",
			"var0", &basic::var,
			"var1", &basic::var,
			"var2", &basic::var,
			"var3", &basic::var,
			"var4", &basic::var,
			"var5", &basic::var,
			"var6", &basic::var,
			"var7", &basic::var,
			"var8", &basic::var,
			"var9", &basic::var,
			"var10", &basic::var,
			"var11", &basic::var,
			"var12", &basic::var,
			"var13", &basic::var,
			"var14", &basic::var,
			"var15", &basic::var,
			"var16", &basic::var,
			"var17", &basic::var,
			"var18", &basic::var,
			"var19", &basic::var,
			"var20", &basic::var,
			"var21", &basic::var,
			"var22", &basic::var,
			"var23", &basic::var,
			"var24", &basic::var,
			"var25", &basic::var,
			"var26", &basic::var,
			"var27", &basic::var,
			"var28", &basic::var,
			"var29", &basic::var,
			"var30", &basic::var,
			"var31", &basic::var,
			"var32", &basic::var,
			"var33", &basic::var,
			"var34", &basic::var,
			"var35", &basic::var,
			"var36", &basic::var,
			"var37", &basic::var,
			"var38", &basic::var,
			"var39", &basic::var,
			"var40", &basic::var,
			"var41", &basic::var,
			"var42", &basic::var,
			"var43", &basic::var,
			"var44", &basic::var,
			"var45", &basic::var,
			"var46", &basic::var,
			"var47", &basic::var,
			"var48", &basic::var,
			"var49", &basic::var
		);
		lua.script("b = basic:new()");
		std::string code = repeated_code(
			"b.var0 = i\nx = b.var0\n"
			"b.var49 = i\nx = b.var49\n"
			"b.var2 = i\nx = b.var2\n"
			"b.var47 = i\nx = b.var47\n"
			"b.var4 = i\nx = b.var4\n"
			"b.var45 = i\nx = b.var45\n"
			"b.var6 = i\nx = b.var6\n"
			"b.var43 = i\nx = b.var43\n"
			"b.var8 = i\nx = b.var8\n"
			"b.var41 = i\nx = b.var41\n"
			"b.var10 = i\nx = b.var10\n"
			"b.var39 = i\nx = b.var39\n"
			"b.var12 = i\nx = b.var12\n"
			"b.var37 = i\nx = b.var37\n"
			"b.var14 = i\nx = b.var14\n"
			"b.var35 = i\nx = b.var35\n"
			"b.var16 = i\nx = b.var16\n"
			"b.var33 = i\nx = b.var33\n"
			"b.var18 = i\nx = b.var18\n"
			"b.var31 = i\nx = b.var31\n"
			"b.var20 = i\nx = b.var20\n"
			"b.var29 = i\nx = b.var29\n"
			"b.var22 = i\nx = b.var22\n"
			"b.var27 = i\nx = b.var27\n"
			"b.var24 = i\nx = b.var24\n"
			"b.var25 = i\nx = b.var25\n"
			"b.var26 = i\nx = b.var26\n"
			"b.var23 = i\nx = b.var23\n"
			"b.var28 = i\nx = b.var28\n"
			"b.var21 = i\nx = b.var21\n"
			"b.var30 = i\nx = b.var30\n"
			"b.var19 = i\nx = b.var19\n"
			"b.var32 = i\nx = b.var32\n"
			"b.var17 = i\nx = b.var17\n"
			"b.var34 = i\nx = b.var34\n"
			"b.var15 = i\nx = b.var15\n"
			"b.var36 = i\nx = b.var36\n"
			"b.var13 = i\nx = b.var13\n"
			"b.var38 = i\nx = b.var38\n"
			"b.var11 = i\nx = b.var11\n"
			"b.var40 = i\nx = b.var40\n"
			"b.var9 = i\nx = b.var9\n"
			"b.var42 = i\nx = b.var42\n"
			"b.var7 = i\nx = b.var7\n"
			"b.var44 = i\nx = b.var44\n"
			"b.var5 = i\nx = b.var5\n"
			"b.var46 = i\nx = b.var46\n"
			"b.var3 = i\nx = b.var3\n"
			"b.var48 = i\nx = b.var48\n"
			"b.var1 = i\nx = b.var1\n"
		);
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_member_variable_last_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.new_usertype<basic>("basic",
			"var0", &basic::var,
			"var1", &basic::var,
			"var2", &basic::var,
			"var3", &basic::var,
			"var4", &basic::var,
			"var5", &basic::var,
			"var6", &basic::var,
			"var7", &basic::var,
			"var8", &basic::var,
			"var9", &basic::var,
			"var10", &basic::var,
			"var11", &basic::var,
			"var12", &basic::var,
			"var13", &basic::var,
			"var14", &basic::var,
			"var15", &basic::var,
			"var16", &basic::var,
			"var17", &basic::var,
			"var18", &basic::var,
			"var19", &basic::var,
			"var20", &basic::var,
			"var21", &basic::var,
			"var22", &basic::var,
			"var23", &basic::var,
			"var24", &basic::var,
			"var25", &basic::var,
			"var26", &basic::var,
			"var27", &basic::var,
			"var28", &basic::var,
			"var29", &basic::var,
			"var30", &basic::var,
			"var31", &basic::var,
			"var32", &basic::var,
			"var33", &basic::var,
			"var34", &basic::var,
			"var35", &basic::var,
			"var36", &basic::var,
			"var37", &basic::var,
			"var38", &basic::var,
			"var39", &basic::var,
			"var40", &basic::var,
			"var41", &basic::var,
			"var42", &basic::var,
			"var43", &basic::var,
			"var44", &basic::var,
			"var45", &basic::var,
			"var46", &basic::var,
			"var47", &basic::var,
			"var48", &basic::var,
			"var49", &basic::var
		);
		lua.script("b = basic:new()");
		std::string code = repeated_code("b.var49 = i\nx = b.var49\n");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_member_function_call_simple_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.new_simple_usertype<basic>("basic",
			"get", sol::c_call<decltype(&basic::get), &basic::get>,
			"set", sol::c_call<decltype(&basic::set), &basic::set>
		);
		lua.script("b = basic:new()");
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_member_variable_simple_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.new_simple_usertype<basic>("basic",
			"var0", &basic::var,
			"var1", &basic::var,
			"var2", &basic::var,
			"var3", &basic::var,
			"var4", &basic::var
		);
		lua.script("b = basic:new()");
		std::string code = repeated_code(
			"b.var0 = i\n"
			"x = b.var0\n"
			"b.var4 = i\n"
			"x = b.var4\n"
			"b.var1 = i\n"
			"x = b.var1\n"
			"b.var3 = i\n"
			"x = b.var3\n"
			"b.var2 = i\n"
			"x = b.var2\n"
		);
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_member_variable_complex_simple_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.new_simple_usertype<basic>("basic",
			"var0", &basic::var,
			"var1", &basic::var,
			"var2", &basic::var,
			"var3", &basic::var,
			"var4", &basic::var,
			"var5", &basic::var,
			"var6", &basic::var,
			"var7", &basic::var,
			"var8", &basic::var,
			"var9", &basic::var,
			"var10", &basic::var,
			"var11", &basic::var,
			"var12", &basic::var,
			"var13", &basic::var,
			"var14", &basic::var,
			"var15", &basic::var,
			"var16", &basic::var,
			"var17", &basic::var,
			"var18", &basic::var,
			"var19", &basic::var,
			"var20", &basic::var,
			"var21", &basic::var,
			"var22", &basic::var,
			"var23", &basic::var,
			"var24", &basic::var,
			"var25", &basic::var,
			"var26", &basic::var,
			"var27", &basic::var,
			"var28", &basic::var,
			"var29", &basic::var,
			"var30", &basic::var,
			"var31", &basic::var,
			"var32", &basic::var,
			"var33", &basic::var,
			"var34", &basic::var,
			"var35", &basic::var,
			"var36", &basic::var,
			"var37", &basic::var,
			"var38", &basic::var,
			"var39", &basic::var,
			"var40", &basic::var,
			"var41", &basic::var,
			"var42", &basic::var,
			"var43", &basic::var,
			"var44", &basic::var,
			"var45", &basic::var,
			"var46", &basic::var,
			"var47", &basic::var,
			"var48", &basic::var,
			"var49", &basic::var
		);

		lua.script("b = basic:new()");
		std::string code = repeated_code(
			"b.var0 = i\nx = b.var0\n"
			"b.var49 = i\nx = b.var49\n"
			"b.var2 = i\nx = b.var2\n"
			"b.var47 = i\nx = b.var47\n"
			"b.var4 = i\nx = b.var4\n"
			"b.var45 = i\nx = b.var45\n"
			"b.var6 = i\nx = b.var6\n"
			"b.var43 = i\nx = b.var43\n"
			"b.var8 = i\nx = b.var8\n"
			"b.var41 = i\nx = b.var41\n"
			"b.var10 = i\nx = b.var10\n"
			"b.var39 = i\nx = b.var39\n"
			"b.var12 = i\nx = b.var12\n"
			"b.var37 = i\nx = b.var37\n"
			"b.var14 = i\nx = b.var14\n"
			"b.var35 = i\nx = b.var35\n"
			"b.var16 = i\nx = b.var16\n"
			"b.var33 = i\nx = b.var33\n"
			"b.var18 = i\nx = b.var18\n"
			"b.var31 = i\nx = b.var31\n"
			"b.var20 = i\nx = b.var20\n"
			"b.var29 = i\nx = b.var29\n"
			"b.var22 = i\nx = b.var22\n"
			"b.var27 = i\nx = b.var27\n"
			"b.var24 = i\nx = b.var24\n"
			"b.var25 = i\nx = b.var25\n"
			"b.var26 = i\nx = b.var26\n"
			"b.var23 = i\nx = b.var23\n"
			"b.var28 = i\nx = b.var28\n"
			"b.var21 = i\nx = b.var21\n"
			"b.var30 = i\nx = b.var30\n"
			"b.var19 = i\nx = b.var19\n"
			"b.var32 = i\nx = b.var32\n"
			"b.var17 = i\nx = b.var17\n"
			"b.var34 = i\nx = b.var34\n"
			"b.var15 = i\nx = b.var15\n"
			"b.var36 = i\nx = b.var36\n"
			"b.var13 = i\nx = b.var13\n"
			"b.var38 = i\nx = b.var38\n"
			"b.var11 = i\nx = b.var11\n"
			"b.var40 = i\nx = b.var40\n"
			"b.var9 = i\nx = b.var9\n"
			"b.var42 = i\nx = b.var42\n"
			"b.var7 = i\nx = b.var7\n"
			"b.var44 = i\nx = b.var44\n"
			"b.var5 = i\nx = b.var5\n"
			"b.var46 = i\nx = b.var46\n"
			"b.var3 = i\nx = b.var3\n"
			"b.var48 = i\nx = b.var48\n"
			"b.var1 = i\nx = b.var1\n"
		);
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_member_variable_last_simple_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.new_simple_usertype<basic>("basic",
			"var0", &basic::var,
			"var1", &basic::var,
			"var2", &basic::var,
			"var3", &basic::var,
			"var4", &basic::var,
			"var5", &basic::var,
			"var6", &basic::var,
			"var7", &basic::var,
			"var8", &basic::var,
			"var9", &basic::var,
			"var10", &basic::var,
			"var11", &basic::var,
			"var12", &basic::var,
			"var13", &basic::var,
			"var14", &basic::var,
			"var15", &basic::var,
			"var16", &basic::var,
			"var17", &basic::var,
			"var18", &basic::var,
			"var19", &basic::var,
			"var20", &basic::var,
			"var21", &basic::var,
			"var22", &basic::var,
			"var23", &basic::var,
			"var24", &basic::var,
			"var25", &basic::var,
			"var26", &basic::var,
			"var27", &basic::var,
			"var28", &basic::var,
			"var29", &basic::var,
			"var30", &basic::var,
			"var31", &basic::var,
			"var32", &basic::var,
			"var33", &basic::var,
			"var34", &basic::var,
			"var35", &basic::var,
			"var36", &basic::var,
			"var37", &basic::var,
			"var38", &basic::var,
			"var39", &basic::var,
			"var40", &basic::var,
			"var41", &basic::var,
			"var42", &basic::var,
			"var43", &basic::var,
			"var44", &basic::var,
			"var45", &basic::var,
			"var46", &basic::var,
			"var47", &basic::var,
			"var48", &basic::var,
			"var49", &basic::var
			);

		lua.script("b = basic:new()");
		std::string code = repeated_code(
			"b.var49 = i\nx = b.var49\n"
		);
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_stateful_function_object_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		int storage = 0;
		lua.set_function("f", basic_stateful());
		sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f.call<int>(i);
				x += v;
			}
			return x;
		});
	}

	void sol_multi_return_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.set_function("f", sol::c_call<decltype(&basic_multi_return), basic_multi_return>);
		sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				std::tuple<int, int> v = f.call<int, int>(i);
				x += static_cast<int>(std::get<0>(v));
				x += static_cast<int>(std::get<1>(v));
			}
			return x;
		});
	}

	void sol_base_derived_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.new_usertype<complex_ab>("complex_ab",
			"a_func", &complex_ab::a_func,
			"b_func", &complex_ab::b_func,
			"ab_func", &complex_ab::ab_func,
			sol::base_classes, sol::bases<complex_base_a, complex_base_b>()
		);
		complex_ab ab;
		// Set and verify correctness
		lua.set("b", &ab);
		{
			complex_base_a& va = lua["b"];
			complex_base_b& vb = lua["b"];
			if (va.a_func() != ab.a_func() || va.a != ab.a) {
				throw std::logic_error("proper base class casting not provided: failing test");
			}
			if (vb.b_func() != ab.b_func() || vb.b != ab.b) {
				throw std::logic_error("proper base class casting not provided: failing test");
			}
		}
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				complex_base_a& va = lua["b"];
				complex_base_b& vb = lua["b"];
				x += va.a_func();
				x += vb.b_func();
			}
			return x;
		});
	}

	void sol_optional_measure(nonius::chronometer& meter) {
		sol::state lua;
		lua.set_panic(panic_throw);

		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				sol::optional<int> v = lua["warble"]["value"];
				x += v.value_or(1);
			}
			return x;
		});
	}

	void sol_return_userdata_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.set_function("f", sol::c_call<decltype(&basic_return), basic_return>);
		std::string code = repeated_code("b = f(i)");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_implicit_inheritance_call_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);

		lua.new_usertype<complex_base_a>("complex_base_a",
			"a", &complex_base_a::a,
			"a_func", &complex_base_a::a_func
		);

		lua.new_usertype<complex_base_b>("complex_base_b",
			"b", &complex_base_b::b,
			"b_func", &complex_base_b::b_func
		);

		lua.new_usertype<complex_ab>("complex_ab",
			"ab", &complex_ab::ab,
			"ab_func", &complex_ab::ab_func,
			sol::base_classes, sol::bases<complex_base_a, complex_base_b>()
		);
		
		complex_ab ab;
		// Set and verify correctness
		lua.set("b", &ab);

		std::string code = repeated_code("b:b_func()");
		meter.measure([&]() {
			lua.script(code);
		});
	}

}
