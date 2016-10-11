#include "lua bench.hpp"
#include <selene.h>
#include "basic_lua.hpp"

namespace lb {

	void selene_global_string_get_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua.HandleExceptionsWith(selene_panic_throw);
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
		lua.HandleExceptionsWith(selene_panic_throw);
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua["value"] = i;
			}
		});
	}

	void selene_chained_get_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua.HandleExceptionsWith(selene_panic_throw);
		
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
		lua.HandleExceptionsWith(selene_panic_throw);
		
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua["ulahibe"]["warble"]["value"] = i;
			}
		});
	}

	void selene_table_get_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua.HandleExceptionsWith(selene_panic_throw);
		
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
		lua.HandleExceptionsWith(selene_panic_throw);
		
		auto t = lua["value"];
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				t["warble"] = i;
			}
		});
	}

	void selene_c_function_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua.HandleExceptionsWith(selene_panic_throw);

		lua["f"] = basic_call;
		auto code = repeated_code("f(i)");
		meter.measure([&]() {
			lua(code.c_str());
		});
	}

	void selene_lua_function_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua.HandleExceptionsWith(selene_panic_throw);

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
		lua.HandleExceptionsWith(selene_panic_throw);

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

	void selene_member_function_call_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua.HandleExceptionsWith(selene_panic_throw);

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

	void selene_userdata_variable_access_measure(nonius::chronometer& meter) {
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
		sel::State lua;
		lua.HandleExceptionsWith(selene_panic_throw);

		lua["f"] = basic_stateful();
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

	void selene_multi_return_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua.HandleExceptionsWith(selene_panic_throw);

		lua["f"] = basic_multi_return;
		sel::function<std::tuple<int, int>(int)> f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				std::tuple<int, int> v = f(i);
				x += std::get<0>(v);
				x += std::get<1>(v);
			}
			return x;
		});
	}

	void selene_base_derived_measure(nonius::chronometer& meter) {
		// Explicitly unsupported,
		// as stated by the Readme for inheritance
		meter.measure([&]() {
		});
	}

	void selene_optional_measure(nonius::chronometer& meter) {
		// Not supported:
		// there does not seem to be a way to check if a key exists in Selene
		// after being set
		meter.measure([&]() {
		});
	}

	void selene_return_userdata_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua.HandleExceptionsWith(selene_panic_throw);

		lua["basic"].SetClass<basic>();
		lua["f"] = basic_return;
		auto code = repeated_code("b = f(i)");
		meter.measure([&]() {
			lua(code.c_str());
		});
	}

	void selene_implicit_inheritance_call_measure(nonius::chronometer& meter) {
		// UNSUPPORTED
		// The below code doesn't work and calls panic
		sel::State lua;
		lua.HandleExceptionsWith(selene_panic_throw);

		lua["complex_base_a"].SetClass<complex_base_a>(
			"a", &complex_base_a::a,
			"a_func", &complex_base_a::a_func
		);
		lua["complex_base_b"].SetClass<complex_base_b>(
			"b", &complex_base_b::b,
			"b_func", &complex_base_b::b_func
		);
		lua["complex_ab"].SetClass<complex_ab>(
			"ab", &complex_ab::ab,
			"ab_func", &complex_ab::ab_func
		);

		lua("b = complex_ab.new()");

		auto code = repeated_code("b:b_func()");
		meter.measure([&]() {
			lua(code.c_str());
		});
	}

}
