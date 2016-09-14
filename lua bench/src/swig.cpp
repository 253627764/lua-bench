#include "lua bench.hpp"
#include "basic.hpp"
#include "basic_lua.hpp"

extern "C" {
	int luaopen_lb(lua_State* L);
}

namespace lb {
	
	void swig_global_string_get_measure(nonius::chronometer& meter) {
		// Unsupported
		// meter.measure([](){});
	}

	void swig_global_string_set_measure(nonius::chronometer& meter) {
		// Unsupported
		// meter.measure([](){});
	}

	void swig_table_get_measure(nonius::chronometer& meter) {
		// Unsupported
		// meter.measure([](){});
	}

	void swig_table_set_measure(nonius::chronometer& meter) {
		// Unsupported
		// meter.measure([](){});
	}

	void swig_chained_get_measure(nonius::chronometer& meter) {
		// Unsupported
		// meter.measure([](){});
	}

	void swig_chained_set_measure(nonius::chronometer& meter) {
		// Unsupported
		// meter.measure([](){});
	}

	void swig_c_function_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "f = lb.basic_call");

		auto code = repeated_code("f(i)");
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void swig_lua_function_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);
		lua_do_or_die(L, "function f (i) return i end");
		
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				lua_getglobal(L, "f");
				lua_pushinteger(L, i);
				lua_pcallk(L, 1, 1, LUA_NOREF, 0, nullptr);
				int v = static_cast<int>(lua_tointeger(L, -1));
				x += v;
				lua_pop(L, 1);
			}
			return x;
		});
	}

	void swig_c_through_lua_function_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "f = lb.basic_call");

		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				lua_getglobal(L, "f");
				lua_pushinteger(L, i);
				lua_pcallk(L, 1, 1, LUA_NOREF, 0, nullptr);
				int v = static_cast<int>(lua_tointeger(L, -1));
				x += v;
				lua_pop(L, 1);
			}
			return x;
		});
	}

	void swig_member_function_call_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "b = lb.basic()");

		auto code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void swig_member_variable_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "b = lb.basic_var()");
		
		auto code = repeated_code(
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
			lua_do_or_die(L, code.c_str());
		});
	}

	void swig_member_variable_complex_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "b = lb.basic_var_complex()");

		auto code = repeated_code(
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
			lua_do_or_die(L, code.c_str());
		});
	}

	void swig_member_variable_last_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "b = lb.basic_var_complex()");

		auto code = repeated_code(
			"b.var49 = i\nx = b.var49\n"
		);
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void swig_stateful_function_object_measure(nonius::chronometer& meter) {
		// Unsupported:
		// SWIG seems to do some erroneous function-type casting
		// and it breaks C++ compilers.
		// Sigh...

		/*lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "f = lb.basic_stateful()");

		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				lua_getglobal(L, "f");
				lua_pushinteger(L, i);
				lua_pcallk(L, 1, 1, LUA_NOREF, 0, nullptr);
				int v = static_cast<int>(lua_tointeger(L, -1));
				x += v;
				lua_pop(L, 1);
			}
			return x;
		})*/;
	}

	void swig_multi_return_measure(nonius::chronometer& meter) {
		// std::tuple and its friends
		// are currently unsupported,
		// but there's a way to map multiple outputs?
		// need to look deeper into SWIG documentation
		meter.measure([&]() {
		});
	}

	void swig_base_derived_measure(nonius::chronometer& meter) {
		// Unsupported
		meter.measure([&]() {
		});
	}

	void swig_optional_measure(nonius::chronometer& meter) {
		// Unsupported
		meter.measure([&]() {
		});
	}

	void swig_return_userdata_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "f = lb.basic_return");

		auto code = repeated_code("b = f(i)");
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void swig_implicit_inheritance_call_measure(nonius::chronometer& meter) {
		// Unsupported
		// E.g., we're doing something wrong
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "b = lb.complex_ab()");

		std::string code = repeated_code("b:b_func()");
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

}
