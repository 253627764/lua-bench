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
		lua["value"] = kaguya::NewTable();
		lua["value"]["warble"] = 24;
		kaguya::LuaTable t = lua["value"];
		meter.measure([&](int i) {
			int x = t["warble"];
			return x;
		});
	}

	void kaguya_table_set_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["value"] = kaguya::NewTable();
		kaguya::LuaTable t = lua["value"];
		meter.measure([&](int i) {
			t["warble"] = 24;
		});
	}

	void kaguya_chained_get_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["ulahibe"] = kaguya::NewTable();
		lua["ulahibe"]["warble"] = kaguya::NewTable();
		lua["ulahibe"]["warble"]["value"] = 24;
		meter.measure([&](int i) {
			int x = lua["ulahibe"]["warble"]["value"];
			return x;
		});
	}

	void kaguya_chained_set_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["ulahibe"] = kaguya::NewTable();
		lua["ulahibe"]["warble"] = kaguya::NewTable();
		lua["ulahibe"]["warble"]["value"] = 24;
		meter.measure([&](int i) {
			lua["ulahibe"]["warble"]["value"] = 24;
		});
	}

	void kaguya_c_function_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["f"].setFunction(basic_call);
		lua["run"] = 0;
		meter.measure([&](int i) {
			lua(R"(
				f(run)
				run += 1
			)");
		});
	}

	void kaguya_lua_function_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua(R"(function f (i)
			return i;
		end)");
		kaguya::LuaFunction f = lua["f"];
		meter.measure([&](int i) {
			int x = f(i);
			return x;
		});
	}

	void kaguya_c_through_lua_function_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["f"].setFunction(basic_call);
		kaguya::LuaFunction f = lua["f"];
		meter.measure([&](int i) {
			int x = f(i);
			return x;
		});
	}

	void kaguya_member_function_call(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["basic"].setClass<basic>(kaguya::ClassMetatable<basic>()
			.addConstructor()
			.addMember("var", &basic::var)
			.addMemberFunction("get", &basic::get)
			.addMemberFunction("set", &basic::set)
			);
		lua("b = basic:new()");
		meter.measure([&](int i) {
			lua("b:set(20)\nb:get()");
		});
	}

	void kaguya_member_variable_set(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["basic"].setClass<basic>(kaguya::ClassMetatable<basic>()
			.addConstructor()
			.addMember("var", &basic::var)
			.addMemberFunction("get", &basic::get)
			.addMemberFunction("set", &basic::set)
			);
		lua("b = basic:new()");
		meter.measure([&](int i) {
			lua("b.var = 20");
		});
	}

	void kaguya_member_variable_get(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["basic"].setClass<basic>(kaguya::ClassMetatable<basic>()
			.addConstructor()
			.addMember("var", &basic::var)
		);
		lua("b = basic:new()");
		meter.measure([&](int i) {
			lua("x = b.var");
		});
	}

}
