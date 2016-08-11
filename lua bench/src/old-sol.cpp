#include <old_sol.hpp>
#include "lua bench.hpp"
#include "basic.hpp"
#include "basic_lua.hpp"

namespace lb {

	void old_sol_global_string_get_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua["value"] = 24;
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua.get<int>("value");
				x += v;
			}
			return x;
		});
	}

	void old_sol_global_string_set_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua.set("value", i);
			}
		});
	}

	void old_sol_table_get_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.script("warble = { value = 24 }");
		old_sol::table t = lua["warble"].get<old_sol::table>();
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = t["value"];
				x += v;
			}
			return x;
		});
	}

	void old_sol_table_set_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.create_table("warble", 0, 0);
		old_sol::table x = lua["warble"].get<old_sol::table>();
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				x.set("value", i);
		});
	}

	void old_sol_chained_get_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.script("ulahibe = { warble = { value = 24 } }");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["ulahibe"].get<old_sol::table>()["warble"].get<old_sol::table>()["value"];
				x += v;
			}
			return x;
		});
	}

	void old_sol_chained_set_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.script("ulahibe = { warble = { value = 24 } }");
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				lua["ulahibe"].get<old_sol::table>()["warble"].get<old_sol::table>()["value"] = i;
		});
	}

	void old_sol_c_function_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.set_function("f", &basic_call);
		std::string code = repeated_code("f(i)");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void old_sol_lua_function_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.script(R"(function f (i)
			return i;
		end)");
		old_sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f.call<int>(i);
				x += v;
			}
			return x;
		});
	}

	void old_sol_c_through_lua_function_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.set_function("f", basic_call);
		old_sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f.call<int>(i);
				x += v;
			}
			return x;
		});
	}

	void old_sol_member_function_call_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.new_usertype<basic>("basic",
			"get", &basic::get,
			"set", &basic::set
		);
		lua.script("b = basic:new()");
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void old_sol_member_variable_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.new_usertype<basic>("basic",
			"var", &basic::var
		);
		lua.script("b = basic:new()");
		std::string code = repeated_code("b.var = i\nx = b.var");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void old_sol_stateful_function_object_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		int storage = 0;
		lua.set_function("f", basic_stateful());
		old_sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f.call<int>(i);
				x += v;
			}
			return x;
		});
	}

	void old_sol_multi_return_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.set_function("f", basic_multi_return);
		old_sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				std::tuple<int, int> v = f.call<int, int>(i);
				x += static_cast<int>(std::get<0>(v));
				x += static_cast<int>(std::get<1>(v));
			}
			return x;
		});
	}

	void old_sol_base_derived_measure(nonius::chronometer& meter) {
		/* Unsupported */
	}

	void old_sol_optional_measure(nonius::chronometer& meter) {
		/* Unsupported */
	}

	void old_sol_return_userdata_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.set_function("f", basic_return);
		std::string code = repeated_code("b = f(i)");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void old_sol_implicit_inheritance_call_measure(nonius::chronometer& meter) {
		/* Unsupported */
	}

}
