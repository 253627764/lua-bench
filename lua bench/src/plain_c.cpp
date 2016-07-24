#include <lua.hpp>
#include "lua bench.hpp"
#include "basic.hpp"
#include "basic_lua.hpp"

namespace lb {

	void plain_global_string_get_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

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

	void plain_global_string_set_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		meter.measure([&]() {
			lua_pushinteger(L, 24);
			lua_setglobal(L, "value");
		});
	}

	void plain_table_get_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		lua_createtable(L, 0, 0);
		lua_pushinteger(L, 24);
		lua_setfield(L, -2, "value");
		lua_setglobal(L, "warble");
		
		lua_getglobal(L, "warble");
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

	void plain_table_set_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		lua_createtable(L, 0, 0);
		lua_pushinteger(L, 24);
		lua_setfield(L, -2, "value");
		lua_setglobal(L, "warble");
		
		lua_getglobal(L, "warble");
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua_pushinteger(L, i);
				lua_setfield(L, -2, "value");
			}
		});
		lua_pop(L, 1);
	}

	void plain_chained_get_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		lua_createtable(L, 0, 0);
		lua_createtable(L, 0, 0);
		lua_pushinteger(L, 24);
		lua_setfield(L, -2, "value");
		lua_setfield(L, -2, "warble");
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

	void plain_chained_set_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

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

	void plain_c_function_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		lua_pushcfunction(L, &basic_call_wrap);
		lua_setglobal(L, "f");
		lua_pushinteger(L, 0);
		lua_setglobal(L, "run");
		auto code = repeated_code("f(i)");
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void plain_lua_function_measure(nonius::chronometer& meter) {
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

	void plain_c_through_lua_function_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		lua_pushcfunction(L, &basic_call_wrap);
		lua_setglobal(L, "f");
		
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

	void plain_member_function_call(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		basic** s = static_cast<basic**>(lua_newuserdata(L, sizeof(basic*)));
		basic b;
		*s = &b;
		luaL_Reg funcs[] = {
			//{ "__index", &basic_index_wrap },
			//{ "__newindex", &basic_newindex_wrap },
			{ "set", &basic_set_wrap },
			{ "get", &basic_get_wrap },
			{ nullptr, nullptr }
		};
		luaL_newmetatable(L, "struct_basic");
		lua_createtable(L, 0, 0);
		luaL_setfuncs(L, funcs, 0);
		lua_setfield(L, -2, "__index");
		lua_setmetatable(L, -2);
		lua_setglobal(L, "b");

		auto code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void plain_member_variable(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		basic** s = static_cast<basic**>(lua_newuserdata(L, sizeof(basic*)));
		basic b;
		*s = &b;
		luaL_Reg funcs[] = {
			{ "__index", &basic_index_wrap },
			{ "__newindex", &basic_newindex_wrap },
			{ nullptr, nullptr }
		};
		luaL_newmetatable(L, "struct_basic");
		luaL_setfuncs(L, funcs, 0);
		lua_setmetatable(L, -2);
		lua_setglobal(L, "b");

		auto code = repeated_code("b.var = i\nx = b.var");
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void plain_c_stateful_function_object_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

	void plain_c_multi_return_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

	void plain_c_base_derived_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

}
