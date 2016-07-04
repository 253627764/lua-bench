#include "lua_bench.hpp"
#include "basic.hpp"
#include <selene.h>

namespace lb {

	void selene_global_string_get_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua["value"] = 24;
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["value"];
				x += v;
			}
			return x;
		});
	}

	void selene_global_string_set_measure(nonius::chronometer& meter) {
		sel::State lua;
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua["value"] = i;
			}
		});
	}

	void selene_chained_get_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua["ulahibe"]["warble"]["value"] = 24;
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["ulahibe"]["warble"]["value"];
				x += v;
			}
			return x;
		});
	}

	void selene_chained_set_measure(nonius::chronometer& meter) {
		sel::State lua;
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua["ulahibe"]["warble"]["value"] = i;
			}
		});
	}

	void selene_table_get_measure(nonius::chronometer& meter) {
		sel::State lua;
		auto t = lua["warble"];
		t["value"] = 24;
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = t["value"];
				x += v;
			}
			return x;
		});
	}

	void selene_table_set_measure(nonius::chronometer& meter) {
		sel::State lua;
		auto t = lua["value"];
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				t["warble"] = i;
			}
		});
	}

	void selene_c_function_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua["f"] = basic_call;
		auto code = repeated_code("f(i)");
		meter.measure([&]() {
			lua(code.c_str());
		});
	}

	void selene_lua_function_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua(R"(function f (i)
			return i;
		end)");
		sel::function<int(int)> f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void selene_c_through_lua_function_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua["f"] = basic_call;
		sel::function<int(int)> f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void selene_member_function_call(nonius::chronometer& meter) {
		sel::State lua;
		lua.HandleExceptionsPrintingToStdOut();
		lua["basic"].SetClass<basic>(
			"get", &basic::get,
			"set", &basic::set
		);
		lua("b = basic.new()");
		auto code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			lua(code.c_str());
		});
	}

	void selene_member_variable(nonius::chronometer& meter) {
		/*sel::State lua;
		lua["basic"].SetClass<basic>(
			"var", &basic::var,
			"set", &basic::set,
			"get", &basic::get
		);
		lua("b = basic.new()");
		auto code = repeated_code("b:set_var(i)\nx = b:var()");
		meter.measure([&]() {
			lua(code.c_str());
		});*/
		//meter.measure([&]() {
		//});
	}

	void selene_stateful_function_object_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

	void selene_multi_return_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

	void selene_virtual_cxx_function_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

	void selene_multi_get_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

	void selene_return_userdata(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}


}
