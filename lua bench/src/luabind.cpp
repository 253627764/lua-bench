#include "lua_bench.hpp"
#include "basic.hpp"
#include <lua.hpp>
#include <luabind/luabind.hpp>

namespace lb {

	void luabind_global_string_get_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		luabind::open(L);
		if (luaL_dostring(L, "value = 24"))
			lua_error(L);
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
		luaL_openlibs(L);
		luabind::open(L);
		if (luaL_dostring(L, "value = 0"))
			lua_error(L);
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				luabind::globals(L)["value"] = 24;
			}
		});
	}

	void luabind_chained_get_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		luabind::open(L);
		if (luaL_dostring(L, "ulahibe = { warble = { value = 24 } }"))
			lua_error(L);
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
		luaL_openlibs(L);
		luabind::open(L);
		if (luaL_dostring(L, "ulahibe = { warble = { value = 0 } }"))
			lua_error(L);
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				luabind::globals(L)["ulahibe"]["warble"]["value"] = 24;
			}
		});
	}

	void luabind_table_get_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		luabind::open(L);
		if (luaL_dostring(L, "warble = { value = 24 }"))
			lua_error(L);
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
		luaL_openlibs(L);
		luabind::open(L);
		if (luaL_dostring(L, "warble = { value = 24 }"))
			lua_error(L);
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				luabind::globals(L)["warble"]["value"] = 24;
			}
		});
	}

	void luabind_c_function_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		luabind::open(L);
		luabind::module(L) [
			luabind::def("f", basic_call)
		];
		auto code = repeated_code("f(i)");
		meter.measure([&L, &code]() {
			if (luaL_dostring(L, code.c_str()))
				lua_error(L);
		});
	}

	void luabind_lua_function_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		luabind::open(L);
		if (luaL_dostring(L, "function f (i) return i end"))
			lua_error(L);
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

	void luabind_member_function_call(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		luabind::open(L);
		luabind::module(L)[
			luabind::class_<basic>("basic")
				.def(luabind::constructor<>())
				.def_nonconst("set", &basic::set)
				.def_const("get", &basic::get)
				.def_readwrite("var", &basic::var)
		];
		if (luaL_dostring(L, "b = basic()"))
			lua_error(L);
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			if (luaL_dostring(L, code.c_str()))
				lua_error(L);
		});
	}

	void luabind_member_variable(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		luabind::open(L);
		luabind::module(L)[
			luabind::class_<basic>("basic")
				.def(luabind::constructor<>())
				.def_nonconst("set", &basic::set)
				.def_const("get", &basic::get)
				.def_readwrite("var", &basic::var)
		];
		if (luaL_dostring(L, "b = basic()"))
			lua_error(L);
		std::string code = repeated_code("b.var = i\nx = b.var");
		meter.measure([&]() {
			if (luaL_dostring(L, code.c_str()))
				lua_error(L);
		});
	}

}
