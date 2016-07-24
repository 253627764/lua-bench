#include "luwra.hpp"
#include "basic.hpp"
#include "basic_lua.hpp"
#include "lua bench.hpp"

namespace lb {

	void luwra_global_string_get_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua_atpanic(lua, panic_throw);

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
		lua_atpanic(lua, panic_throw);

		meter.measure([&lua]() {
			for (int i = 0; i < repetition; ++i) {
				lua["value"] = 24;
			}
		});
	}

	void luwra_chained_get_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua_atpanic(lua, panic_throw);

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
		lua_atpanic(lua, panic_throw);

		lua.runString("ulahibe={warble={value = 24}}");
		meter.measure([&lua]() {
			for (int i = 0; i < repetition; ++i) {
				lua["ulahibe"]["warble"]["value"] = i;
			}
		});
	}

	void luwra_table_get_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua_atpanic(lua, panic_throw);

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
		lua_atpanic(lua, panic_throw);

		lua.runString("warble={value = 24}");
		meter.measure([&lua]() {
			for (int i = 0; i < repetition; ++i) {
				lua["warble"]["value"] = i;
			}
		});
	}

	void luwra_c_function_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua_atpanic(lua, panic_throw);

		lua["f"] = LUWRA_WRAP(basic_call);
		auto code = repeated_code("f(i)");
		meter.measure([&]() {
			lua.runString(code.c_str());
		});
	}

	void luwra_lua_function_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua_atpanic(lua, panic_throw);

		lua.runString(R"(function f (i)
			return i;
		end)");
		lua_getglobal(lua, "f");
		luwra::Function<int> f(lua, -1);
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
		lua_pop(lua, 1);
	}

	void luwra_c_through_lua_function_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua_atpanic(lua, panic_throw);

		lua["f"] = LUWRA_WRAP(basic_call);
		
		// Since Luwra expects the referenced function to exist on a Lua stack before execution,
		// we have to push it manually. Luwra is way too minimal to work with Lua-native functions
		// outside the scope of a wrapped function.
		lua_getglobal(lua, "f");
		luwra::Function<int> f(lua , -1);
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
		lua_pop(lua, 1);
	}

	void luwra_member_function_call(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua_atpanic(lua, panic_throw);

		lua.registerUserType<basic()>(
			"basic",
			{
				LUWRA_MEMBER(basic, get),
				LUWRA_MEMBER(basic, set)
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
		lua_atpanic(lua, panic_throw);

		lua.registerMember("var", &basic::var);
		lua.writeVariable("b", basic());
		auto code = repeated_code("b.var = i\nx = b.var");
		meter.measure([&]() {
			lua.runString(code.c_str());
		});*/
		// Unsupported
	}

	void luwra_stateful_function_object_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua_atpanic(lua, panic_throw);
		
		lua.set("f", basic_stateful());
		luwra::Function<int> f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void luwra_multi_return_measure(nonius::chronometer& meter) {
		// std::tuple returns still not supported...
		// G R E A T
		luwra::StateWrapper lua;
		lua_atpanic(lua, panic_throw);
		
		lua.set("f", LUWRA_WRAP( basic_multi_return ));
		luwra::Function<std::tuple<int, int>> f = lua["f"];
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

	void luwra_base_derived_measure(nonius::chronometer& meter) {
		luwra::StateWrapper lua;
		lua_atpanic(lua, panic_throw);

		lua.registerUserType<complex_ab>();
		complex_ab ab;
		// Set and verify correctness
		lua.set("b", &ab);
		{
			complex_base_a& va = lua["b"].read<complex_base_a>();
			complex_base_b& vb = lua["b"].read<complex_base_b>();
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
				complex_base_a& va = lua["b"].read<complex_base_a>();
				complex_base_b& vb = lua["b"].read<complex_base_b>();
				x += va.a_func();
				x += vb.b_func();
			}
			return x;
		});
	}

}
