#include "lua_bench.hpp"
#include "basic.hpp"
#include <sol.hpp>

namespace lb {

	inline int atpanic(lua_State* L) {
		const char* message = lua_tostring(L, -1);
		std::string err = message ? message : "An unexpected error occurred and forced the lua state to call atpanic";
		throw std::runtime_error(err);
	}

	void sol_global_string_get_measure(nonius::chronometer& meter) {
		sol::state lua;
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

	void sol_global_string_set_measure(nonius::chronometer& meter) {
		sol::state lua(atpanic);
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua.set("value", i);
			}
		});
	}

	void sol_table_get_measure(nonius::chronometer& meter) {
		sol::state lua(atpanic);
		lua.create_table("warble", 0, 0, "value", 24);
		sol::table t = lua["warble"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = t["value"];
				x += v;
			}
			return x;
		});
	}

	void sol_table_set_measure(nonius::chronometer& meter) {
		sol::state lua(atpanic);
		lua.create_table("value", 0, 0);
		sol::table x = lua["value"];
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				x.set("warble", i);
		});
	}

	void sol_chained_get_measure(nonius::chronometer& meter) {
		sol::state lua(atpanic);
		lua.create_table("ulahibe", 0, 0, "warble", lua.create_table(0, 0, "value", 24));
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["ulahibe"]["warble"]["value"];
				x += v;
			}
			return x;
		});
	}

	void sol_chained_set_measure(nonius::chronometer& meter) {
		sol::state lua(atpanic);
		lua.create_table("ulahibe", 0, 0, "warble", lua.create_table(0, 0, "value", 24));
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				lua["ulahibe"]["warble"]["value"] = i;
		});
	}

	void sol_c_function_measure(nonius::chronometer& meter) {
		sol::state lua(atpanic);
		lua.set_function("f", basic_call);
		std::string code = repeated_code("f(i)");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_lua_function_measure(nonius::chronometer& meter) {
		sol::state lua(atpanic);
		lua.script(R"(function f (i)
			return i;
		end)");
		sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void sol_c_through_lua_function_measure(nonius::chronometer& meter) {
		sol::state lua(atpanic);
		lua.set_function("f", sol::c_call<decltype(&basic_call), &basic_call>);
		sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void sol_member_function_call(nonius::chronometer& meter) {
		sol::state lua(atpanic);
		lua.new_usertype<basic>("basic",
			"get", sol::c_call<decltype(&basic::get), &basic::get>,
			"set", sol::c_call<decltype(&basic::set), &basic::set>
		);
		lua.script("b = basic:new()");
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_member_variable(nonius::chronometer& meter) {
		sol::state lua(atpanic);
		lua.new_usertype<basic>("basic",
			"var", &basic::var
		);
		lua.script("b = basic:new()");
		std::string code = repeated_code("b.var = i\nx = b.var");
		meter.measure([&]() {
			lua.script(code);
		});
	}

}
