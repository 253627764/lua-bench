#include "lua_bench.hpp"
#include <kaguya/kaguya.hpp>

namespace lb {

	void kaguya_global_string_get_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["value"] = 24;
		meter.measure([&](int i) {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["value"];
				x += v;
			}
			return x;
		});
	}

	void kaguya_global_string_set_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		meter.measure([&](int i) {
			for (int i = 0; i < repetition; ++i) {
				lua["value"] = i;
			}
		});
	}

	void kaguya_table_get_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["value"] = kaguya::NewTable();
		lua["value"]["warble"] = 24;
		kaguya::LuaTable t = lua["value"];
		meter.measure([&](int i) {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = t["warble"];
				v += x;
			}
			return x;
		});
	}

	void kaguya_table_set_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["warble"] = kaguya::NewTable();
		kaguya::LuaTable t = lua["warble"];
		meter.measure([&](int i) {
			for (int i = 0; i < repetition; ++i) {
				t["value"] = i;
			}
		});
	}

	void kaguya_chained_get_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["ulahibe"] = kaguya::NewTable();
		lua["ulahibe"]["warble"] = kaguya::NewTable();
		lua["ulahibe"]["warble"]["value"] = 24;
		meter.measure([&](int i) {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["ulahibe"]["warble"]["value"];
				x += v;
			}
			return x;
		});
	}

	void kaguya_chained_set_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["ulahibe"] = kaguya::NewTable();
		lua["ulahibe"]["warble"] = kaguya::NewTable();
		lua["ulahibe"]["warble"]["value"] = 24;
		meter.measure([&](int i) {
			for (int i = 0; i < repetition; ++i) {
				lua["ulahibe"]["warble"]["value"] = i;
			}
		});
	}

	void kaguya_c_function_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["f"].setFunction(basic_call);
		auto code = repeated_code("f(i)");
		meter.measure([&](int i) {
			lua(code);
		});
	}

	void kaguya_lua_function_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua(R"(function f (i)
			return i;
		end)");
		kaguya::LuaFunction f = lua["f"];
		meter.measure([&](int i) {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void kaguya_c_through_lua_function_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["f"].setFunction(basic_call);
		kaguya::LuaFunction f = lua["f"];
		meter.measure([&](int i) {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
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
		lua("b = basic.new()");
		auto code = repeated_code("b:set(i) b:get()");
		meter.measure([&](int i) {
			lua(code);
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
		lua("b = basic.new()");
		auto code = repeated_code("b.var = i");
		meter.measure([&](int i) {
			lua(code);
		});
	}

	void kaguya_member_variable_get(nonius::chronometer& meter) {
		kaguya::State lua;
		lua["basic"].setClass<basic>(kaguya::ClassMetatable<basic>()
			.addConstructor()
			.addMember("var", &basic::var)
		);
		lua("b = basic:new()");
		auto code = repeated_code("x = b.var");
		meter.measure([&](int i) {
			lua(code);
		});
	}

}
