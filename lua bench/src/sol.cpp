#include "lua_bench.hpp"
#include <sol.hpp>

namespace lb {

	void sol_global_string_get_measure(nonius::chronometer& meter) {
		sol::state lua;
		lua["value"] = 24;
		meter.measure([&](int i) {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua.get<int>("value");
				x += v;
			}
			return x;
		});
	}

	void sol_global_string_set_measure(nonius::chronometer& meter) {
		sol::state lua;
		meter.measure([&](int i) {
			for (int i = 0; i < repetition; ++i) {
				lua.set("value", i);
			}
		});
	}

	void sol_table_get_measure(nonius::chronometer& meter) {
		sol::state lua;
		lua.create_table("warble", 0, 0, "value", 24);
		sol::table t = lua["warble"];
		meter.measure([&](int i) {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = t["value"];
				x += v;
			}
			return x;
		});
	}

	void sol_table_set_measure(nonius::chronometer& meter) {
		sol::state lua;
		lua.create_table("value", 0, 0);
		sol::table x = lua["value"];
		meter.measure([&](int i) {
			for (int i = 0; i < repetition; ++i)
				x.set("warble", i);
		});
	}

	void sol_chained_get_measure(nonius::chronometer& meter) {
		sol::state lua;
		lua.create_table("ulahibe", 0, 0, "warble", lua.create_table(0, 0, "value", 24));
		meter.measure([&](int i) {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["ulahibe"]["warble"]["value"];
				x += v;
			}
			return x;
		});
	}

	void sol_chained_set_measure(nonius::chronometer& meter) {
		sol::state lua;
		lua.create_table("ulahibe", 0, 0, "warble", lua.create_table(0, 0, "value", 24));
		meter.measure([&](int i) {
			for (int i = 0; i < repetition; ++i)
				lua["ulahibe"]["warble"]["value"] = i;
		});
	}

	void sol_c_function_measure(nonius::chronometer& meter) {
		sol::state lua;
		lua.set_function("f", basic_call);
		std::string code = repeated_code("f(i)");
		meter.measure([&](int i) {
			lua.script(code);
		});
	}

	void sol_lua_function_measure(nonius::chronometer& meter) {
		sol::state lua;
		lua.script(R"(function f (i)
			return i;
		end)");
		sol::function f = lua["f"];
		meter.measure([&](int i) {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void sol_c_through_lua_function_measure(nonius::chronometer& meter) {
		sol::state lua;
		lua.set_function("f", basic_call);
		sol::function f = lua["f"];
		meter.measure([&](int i) {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void sol_member_function_call(nonius::chronometer& meter) {
		sol::state lua;
		lua.new_usertype<basic>("basic",
			"get", &basic::get,
			"set", &basic::set);
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&](int i) {
			lua.script(code);
		});
	}

	void sol_member_variable_set(nonius::chronometer& meter) {
		sol::state lua;
		lua.new_usertype<basic>("basic",
			"var", &basic::var,
			"get", &basic::get,
			"set", &basic::set);
		lua.script("b = basic:new()");
		std::string code = repeated_code("b.var = i");
		meter.measure([&](int i) {
			lua.script(code);
		});
	}

	void sol_member_variable_get(nonius::chronometer& meter) {
		sol::state lua;
		lua.new_usertype<basic>("basic",
			"var", &basic::var);
		lua.script("b = basic:new()");
		std::string code = repeated_code("x = b.var");
		meter.measure([&](int i) {
			lua.script(code);
		});
	}

}
