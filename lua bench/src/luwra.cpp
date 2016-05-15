#include "luwra.hpp"
#include "basic.hpp"
#include "lua_bench.hpp"

namespace lb {

	void luwra_global_string_get_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua["value"] = 24;
		meter.measure([&lua]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["value"];
				x += v;
			}
			return x;
		});
	}

	void luwra_global_string_set_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		meter.measure([&lua]() {
			for (int i = 0; i < repetition; ++i) {
				lua["value"] = 24;
			}
		});
	}

	void luwra_chained_get_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua.runString("ulahibe={warble={value = 24}}");
		meter.measure([&lua]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["ulahibe"]["warble"]["value"];
				x += v;
			}
			return x;
		});
	}

	void luwra_chained_set_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua.runString("ulahibe={warble={value = 24}}");
		meter.measure([&lua]() {
			for (int i = 0; i < repetition; ++i) {
				lua["ulahibe"]["warble"]["value"] = i;
			}
		});
	}

	void luwra_table_get_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua.runString("warble={value = 24}");
		meter.measure([&lua]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["warble"]["value"];
				x += v;
			}
			return x;
		});
	}

	void luwra_table_set_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua.runString("warble={value = 24}");
		meter.measure([&lua]() {
			for (int i = 0; i < repetition; ++i) {
				lua["warble"]["value"] = i;
			}
		});
	}

	void luwra_c_function_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua.set("f", &basic_call);
		auto code = repeated_code("f(i)");
		meter.measure([&]() {
			lua.runString(code);
		});
	}

	void luwra_lua_function_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua.runString(R"(function f (i)
			return i;
		end)");
		auto f = lua.get<std::function<int(int)>>("f");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void luwra_c_through_lua_function_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua.set("f", &basic_call);
		auto f = lua.get<std::function<int(int)>>("f");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void luwra_member_function_call(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua.registerUserType<basic>(
			"basic",
			{
				LUWRA_MEMBER(basic::get, get),
				LUWRA_MEMBER(basic::set, set)
			}
		);
		lua.runString("b = basic()");
		auto code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			lua.runString(code.c_str());
		});
	}

	void luwra_member_variable(nonius::chronometer& meter) {
		/*luwra::StateWrapper lua;
		lua.registerMember("var", &basic::var);
		lua.writeVariable("b", basic());
		auto code = repeated_code("b.var = i\nx = b.var");
		meter.measure([&]() {
			lua.runString(code.c_str());
		});*/
		// Unsupported
	}

}
