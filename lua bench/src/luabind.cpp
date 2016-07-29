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
				.def_nonconst("set", &basic::set)
				.def_const("get", &basic::get)
				.def_readwrite("var", &basic::var)
		];
		lua_do_or_die(L, "b = basic()");
		std::string code = repeated_code("b.var = i\nx = b.var");
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
