#include <sol.hpp>
#include "lua bench.hpp"
#include "basic.hpp"
#include "basic_lua.hpp"

namespace lb {

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
		sol::state lua(panic_throw);
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua.set("value", i);
			}
		});
	}

	void sol_table_get_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
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
		sol::state lua(panic_throw);
		lua.create_table("value", 0, 0);
		sol::table x = lua["value"];
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				x.set("warble", i);
		});
	}

	void sol_chained_get_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
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
		sol::state lua(panic_throw);
		lua.create_table("ulahibe", 0, 0, "warble", lua.create_table(0, 0, "value", 24));
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				lua["ulahibe"]["warble"]["value"] = i;
		});
	}

	void sol_c_function_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.set_function("f", basic_call);
		std::string code = repeated_code("f(i)");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_lua_function_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
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
		sol::state lua(panic_throw);
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
		sol::state lua(panic_throw);
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
		sol::state lua(panic_throw);
		lua.new_usertype<basic>("basic",
			"var", &basic::var
		);
		lua.script("b = basic:new()");
		std::string code = repeated_code("b.var = i\nx = b.var");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void sol_stateful_function_object_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		int storage = 0;
		lua.set_function("f", basic_stateful());
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

	void sol_multi_return_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.set_function("f", basic_multi_return);
		sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				std::tuple<int, int> v = f(i);
				x += static_cast<int>(std::get<0>(v));
				x += static_cast<int>(std::get<1>(v));
			}
			return x;
		});
	}

	void sol_base_derived_measure(nonius::chronometer& meter) {
		sol::state lua(panic_throw);
		lua.new_usertype<complex_ab>("complex_ab",
			"a_func", &complex_ab::a_func,
			"b_func", &complex_ab::b_func,
			"ab_func", &complex_ab::ab_func,
			sol::base_classes, sol::bases<complex_base_a, complex_base_b>()
		);
		complex_ab ab;
		// Set and verify correctness
		lua.set("b", &ab);
		{
			complex_base_a& va = lua["b"];
			complex_base_b& vb = lua["b"];
			if (va.a_func() != ab.a_func() || va.a != ab.a) {
				throw std::logic_error("proper base class casting not provided: failing test");
			}
			if (vb.b_func() != ab.b_func() || vb.b != ab.b) {
				throw std::logic_error("proper base class casting not provided: failing test");
			}
		}
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				complex_base_a& va = lua["b"];
				complex_base_b& vb = lua["b"];
				x += va.a_func();
				x += vb.b_func();
			}
			return x;
		});
	}


}
