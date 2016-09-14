#include "lua bench.hpp"
#include "basic.hpp"
#include "basic_lua.hpp"
#include <lua.hpp>
#include <luabind/luabind.hpp>

namespace lb {

	void luabind_global_string_get_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		lua_do_or_die(L, "value = 24");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				luabind::object o = luabind::globals(L)["value"];
				o.push(L);
				int v = static_cast<int>(lua_tointeger(L, -1));
				lua_pop(L, -1);
				x += v;
			}
			return x;
		});
	}

	void luabind_global_string_set_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		lua_do_or_die(L, "value = 0");
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				luabind::globals(L)["value"] = 24;
			}
		});
	}

	void luabind_chained_get_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		lua_do_or_die(L, "ulahibe = { warble = { value = 24 } }");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				luabind::object o = luabind::globals(L)["ulahibe"]["warble"]["value"];
				o.push(L);
				int v = static_cast<int>(lua_tointeger(L, -1));
				lua_pop(L, -1);
				x += v;
			}
			return x;
		});
	}

	void luabind_chained_set_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		lua_do_or_die(L, "ulahibe = { warble = { value = 0 } }");
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				luabind::globals(L)["ulahibe"]["warble"]["value"] = 24;
			}
		});
	}

	void luabind_table_get_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		lua_do_or_die(L, "warble = { value = 24 }");

		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				luabind::object o = luabind::globals(L)["warble"]["value"];
				o.push(L);
				int v = static_cast<int>(lua_tointeger(L, -1));
				lua_pop(L, -1);
				x += v;
			}
			return x;
		});
	}

	void luabind_table_set_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		lua_do_or_die(L, "warble = { value = 24 }");
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				luabind::globals(L)["warble"]["value"] = 24;
			}
		});
	}

	void luabind_c_function_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		luabind::module(L) [
			luabind::def("f", basic_call)
		];
		auto code = repeated_code("f(i)");
		meter.measure([&L, &code]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void luabind_lua_function_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		lua_do_or_die(L, "function f (i) return i end");

		luabind::object func = luabind::globals(L)["f"];
		meter.measure([&func]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = luabind::call_function<int>(func, i);
				x += v;
			}
			return x;
		});
	}

	void luabind_c_through_lua_function_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		luabind::module(L)[
			luabind::def("f", basic_call)
		];
		luabind::object func = luabind::globals(L)["f"];
		meter.measure([&func]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = luabind::call_function<int>(func, i);
				x += v;
			}
			return x;
		});
	}

	void luabind_member_function_call_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		luabind::module(L)[
			luabind::class_<basic>("basic")
				.def(luabind::constructor<>())
				.def_nonconst("set", &basic::set)
				.def_const("get", &basic::get)
				.def_readwrite("var", &basic::var)
		];
		lua_do_or_die(L, "b = basic()");
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void luabind_member_variable_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		luabind::module(L)[
			luabind::class_<basic>("basic")
				.def(luabind::constructor<>())
				.def_readwrite("var0", &basic::var)
				.def_readwrite("var1", &basic::var)
				.def_readwrite("var2", &basic::var)
				.def_readwrite("var3", &basic::var)
				.def_readwrite("var4", &basic::var)
		];
		lua_do_or_die(L, "b = basic()");
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
			lua_do_or_die(L, code.c_str());
		});
	}

	void luabind_member_variable_complex_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		luabind::module(L)[
			luabind::class_<basic>("basic")
				.def(luabind::constructor<>())
				.def_readwrite("var0", &basic::var)
				.def_readwrite("var1", &basic::var)
				.def_readwrite("var2", &basic::var)
				.def_readwrite("var3", &basic::var)
				.def_readwrite("var4", &basic::var)
				.def_readwrite("var5", &basic::var)
				.def_readwrite("var6", &basic::var)
				.def_readwrite("var7", &basic::var)
				.def_readwrite("var8", &basic::var)
				.def_readwrite("var9", &basic::var)
				.def_readwrite("var10", &basic::var)
				.def_readwrite("var11", &basic::var)
				.def_readwrite("var12", &basic::var)
				.def_readwrite("var13", &basic::var)
				.def_readwrite("var14", &basic::var)
				.def_readwrite("var15", &basic::var)
				.def_readwrite("var16", &basic::var)
				.def_readwrite("var17", &basic::var)
				.def_readwrite("var18", &basic::var)
				.def_readwrite("var19", &basic::var)
				.def_readwrite("var20", &basic::var)
				.def_readwrite("var21", &basic::var)
				.def_readwrite("var22", &basic::var)
				.def_readwrite("var23", &basic::var)
				.def_readwrite("var24", &basic::var)
				.def_readwrite("var25", &basic::var)
				.def_readwrite("var26", &basic::var)
				.def_readwrite("var27", &basic::var)
				.def_readwrite("var28", &basic::var)
				.def_readwrite("var29", &basic::var)
				.def_readwrite("var30", &basic::var)
				.def_readwrite("var31", &basic::var)
				.def_readwrite("var32", &basic::var)
				.def_readwrite("var33", &basic::var)
				.def_readwrite("var34", &basic::var)
				.def_readwrite("var35", &basic::var)
				.def_readwrite("var36", &basic::var)
				.def_readwrite("var37", &basic::var)
				.def_readwrite("var38", &basic::var)
				.def_readwrite("var39", &basic::var)
				.def_readwrite("var40", &basic::var)
				.def_readwrite("var41", &basic::var)
				.def_readwrite("var42", &basic::var)
				.def_readwrite("var43", &basic::var)
				.def_readwrite("var44", &basic::var)
				.def_readwrite("var45", &basic::var)
				.def_readwrite("var46", &basic::var)
				.def_readwrite("var47", &basic::var)
				.def_readwrite("var48", &basic::var)
				.def_readwrite("var49", &basic::var)
		];
		lua_do_or_die(L, "b = basic()");
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
			lua_do_or_die(L, code.c_str());
		});
	}

	void luabind_member_variable_last_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		luabind::module(L)[
			luabind::class_<basic>("basic")
				.def(luabind::constructor<>())
				.def_readwrite("var0", &basic::var)
				.def_readwrite("var1", &basic::var)
				.def_readwrite("var2", &basic::var)
				.def_readwrite("var3", &basic::var)
				.def_readwrite("var4", &basic::var)
				.def_readwrite("var5", &basic::var)
				.def_readwrite("var6", &basic::var)
				.def_readwrite("var7", &basic::var)
				.def_readwrite("var8", &basic::var)
				.def_readwrite("var9", &basic::var)
				.def_readwrite("var10", &basic::var)
				.def_readwrite("var11", &basic::var)
				.def_readwrite("var12", &basic::var)
				.def_readwrite("var13", &basic::var)
				.def_readwrite("var14", &basic::var)
				.def_readwrite("var15", &basic::var)
				.def_readwrite("var16", &basic::var)
				.def_readwrite("var17", &basic::var)
				.def_readwrite("var18", &basic::var)
				.def_readwrite("var19", &basic::var)
				.def_readwrite("var20", &basic::var)
				.def_readwrite("var21", &basic::var)
				.def_readwrite("var22", &basic::var)
				.def_readwrite("var23", &basic::var)
				.def_readwrite("var24", &basic::var)
				.def_readwrite("var25", &basic::var)
				.def_readwrite("var26", &basic::var)
				.def_readwrite("var27", &basic::var)
				.def_readwrite("var28", &basic::var)
				.def_readwrite("var29", &basic::var)
				.def_readwrite("var30", &basic::var)
				.def_readwrite("var31", &basic::var)
				.def_readwrite("var32", &basic::var)
				.def_readwrite("var33", &basic::var)
				.def_readwrite("var34", &basic::var)
				.def_readwrite("var35", &basic::var)
				.def_readwrite("var36", &basic::var)
				.def_readwrite("var37", &basic::var)
				.def_readwrite("var38", &basic::var)
				.def_readwrite("var39", &basic::var)
				.def_readwrite("var40", &basic::var)
				.def_readwrite("var41", &basic::var)
				.def_readwrite("var42", &basic::var)
				.def_readwrite("var43", &basic::var)
				.def_readwrite("var44", &basic::var)
				.def_readwrite("var45", &basic::var)
				.def_readwrite("var46", &basic::var)
				.def_readwrite("var47", &basic::var)
				.def_readwrite("var48", &basic::var)
				.def_readwrite("var49", &basic::var)
		];
		lua_do_or_die(L, "b = basic()");
		std::string code = repeated_code(
			"b.var49 = i\nx = b.var49\n"
		);
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void luabind_stateful_function_object_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		luabind::module(L)[
			luabind::class_<basic_stateful>("basic_stateful")
				.def(luabind::constructor<>())
				.def("__call", &basic_stateful::operator())
		];
		lua_do_or_die(L, "f = basic_stateful()");

		luabind::object func = luabind::globals(L)["f"];
		meter.measure([&func]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = luabind::call_function<int>(func, i);
				x += v;
			}
			return x;
		});
	}

	void luabind_multi_return_measure(nonius::chronometer& meter) {
		// Unsupported: requires you to register
		// every kind of tuple you want individually
		// In BetterTwitchTV terms: LUL
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);
		luabind::module(L)[
			luabind::def("f", basic_multi_return)
		];
		luabind::object func = luabind::globals(L)["f"];
		meter.measure([&func]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				std::tuple<int, int> v = luabind::call_function<std::tuple<int, int>>(func, i);
				x += std::get<0>(v);
				x += std::get<1>(v);
			}
			return x;
		});
	}

	void luabind_base_derived_measure(nonius::chronometer& meter) {
		// Unsupported
		// You'd have to figure out the casting yourself and use the Lua API,
		// at which point it's not really an abstraction anymore, is it?
		meter.measure([&]() {
		});
	}

	void luabind_return_userdata_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaL_openlibs(L);
		luabind::open(L);

		luabind::module(L)[
			luabind::class_<basic>("basic")
				.def(luabind::constructor<>())
		];

		luabind::module(L)[
			luabind::def("f", basic_return)
		];

		std::string code = repeated_code("b = f(i)");
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void luabind_optional_measure(nonius::chronometer& meter) {
		// Unsupported
		// You'd have to figure out the casting yourself and use the Lua API,
		// at which point it's not really an abstraction anymore, is it?
		meter.measure([&]() {
		});
	}

}
