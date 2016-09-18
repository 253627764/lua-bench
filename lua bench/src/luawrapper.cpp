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
		auto code = repeated_code(lb::member_function_call_code);
		meter.measure([&]() {
			lua.executeCode(code.c_str());
		});
	}

	void luawrapper_member_variable_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.registerMember("var", &basic::var);
		lua.registerMember("var0", &basic::var0);
		lua.registerMember("var1", &basic::var1);
		lua.registerMember("var2", &basic::var2);
		lua.registerMember("var3", &basic::var3);
		lua.registerMember("var4", &basic::var4);
		lua.writeVariable("b", basic());
		auto code = repeated_code(
			member_variable_code
		);
		meter.measure([&]() {
			lua.executeCode(code.c_str());
		});
	}

	void luawrapper_member_variable_complex_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.registerMember("var", &basic_large::var);
		lua.registerMember("var0", &basic_large::var0);
		lua.registerMember("var1", &basic_large::var1);
		lua.registerMember("var2", &basic_large::var2);
		lua.registerMember("var3", &basic_large::var3);
		lua.registerMember("var4", &basic_large::var4);
		lua.registerMember("var5", &basic_large::var5);
		lua.registerMember("var6", &basic_large::var6);
		lua.registerMember("var7", &basic_large::var7);
		lua.registerMember("var8", &basic_large::var8);
		lua.registerMember("var9", &basic_large::var9);
		lua.registerMember("var10", &basic_large::var10);
		lua.registerMember("var11", &basic_large::var11);
		lua.registerMember("var12", &basic_large::var12);
		lua.registerMember("var13", &basic_large::var13);
		lua.registerMember("var14", &basic_large::var14);
		lua.registerMember("var15", &basic_large::var15);
		lua.registerMember("var16", &basic_large::var16);
		lua.registerMember("var17", &basic_large::var17);
		lua.registerMember("var18", &basic_large::var18);
		lua.registerMember("var19", &basic_large::var19);
		lua.registerMember("var20", &basic_large::var20);
		lua.registerMember("var21", &basic_large::var21);
		lua.registerMember("var22", &basic_large::var22);
		lua.registerMember("var23", &basic_large::var23);
		lua.registerMember("var24", &basic_large::var24);
		lua.registerMember("var25", &basic_large::var25);
		lua.registerMember("var26", &basic_large::var26);
		lua.registerMember("var27", &basic_large::var27);
		lua.registerMember("var28", &basic_large::var28);
		lua.registerMember("var29", &basic_large::var29);
		lua.registerMember("var30", &basic_large::var30);
		lua.registerMember("var31", &basic_large::var31);
		lua.registerMember("var32", &basic_large::var32);
		lua.registerMember("var33", &basic_large::var33);
		lua.registerMember("var34", &basic_large::var34);
		lua.registerMember("var35", &basic_large::var35);
		lua.registerMember("var36", &basic_large::var36);
		lua.registerMember("var37", &basic_large::var37);
		lua.registerMember("var38", &basic_large::var38);
		lua.registerMember("var39", &basic_large::var39);
		lua.registerMember("var40", &basic_large::var40);
		lua.registerMember("var41", &basic_large::var41);
		lua.registerMember("var42", &basic_large::var42);
		lua.registerMember("var43", &basic_large::var43);
		lua.registerMember("var44", &basic_large::var44);
		lua.registerMember("var45", &basic_large::var45);
		lua.registerMember("var46", &basic_large::var46);
		lua.registerMember("var47", &basic_large::var47);
		lua.registerMember("var48", &basic_large::var48);
		lua.registerMember("var49", &basic_large::var49);
		lua.writeVariable("b", basic_large());

		auto code = repeated_code(
			member_variable_large_code
		);
		meter.measure([&]() {
			lua.executeCode(code.c_str());
		});
	}

	void luawrapper_member_variable_last_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.registerMember("var", &basic_large::var);
		lua.registerMember("var0", &basic_large::var0);
		lua.registerMember("var1", &basic_large::var1);
		lua.registerMember("var2", &basic_large::var2);
		lua.registerMember("var3", &basic_large::var3);
		lua.registerMember("var4", &basic_large::var4);
		lua.registerMember("var5", &basic_large::var5);
		lua.registerMember("var6", &basic_large::var6);
		lua.registerMember("var7", &basic_large::var7);
		lua.registerMember("var8", &basic_large::var8);
		lua.registerMember("var9", &basic_large::var9);
		lua.registerMember("var10", &basic_large::var10);
		lua.registerMember("var11", &basic_large::var11);
		lua.registerMember("var12", &basic_large::var12);
		lua.registerMember("var13", &basic_large::var13);
		lua.registerMember("var14", &basic_large::var14);
		lua.registerMember("var15", &basic_large::var15);
		lua.registerMember("var16", &basic_large::var16);
		lua.registerMember("var17", &basic_large::var17);
		lua.registerMember("var18", &basic_large::var18);
		lua.registerMember("var19", &basic_large::var19);
		lua.registerMember("var20", &basic_large::var20);
		lua.registerMember("var21", &basic_large::var21);
		lua.registerMember("var22", &basic_large::var22);
		lua.registerMember("var23", &basic_large::var23);
		lua.registerMember("var24", &basic_large::var24);
		lua.registerMember("var25", &basic_large::var25);
		lua.registerMember("var26", &basic_large::var26);
		lua.registerMember("var27", &basic_large::var27);
		lua.registerMember("var28", &basic_large::var28);
		lua.registerMember("var29", &basic_large::var29);
		lua.registerMember("var30", &basic_large::var30);
		lua.registerMember("var31", &basic_large::var31);
		lua.registerMember("var32", &basic_large::var32);
		lua.registerMember("var33", &basic_large::var33);
		lua.registerMember("var34", &basic_large::var34);
		lua.registerMember("var35", &basic_large::var35);
		lua.registerMember("var36", &basic_large::var36);
		lua.registerMember("var37", &basic_large::var37);
		lua.registerMember("var38", &basic_large::var38);
		lua.registerMember("var39", &basic_large::var39);
		lua.registerMember("var40", &basic_large::var40);
		lua.registerMember("var41", &basic_large::var41);
		lua.registerMember("var42", &basic_large::var42);
		lua.registerMember("var43", &basic_large::var43);
		lua.registerMember("var44", &basic_large::var44);
		lua.registerMember("var45", &basic_large::var45);
		lua.registerMember("var46", &basic_large::var46);
		lua.registerMember("var47", &basic_large::var47);
		lua.registerMember("var48", &basic_large::var48);
		lua.registerMember("var49", &basic_large::var49);
		lua.writeVariable("b", basic_large());

		auto code = repeated_code(
			member_variable_large_last_code
		);
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

	void luawrapper_implicit_inheritance_call_measure(nonius::chronometer& meter) {
		// Unsupported
		meter.measure([&]() {
		});
	}

}
