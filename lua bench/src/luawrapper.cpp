#include "lua bench.hpp"
#include "basic_lua.hpp"
#include <LuaContext.hpp>

namespace lb {

	void luawrapper_global_string_get_measure(nonius::chronometer& meter) {
		LuaContext lua;

		lua.writeVariable("value", 24);
		meter.measure([&lua]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua.readVariable<int>("value");
				x += v;
			}
			return x;
		});
	}

	void luawrapper_global_string_set_measure(nonius::chronometer& meter) {
		LuaContext lua;
		meter.measure([&lua]() {
			for (int i = 0; i < repetition; ++i) {
				lua.writeVariable("value", 24);
			}
		});
	}

	void luawrapper_chained_get_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.writeVariable("ulahibe", 
			std::map<std::string, std::map<std::string, int>> {
				{ "warble", 
					std::map<std::string, int>{ 
						{ "value", 24 }
					} 
				},
			}
		);
		meter.measure([&lua]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua.readVariable<int>("ulahibe", "warble", "value");
				x += v;
			}
			return x;
		});
	}

	void luawrapper_chained_set_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.writeVariable("ulahibe", 
			std::map<std::string, std::map<std::string, int>> {
				{ "warble", 
					std::map<std::string, int>{ 
						{ "value", 24 }
					} 
				},
			}
		);
		meter.measure([&lua]() {
			for (int i = 0; i < repetition; ++i) {
				lua.writeVariable("ulahibe", "warble", "value", i);
			}
		});
	}

	void luawrapper_table_get_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.writeVariable("warble",
			std::map<std::string, int> {
				{ "value", 24 }
		}
		);
		meter.measure([&lua]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua.readVariable<int>("warble", "value");
				x += v;
			}
			return x;
		});
	}

	void luawrapper_table_set_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.writeVariable("warble",
			std::map<std::string, int> {
				{ "value", 24 }
		}
		);
		meter.measure([&lua]() {
			for (int i = 0; i < repetition; ++i) {
				lua.writeVariable("warble", "value", i);
			}
		});
	}

	void luawrapper_c_function_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.writeFunction("f", &basic_call);
		auto code = repeated_code("f(i)");
		meter.measure([&]() {
			lua.executeCode(code);
		});
	}

	void luawrapper_lua_function_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.executeCode(R"(function f (i)
			return i;
		end)");
		auto f = lua.readVariable<std::function<int(int)>>("f");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void luawrapper_c_through_lua_function_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.writeFunction("f", &basic_call);
		auto f = lua.readVariable<std::function<int(int)>>("f");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void luawrapper_member_function_call_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.registerFunction<int (basic::*)()>("get", [](basic& b) { return b.get(); });
		lua.registerFunction<void (basic::*)(int)>("set", [](basic& b, int num) { b.set(num); });
		lua.writeVariable("b", basic());
		auto code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			lua.executeCode(code.c_str());
		});
	}

	void luawrapper_member_variable_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.registerMember("var", &basic::var);
		lua.writeVariable("b", basic());
		auto code = repeated_code("b.var = i\nx = b.var");
		meter.measure([&]() {
			lua.executeCode(code.c_str());
		});
	}


	void luawrapper_stateful_function_object_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.writeFunction("f", basic_stateful());
		auto f = lua.readVariable<std::function<int(int)>>("f");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void luawrapper_multi_return_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.writeFunction("f", &basic_multi_return);
		auto f = lua.readVariable<std::function<std::tuple<int, int>(int)>>("f");
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

	void luawrapper_base_derived_measure(nonius::chronometer& meter) {
		// Unsupported:
		// Errors directly on cast and there's no base/derived template plug
		LuaContext lua;
		complex_ab ab;
		lua.writeVariable("b", &ab);
		{
			complex_base_a& va = lua.readVariable<complex_base_a>("b");
			complex_base_b& vb = lua.readVariable<complex_base_b>("b");
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
				complex_base_a& va = lua.readVariable<complex_base_a>("b");
				complex_base_b& vb = lua.readVariable<complex_base_b>("b");
				x += va.a_func();
				x += vb.b_func();
			}
			return x;
		});
	}

	void luawrapper_return_userdata_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.writeFunction("f", &basic_return);
		auto code = repeated_code("b = f(i)");
		meter.measure([&]() {
			lua.executeCode(code.c_str());
		});
	}

	void luawrapper_optional_measure(nonius::chronometer& meter) {
		// Unsupported
		meter.measure([&]() {
		});
	}

}
