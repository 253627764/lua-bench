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
		];
		lua_do_or_die(L, "b = basic()");
		std::string code = repeated_code(member_function_call_code);
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
				.def_readwrite("var", &basic::var)
				.def_readwrite("var0", &basic::var0)
				.def_readwrite("var1", &basic::var1)
				.def_readwrite("var2", &basic::var2)
				.def_readwrite("var3", &basic::var3)
				.def_readwrite("var4", &basic::var4)
		];
		lua_do_or_die(L, "b = basic()");
		std::string code = repeated_code(
			member_variable_code
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
			luabind::class_<basic_large>("basic_large")
				.def(luabind::constructor<>())
				.def_readwrite("var", &basic_large::var)
				.def_readwrite("var0", &basic_large::var0)
				.def_readwrite("var1", &basic_large::var1)
				.def_readwrite("var2", &basic_large::var2)
				.def_readwrite("var3", &basic_large::var3)
				.def_readwrite("var4", &basic_large::var4)
				.def_readwrite("var5", &basic_large::var5)
				.def_readwrite("var6", &basic_large::var6)
				.def_readwrite("var7", &basic_large::var7)
				.def_readwrite("var8", &basic_large::var8)
				.def_readwrite("var9", &basic_large::var9)
				.def_readwrite("var10", &basic_large::var10)
				.def_readwrite("var11", &basic_large::var11)
				.def_readwrite("var12", &basic_large::var12)
				.def_readwrite("var13", &basic_large::var13)
				.def_readwrite("var14", &basic_large::var14)
				.def_readwrite("var15", &basic_large::var15)
				.def_readwrite("var16", &basic_large::var16)
				.def_readwrite("var17", &basic_large::var17)
				.def_readwrite("var18", &basic_large::var18)
				.def_readwrite("var19", &basic_large::var19)
				.def_readwrite("var20", &basic_large::var20)
				.def_readwrite("var21", &basic_large::var21)
				.def_readwrite("var22", &basic_large::var22)
				.def_readwrite("var23", &basic_large::var23)
				.def_readwrite("var24", &basic_large::var24)
				.def_readwrite("var25", &basic_large::var25)
				.def_readwrite("var26", &basic_large::var26)
				.def_readwrite("var27", &basic_large::var27)
				.def_readwrite("var28", &basic_large::var28)
				.def_readwrite("var29", &basic_large::var29)
				.def_readwrite("var30", &basic_large::var30)
				.def_readwrite("var31", &basic_large::var31)
				.def_readwrite("var32", &basic_large::var32)
				.def_readwrite("var33", &basic_large::var33)
				.def_readwrite("var34", &basic_large::var34)
				.def_readwrite("var35", &basic_large::var35)
				.def_readwrite("var36", &basic_large::var36)
				.def_readwrite("var37", &basic_large::var37)
				.def_readwrite("var38", &basic_large::var38)
				.def_readwrite("var39", &basic_large::var39)
				.def_readwrite("var40", &basic_large::var40)
				.def_readwrite("var41", &basic_large::var41)
				.def_readwrite("var42", &basic_large::var42)
				.def_readwrite("var43", &basic_large::var43)
				.def_readwrite("var44", &basic_large::var44)
				.def_readwrite("var45", &basic_large::var45)
				.def_readwrite("var46", &basic_large::var46)
				.def_readwrite("var47", &basic_large::var47)
				.def_readwrite("var48", &basic_large::var48)
				.def_readwrite("var49", &basic_large::var49)
		];
		lua_do_or_die(L, "b = basic_large()");
		std::string code = repeated_code(
			member_variable_large_code
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
			luabind::class_<basic_large>("basic_large")
				.def(luabind::constructor<>())
				.def_readwrite("var", &basic_large::var)
				.def_readwrite("var0", &basic_large::var0)
				.def_readwrite("var1", &basic_large::var1)
				.def_readwrite("var2", &basic_large::var2)
				.def_readwrite("var3", &basic_large::var3)
				.def_readwrite("var4", &basic_large::var4)
				.def_readwrite("var5", &basic_large::var5)
				.def_readwrite("var6", &basic_large::var6)
				.def_readwrite("var7", &basic_large::var7)
				.def_readwrite("var8", &basic_large::var8)
				.def_readwrite("var9", &basic_large::var9)
				.def_readwrite("var10", &basic_large::var10)
				.def_readwrite("var11", &basic_large::var11)
				.def_readwrite("var12", &basic_large::var12)
				.def_readwrite("var13", &basic_large::var13)
				.def_readwrite("var14", &basic_large::var14)
				.def_readwrite("var15", &basic_large::var15)
				.def_readwrite("var16", &basic_large::var16)
				.def_readwrite("var17", &basic_large::var17)
				.def_readwrite("var18", &basic_large::var18)
				.def_readwrite("var19", &basic_large::var19)
				.def_readwrite("var20", &basic_large::var20)
				.def_readwrite("var21", &basic_large::var21)
				.def_readwrite("var22", &basic_large::var22)
				.def_readwrite("var23", &basic_large::var23)
				.def_readwrite("var24", &basic_large::var24)
				.def_readwrite("var25", &basic_large::var25)
				.def_readwrite("var26", &basic_large::var26)
				.def_readwrite("var27", &basic_large::var27)
				.def_readwrite("var28", &basic_large::var28)
				.def_readwrite("var29", &basic_large::var29)
				.def_readwrite("var30", &basic_large::var30)
				.def_readwrite("var31", &basic_large::var31)
				.def_readwrite("var32", &basic_large::var32)
				.def_readwrite("var33", &basic_large::var33)
				.def_readwrite("var34", &basic_large::var34)
				.def_readwrite("var35", &basic_large::var35)
				.def_readwrite("var36", &basic_large::var36)
				.def_readwrite("var37", &basic_large::var37)
				.def_readwrite("var38", &basic_large::var38)
				.def_readwrite("var39", &basic_large::var39)
				.def_readwrite("var40", &basic_large::var40)
				.def_readwrite("var41", &basic_large::var41)
				.def_readwrite("var42", &basic_large::var42)
				.def_readwrite("var43", &basic_large::var43)
				.def_readwrite("var44", &basic_large::var44)
				.def_readwrite("var45", &basic_large::var45)
				.def_readwrite("var46", &basic_large::var46)
				.def_readwrite("var47", &basic_large::var47)
				.def_readwrite("var48", &basic_large::var48)
				.def_readwrite("var49", &basic_large::var49)
		];
		lua_do_or_die(L, "b = basic_large()");
		std::string code = repeated_code(
			member_variable_large_last_code
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
