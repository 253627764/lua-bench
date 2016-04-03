#include "lua_bench.hpp"
#include "basic.hpp"
#include "lua_bench_wrap.hpp"

extern "C" {
	int luaopen_lb(lua_State* L);
}

namespace lb {

	void swig_global_string_get_measure(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		lua_pushinteger(L, 24);
		lua_setglobal(L, "value");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				lua_getglobal(L, "value");
				int v = static_cast<int>(lua_tointeger(L, -1));
				x += v;
				lua_pop(L, 1);
			}
			return x;
		});
	}

	void swig_global_string_set_measure(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		meter.measure([&]() {
			lua_pushinteger(L, 24);
			lua_setglobal(L, "value");
		});
	}

	void swig_table_get_measure(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		lua_createtable(L, 0, 0);
		lua_setglobal(L, "warble");
		lua_pushinteger(L, 24);
		lua_setfield(L, -2, "value");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				lua_getfield(L, -1, "value");
				int v = static_cast<int>(lua_tointeger(L, -1));
				x += v;
				lua_pop(L, 1);
			}
			return x;
		});
		lua_pop(L, 1);
	}

	void swig_table_set_measure(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		lua_createtable(L, 0, 0);
		lua_setglobal(L, "warble");
		lua_pushinteger(L, 24);
		lua_setfield(L, -2, "value");
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua_pushinteger(L, i);
				lua_setfield(L, -2, "value");
			}
		});
		lua_pop(L, 1);
	}

	void swig_chained_get_measure(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		lua_createtable(L, 0, 0);
		lua_createtable(L, 0, 0);
		lua_pushinteger(L, 24);
		lua_setfield(L, -2, "warble");
		lua_setfield(L, -2, "value");
		lua_setglobal(L, "ulahibe");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				lua_getglobal(L, "ulahibe");
				lua_getfield(L, -1, "warble");
				lua_getfield(L, -1, "value");
				int v = static_cast<int>(lua_tointeger(L, -1));
				x += v;
				lua_pop(L, 3);
			}
			return x;
		});
	}

	void swig_chained_set_measure(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		lua_createtable(L, 0, 0);
		lua_createtable(L, 0, 0);
		lua_pushinteger(L, 24);
		lua_setfield(L, -2, "value");
		lua_setfield(L, -2, "warble");
		lua_setglobal(L, "ulahibe");
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua_getglobal(L, "ulahibe");
				lua_getfield(L, -1, "warble");
				lua_pushinteger(L, 24);
				lua_setfield(L, -2, "value");
				lua_pop(L, 2);
			}
		});
	}

	void swig_c_function_measure(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		lua_pushcfunction(L, &basic_call_wrap);
		lua_setglobal(L, "f");
		lua_pushinteger(L, 0);
		lua_setglobal(L, "run");
		auto code = repeated_code("f(i)");
		meter.measure([&]() {
			if (!luaL_dostring(L, code.c_str()))
				lua_error(L);
		});
	}

	void swig_lua_function_measure(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		luaL_loadstring(L, R"(function f (i)
			return i;
		end)");
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
		lua_pop(L, 1);
	}

	void swig_c_through_lua_function_measure(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		lua_pushcfunction(L, &basic_call_wrap);
		lua_setglobal(L, "f");
		lua_pushinteger(L, 0);
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

	void swig_member_function_call(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		luaopen_lb(L);
		luaL_dostring(L, "b = lb.new_basic()");

		auto code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			if (!luaL_dostring(L, code.c_str()))
				lua_error(L);
		});
	}

	void swig_member_variable_set(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		luaopen_lb(L);
		luaL_dostring(L, "b = lb.new_basic()");
		
		auto code = repeated_code("b.var = i");
		meter.measure([&]() {
			if (!luaL_dostring(L, code.c_str()))
				lua_error(L);
		});
	}

	void swig_member_variable_get(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		luaopen_lb(L);
		luaL_dostring(L, "b = lb.new_basic()");
		auto code = repeated_code("x = b.var");
		meter.measure([&]() {
			if (!luaL_dostring(L, code.c_str()))
				lua_error(L);
		});
	}

}
