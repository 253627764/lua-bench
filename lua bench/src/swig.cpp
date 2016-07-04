#include "lua_bench.hpp"
#include "basic.hpp"
#include "lua_bench_wrap.hpp"

extern "C" {
	int luaopen_lb(lua_State* L);
}

namespace lb {
	
	inline int atpanic(lua_State* L) {
		const char* message = lua_tostring(L, -1);
		std::string err = message ? message : "An unexpected error occurred and forced the lua state to call atpanic";
		throw std::runtime_error(err);
	}

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
		lua_atpanic(L, atpanic);

		luaopen_lb(L);
		if (luaL_dostring(L, "f = lb.basic_call"))
			lua_error(L);

		auto code = repeated_code("f(i)");
		meter.measure([&]() {
			if (luaL_dostring(L, code.c_str()))
				lua_error(L);
		});
	}

	void swig_lua_function_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, atpanic);
		if (luaL_dostring(L, "function f (i) return i end"))
			lua_error(L);

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
		lua_atpanic(L, atpanic);

		luaopen_lb(L);
		if (luaL_dostring(L, "f = lb.basic_call"))
			lua_error(L);

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
		lua_State* L = luaL_newstate();
		lua_atpanic(L, atpanic);

		luaopen_lb(L);
		if (luaL_dostring(L, "b = lb.basic()"))
			lua_error(L);

		auto code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			if (luaL_dostring(L, code.c_str()))
				lua_error(L);
		});
	}

	void swig_member_variable(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, atpanic);

		luaopen_lb(L);
		if(luaL_dostring(L, "b = lb.basic()"))
			lua_error(L);
		
		auto code = repeated_code("b.var = i\nx = b.var");
		meter.measure([&]() {
			if (luaL_dostring(L, code.c_str()))
				lua_error(L);
		});
	}

	void swig_stateful_function_object_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

	void swig_multi_return_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

	void swig_virtual_cxx_function_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

	void swig_multi_get_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

	void swig_return_userdata(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}


}
