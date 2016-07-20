#include "lua_bench.hpp"
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

	void swig_member_function_call(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "b = lb.basic()");

		auto code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void swig_member_variable(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "b = lb.basic()");
		
		auto code = repeated_code("b.var = i\nx = b.var");
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
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

	void swig_base_derived_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

}
