#include "lua_bench.hpp"
#include <kaguya/kaguya.hpp>

namespace lb {

	void kaguya_global_string_get_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["value"] = 24;
		meter.measure([&](int i) {
			int x = lua["value"];
			return x;
		});
	}

	void kaguya_global_string_set_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		meter.measure([&](int i) {
			lua["value"] = 24;
		});
	}

	void kaguya_table_get_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.globalTable().
		lua.create_table("value", 0, 0, "warble", 24);
		kaguya::table t = lua["value"];
		meter.measure([&](int i) {
			int x = t["warble"];
			return x;
		});
	}

	void kaguya_table_set_measure(nonius::chronometer& meter) {
		kaguya::state lua;
		lua.create_table("value", 0, 0);
		kaguya::table x = lua["value"];
		meter.measure([&](int i) {
			x.set("warble", 24);
		});
	}

	void kaguya_chained_get_measure(nonius::chronometer& meter) {
		kaguya::state lua;
		lua.create_table("value", 0, 0, "warble", lua.create_table(0, 0, "ulahibe", 24));
		meter.measure([&](int i) {
			int x = lua["value"]["warble"]["ulahibe"];
			return x;
		});
	}

	void kaguya_chained_set_measure(nonius::chronometer& meter) {
		kaguya::state lua;
		lua.create_table("value", 0, 0, "warble", lua.create_table(0, 0, "ulahibe", 24));
		meter.measure([&](int i) {
			lua["value"]["warble"]["ulahibe"] = 24;
		});
	}

	void kaguya_c_function_measure(nonius::chronometer& meter) {
		kaguya::state lua;
		lua.set_function("f", basic_call);
		lua["run"] = 0;
		meter.measure([&](int i) {
			lua.script(R"(
				f(run)
				run += 1
			)");
		});
	}

	void kaguya_lua_function_measure(nonius::chronometer& meter) {
		kaguya::state lua;
		lua.script(R"(function f (i)
			return i;
		end)");
		kaguya::function f = lua["f"];
		meter.measure([&](int i) {
			int x = f(i);
			return x;
		});
	}

	void kaguya_c_through_lua_function_measure(nonius::chronometer& meter) {
		kaguya::state lua;
		lua.set_function("f", basic_call);
		kaguya::function f = lua["f"];
		meter.measure([&](int i) {
			int x = f(i);
			return x;
		});
	}

	void kaguya_member_function_call(nonius::chronometer& meter) {
		kaguya::state lua;
		lua.new_usertype<basic>("basic",
			"get", &basic::get,
			"set", &basic::set);
		meter.measure([&](int i) {
			lua.script("b:set(20)\nb:get()");
		});
	}

	void kaguya_member_variable_set(nonius::chronometer& meter) {
		kaguya::state lua;
		lua.new_usertype<basic>("basic",
			"var", &basic::var,
			"get", &basic::get,
			"set", &basic::set);
		lua.script("b = basic:new()");
		meter.measure([&](int i) {
			lua.script("b.var = 20");
		});
	}

	void kaguya_member_variable_get(nonius::chronometer& meter) {
		kaguya::state lua;
		lua.new_usertype<basic>("basic",
			"var", &basic::var);
		lua.script("b = basic:new()");
		meter.measure([&](int i) {
			lua.script("x = b.var");
		});
	}

}
