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
		lua.registerMember("var0", &basic::var);
		lua.registerMember("var1", &basic::var);
		lua.registerMember("var2", &basic::var);
		lua.registerMember("var3", &basic::var);
		lua.registerMember("var4", &basic::var);
		lua.writeVariable("b", basic());
		auto code = repeated_code(
			"b.var0 = i\n"
			"x = b.var0\n"
			"b.var4 = i\n"
			"x = b.var4\n"
			"b.var1 = i\n"
			"x = b.var1\n"
			"b.var3 = i\n"
			"x = b.var3\n"
			"b.var2 = i\n"
			"x = b.var2\n"
		);
		meter.measure([&]() {
			lua.executeCode(code.c_str());
		});
	}

	void luawrapper_member_variable_complex_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.registerMember("var0", &basic::var);
		lua.registerMember("var1", &basic::var);
		lua.registerMember("var2", &basic::var);
		lua.registerMember("var3", &basic::var);
		lua.registerMember("var4", &basic::var);
		lua.registerMember("var5", &basic::var);
		lua.registerMember("var6", &basic::var);
		lua.registerMember("var7", &basic::var);
		lua.registerMember("var8", &basic::var);
		lua.registerMember("var9", &basic::var);
		lua.registerMember("var10", &basic::var);
		lua.registerMember("var11", &basic::var);
		lua.registerMember("var12", &basic::var);
		lua.registerMember("var13", &basic::var);
		lua.registerMember("var14", &basic::var);
		lua.registerMember("var15", &basic::var);
		lua.registerMember("var16", &basic::var);
		lua.registerMember("var17", &basic::var);
		lua.registerMember("var18", &basic::var);
		lua.registerMember("var19", &basic::var);
		lua.registerMember("var20", &basic::var);
		lua.registerMember("var21", &basic::var);
		lua.registerMember("var22", &basic::var);
		lua.registerMember("var23", &basic::var);
		lua.registerMember("var24", &basic::var);
		lua.registerMember("var25", &basic::var);
		lua.registerMember("var26", &basic::var);
		lua.registerMember("var27", &basic::var);
		lua.registerMember("var28", &basic::var);
		lua.registerMember("var29", &basic::var);
		lua.registerMember("var30", &basic::var);
		lua.registerMember("var31", &basic::var);
		lua.registerMember("var32", &basic::var);
		lua.registerMember("var33", &basic::var);
		lua.registerMember("var34", &basic::var);
		lua.registerMember("var35", &basic::var);
		lua.registerMember("var36", &basic::var);
		lua.registerMember("var37", &basic::var);
		lua.registerMember("var38", &basic::var);
		lua.registerMember("var39", &basic::var);
		lua.registerMember("var40", &basic::var);
		lua.registerMember("var41", &basic::var);
		lua.registerMember("var42", &basic::var);
		lua.registerMember("var43", &basic::var);
		lua.registerMember("var44", &basic::var);
		lua.registerMember("var45", &basic::var);
		lua.registerMember("var46", &basic::var);
		lua.registerMember("var47", &basic::var);
		lua.registerMember("var48", &basic::var);
		lua.registerMember("var49", &basic::var);
		lua.writeVariable("b", basic());

		auto code = repeated_code(
			"b.var0 = i\nx = b.var0\n"
			"b.var49 = i\nx = b.var49\n"
			"b.var2 = i\nx = b.var2\n"
			"b.var47 = i\nx = b.var47\n"
			"b.var4 = i\nx = b.var4\n"
			"b.var45 = i\nx = b.var45\n"
			"b.var6 = i\nx = b.var6\n"
			"b.var43 = i\nx = b.var43\n"
			"b.var8 = i\nx = b.var8\n"
			"b.var41 = i\nx = b.var41\n"
			"b.var10 = i\nx = b.var10\n"
			"b.var39 = i\nx = b.var39\n"
			"b.var12 = i\nx = b.var12\n"
			"b.var37 = i\nx = b.var37\n"
			"b.var14 = i\nx = b.var14\n"
			"b.var35 = i\nx = b.var35\n"
			"b.var16 = i\nx = b.var16\n"
			"b.var33 = i\nx = b.var33\n"
			"b.var18 = i\nx = b.var18\n"
			"b.var31 = i\nx = b.var31\n"
			"b.var20 = i\nx = b.var20\n"
			"b.var29 = i\nx = b.var29\n"
			"b.var22 = i\nx = b.var22\n"
			"b.var27 = i\nx = b.var27\n"
			"b.var24 = i\nx = b.var24\n"
			"b.var25 = i\nx = b.var25\n"
			"b.var26 = i\nx = b.var26\n"
			"b.var23 = i\nx = b.var23\n"
			"b.var28 = i\nx = b.var28\n"
			"b.var21 = i\nx = b.var21\n"
			"b.var30 = i\nx = b.var30\n"
			"b.var19 = i\nx = b.var19\n"
			"b.var32 = i\nx = b.var32\n"
			"b.var17 = i\nx = b.var17\n"
			"b.var34 = i\nx = b.var34\n"
			"b.var15 = i\nx = b.var15\n"
			"b.var36 = i\nx = b.var36\n"
			"b.var13 = i\nx = b.var13\n"
			"b.var38 = i\nx = b.var38\n"
			"b.var11 = i\nx = b.var11\n"
			"b.var40 = i\nx = b.var40\n"
			"b.var9 = i\nx = b.var9\n"
			"b.var42 = i\nx = b.var42\n"
			"b.var7 = i\nx = b.var7\n"
			"b.var44 = i\nx = b.var44\n"
			"b.var5 = i\nx = b.var5\n"
			"b.var46 = i\nx = b.var46\n"
			"b.var3 = i\nx = b.var3\n"
			"b.var48 = i\nx = b.var48\n"
			"b.var1 = i\nx = b.var1\n"
		);
		meter.measure([&]() {
			lua.executeCode(code.c_str());
		});
	}

	void luawrapper_member_variable_last_measure(nonius::chronometer& meter) {
		LuaContext lua;
		lua.registerMember("var0", &basic::var);
		lua.registerMember("var1", &basic::var);
		lua.registerMember("var2", &basic::var);
		lua.registerMember("var3", &basic::var);
		lua.registerMember("var4", &basic::var);
		lua.registerMember("var5", &basic::var);
		lua.registerMember("var6", &basic::var);
		lua.registerMember("var7", &basic::var);
		lua.registerMember("var8", &basic::var);
		lua.registerMember("var9", &basic::var);
		lua.registerMember("var10", &basic::var);
		lua.registerMember("var11", &basic::var);
		lua.registerMember("var12", &basic::var);
		lua.registerMember("var13", &basic::var);
		lua.registerMember("var14", &basic::var);
		lua.registerMember("var15", &basic::var);
		lua.registerMember("var16", &basic::var);
		lua.registerMember("var17", &basic::var);
		lua.registerMember("var18", &basic::var);
		lua.registerMember("var19", &basic::var);
		lua.registerMember("var20", &basic::var);
		lua.registerMember("var21", &basic::var);
		lua.registerMember("var22", &basic::var);
		lua.registerMember("var23", &basic::var);
		lua.registerMember("var24", &basic::var);
		lua.registerMember("var25", &basic::var);
		lua.registerMember("var26", &basic::var);
		lua.registerMember("var27", &basic::var);
		lua.registerMember("var28", &basic::var);
		lua.registerMember("var29", &basic::var);
		lua.registerMember("var30", &basic::var);
		lua.registerMember("var31", &basic::var);
		lua.registerMember("var32", &basic::var);
		lua.registerMember("var33", &basic::var);
		lua.registerMember("var34", &basic::var);
		lua.registerMember("var35", &basic::var);
		lua.registerMember("var36", &basic::var);
		lua.registerMember("var37", &basic::var);
		lua.registerMember("var38", &basic::var);
		lua.registerMember("var39", &basic::var);
		lua.registerMember("var40", &basic::var);
		lua.registerMember("var41", &basic::var);
		lua.registerMember("var42", &basic::var);
		lua.registerMember("var43", &basic::var);
		lua.registerMember("var44", &basic::var);
		lua.registerMember("var45", &basic::var);
		lua.registerMember("var46", &basic::var);
		lua.registerMember("var47", &basic::var);
		lua.registerMember("var48", &basic::var);
		lua.registerMember("var49", &basic::var);
		lua.writeVariable("b", basic());

		auto code = repeated_code(
			"b.var49 = i\nx = b.var49\n"
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
