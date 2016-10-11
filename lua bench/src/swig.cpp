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

		auto code = repeated_code(member_function_call_code);
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void swig_userdata_variable_access_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "b = lb.basic()");
		
		auto code = repeated_code(
			userdata_variable_access_code
		);
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void swig_userdata_variable_access_complex_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "b = lb.basic_large()");

		auto code = repeated_code(
			userdata_variable_access_large_code
		);
		meter.measure([&]() {
			lua_do_or_die(L, code.c_str());
		});
	}

	void swig_userdata_variable_access_last_measure(nonius::chronometer& meter) {
		lua_State* L = luaL_newstate();
		lua_atpanic(L, panic_throw);

		luaopen_lb(L);
		lua_do_or_die(L, "b = lb.basic_large()");

		auto code = repeated_code(
			userdata_variable_access_large_last_code
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
