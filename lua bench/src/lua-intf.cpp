#include "lua bench.hpp"
#include "basic_lua.hpp"
#include <LuaIntf/LuaIntf.h>

namespace lb {

	void lua_intf_global_string_get_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		lua.doString("value = 24");
		meter.measure([&lua]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua.getGlobal<int>("value");
				x += v;
			}
			return x;
		});
	}

	void lua_intf_global_string_set_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		lua.doString("value = 24");
		meter.measure([&lua]() {
			for (int i = 0; i < repetition; ++i) {
				lua.setGlobal("value", i);
			}
		});
	}

	void lua_intf_chained_get_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		lua.doString("ulahibe = {warble = {value = 24}}");
		meter.measure([&lua]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua.getGlobal<int>("ulahibe.warble.value");
				x += v;
			}
			return x;
		});
	}

	void lua_intf_chained_set_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		lua.doString("ulahibe = {warble = {value = 24}}");
		meter.measure([&lua]() {
			for (int i = 0; i < repetition; ++i) {
				LuaIntf::LuaRef tu = lua.getGlobal("ulahibe")["warble"];
				tu.set("value", i);
			}
		});
	}

	void lua_intf_table_get_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		lua.doString("warble = {value = 24}");
		LuaIntf::LuaRef t = lua.getGlobal("warble");
		meter.measure([&t]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = t.get<int>("value");
				v += x;
			}
			return x;
		});
	}

	void lua_intf_table_set_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		lua.doString("warble = {value = 24}");
		LuaIntf::LuaRef t = lua.getGlobal("warble");
		meter.measure([&t]() {
			for (int i = 0; i < repetition; ++i) {
				t.set("value", i);
			}
		});
	}

	void lua_intf_c_function_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		lua.doString("function f(i) return i end");
		lua.setGlobal("f", basic_call);
		LuaIntf::LuaRef f = lua.getGlobal("f");
		std::string code = repeated_code("f(i)");
		meter.measure([&lua, &code]() {
			lua.doString(code.c_str());
		});
	}

	void lua_intf_lua_function_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		lua.doString("function f(i) return i end");
		LuaIntf::LuaRef f = lua.getGlobal("f");
		meter.measure([&f]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f.call<int>(i);
				x += v;
			}
			return x;
		});
	}

	void lua_intf_c_through_lua_function_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		lua.setGlobal("f", basic_call);
		LuaIntf::LuaRef f = lua.getGlobal("f");
		meter.measure([&f]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f.call<int>(i);
				x += v;
			}
			return x;
		});
	}

	void lua_intf_member_function_call_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		LuaIntf::LuaBinding(lua)
			.beginClass<basic>("basic")
			.addConstructor(LUA_ARGS())
			.addFunction("set", &basic::set)
			.addFunction("get", &basic::get)
			.endClass();

		lua.doString("b = basic()");
		auto code = repeated_code("b:set(i) b:get()");
		meter.measure([&lua, &code]() {
			lua.doString(code.c_str());
		});
	}

	void lua_intf_member_variable_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		LuaIntf::LuaBinding(lua)
			.beginClass<basic>("basic")
			.addConstructor(LUA_ARGS())
			.addVariable("var0", &basic::var)
			.addVariable("var1", &basic::var)
			.addVariable("var2", &basic::var)
			.addVariable("var3", &basic::var)
			.addVariable("var4", &basic::var)
			.endClass();

		lua.doString("b = basic()");
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
		meter.measure([&lua, &code]() {
			lua.doString(code.c_str());
		});
	}

	void lua_intf_member_variable_complex_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		LuaIntf::LuaBinding(lua)
			.beginClass<basic>("basic")
			.addConstructor(LUA_ARGS())
			.addVariable("var0", &basic::var)
			.addVariable("var1", &basic::var)
			.addVariable("var2", &basic::var)
			.addVariable("var3", &basic::var)
			.addVariable("var4", &basic::var)
			.addVariable("var5", &basic::var)
			.addVariable("var6", &basic::var)
			.addVariable("var7", &basic::var)
			.addVariable("var8", &basic::var)
			.addVariable("var9", &basic::var)
			.addVariable("var10", &basic::var)
			.addVariable("var11", &basic::var)
			.addVariable("var12", &basic::var)
			.addVariable("var13", &basic::var)
			.addVariable("var14", &basic::var)
			.addVariable("var15", &basic::var)
			.addVariable("var16", &basic::var)
			.addVariable("var17", &basic::var)
			.addVariable("var18", &basic::var)
			.addVariable("var19", &basic::var)
			.addVariable("var20", &basic::var)
			.addVariable("var21", &basic::var)
			.addVariable("var22", &basic::var)
			.addVariable("var23", &basic::var)
			.addVariable("var24", &basic::var)
			.addVariable("var25", &basic::var)
			.addVariable("var26", &basic::var)
			.addVariable("var27", &basic::var)
			.addVariable("var28", &basic::var)
			.addVariable("var29", &basic::var)
			.addVariable("var30", &basic::var)
			.addVariable("var31", &basic::var)
			.addVariable("var32", &basic::var)
			.addVariable("var33", &basic::var)
			.addVariable("var34", &basic::var)
			.addVariable("var35", &basic::var)
			.addVariable("var36", &basic::var)
			.addVariable("var37", &basic::var)
			.addVariable("var38", &basic::var)
			.addVariable("var39", &basic::var)
			.addVariable("var40", &basic::var)
			.addVariable("var41", &basic::var)
			.addVariable("var42", &basic::var)
			.addVariable("var43", &basic::var)
			.addVariable("var44", &basic::var)
			.addVariable("var45", &basic::var)
			.addVariable("var46", &basic::var)
			.addVariable("var47", &basic::var)
			.addVariable("var48", &basic::var)
			.addVariable("var49", &basic::var)
			.endClass();

		lua.doString("b = basic()");
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
		meter.measure([&lua, &code]() {
			lua.doString(code.c_str());
		});
	}

	void lua_intf_member_variable_last_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		LuaIntf::LuaBinding(lua)
			.beginClass<basic>("basic")
			.addConstructor(LUA_ARGS())
			.addVariable("var0", &basic::var)
			.addVariable("var1", &basic::var)
			.addVariable("var2", &basic::var)
			.addVariable("var3", &basic::var)
			.addVariable("var4", &basic::var)
			.addVariable("var5", &basic::var)
			.addVariable("var6", &basic::var)
			.addVariable("var7", &basic::var)
			.addVariable("var8", &basic::var)
			.addVariable("var9", &basic::var)
			.addVariable("var10", &basic::var)
			.addVariable("var11", &basic::var)
			.addVariable("var12", &basic::var)
			.addVariable("var13", &basic::var)
			.addVariable("var14", &basic::var)
			.addVariable("var15", &basic::var)
			.addVariable("var16", &basic::var)
			.addVariable("var17", &basic::var)
			.addVariable("var18", &basic::var)
			.addVariable("var19", &basic::var)
			.addVariable("var20", &basic::var)
			.addVariable("var21", &basic::var)
			.addVariable("var22", &basic::var)
			.addVariable("var23", &basic::var)
			.addVariable("var24", &basic::var)
			.addVariable("var25", &basic::var)
			.addVariable("var26", &basic::var)
			.addVariable("var27", &basic::var)
			.addVariable("var28", &basic::var)
			.addVariable("var29", &basic::var)
			.addVariable("var30", &basic::var)
			.addVariable("var31", &basic::var)
			.addVariable("var32", &basic::var)
			.addVariable("var33", &basic::var)
			.addVariable("var34", &basic::var)
			.addVariable("var35", &basic::var)
			.addVariable("var36", &basic::var)
			.addVariable("var37", &basic::var)
			.addVariable("var38", &basic::var)
			.addVariable("var39", &basic::var)
			.addVariable("var40", &basic::var)
			.addVariable("var41", &basic::var)
			.addVariable("var42", &basic::var)
			.addVariable("var43", &basic::var)
			.addVariable("var44", &basic::var)
			.addVariable("var45", &basic::var)
			.addVariable("var46", &basic::var)
			.addVariable("var47", &basic::var)
			.addVariable("var48", &basic::var)
			.addVariable("var49", &basic::var)
			.endClass();

		lua.doString("b = basic()");
		auto code = repeated_code(
			"b.var49 = i\nx = b.var49\n"
		);
		meter.measure([&lua, &code]() {
			lua.doString(code.c_str());
		});
	}

	void lua_intf_stateful_function_object_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		LuaIntf::LuaBinding(lua)
			.addFunction("f", basic_stateful());
		LuaIntf::LuaRef f = lua.getGlobal("f");
		meter.measure([&f]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f.call<int>(i);
				x += v;
			}
			return x;
		});
	}

	void lua_intf_multi_return_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		lua.setGlobal("f", &basic_multi_return);
		LuaIntf::LuaRef f = lua.getGlobal("f");
		meter.measure([&f]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				std::tuple<int, int> v = f.call<std::tuple<int, int>>(i);
				x += std::get<0>(v);
				x += std::get<1>(v);
			}
			return x;
		});
	}

	void lua_intf_base_derived_measure(nonius::chronometer& meter) {
		// Unsupported?
		// It seems like lua_intf has no facilities for base casting
		// from a derived stored in Lua
		meter.measure([&]() {
		});
	}

	void lua_intf_return_userdata_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		LuaIntf::LuaBinding(lua)
			.beginClass<basic>("basic")
			.endClass();

		lua.setGlobal("f", &basic_return);
		auto code = repeated_code("b = f(i)");
		meter.measure([&lua, &code]() {
			lua.doString(code.c_str());
		});
	}

	void lua_intf_optional_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		meter.measure([&lua]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				LuaIntf::LuaRef tu = lua.getGlobal("warble.value");
				if (tu.type() == LuaIntf::LuaTypeID::NUMBER) {
					int v = tu.toValue<int>();
					x += v;
				}
				else {
					x += 1;
				}
			}
			return x;
		});
	}

	void lua_intf_implicit_inheritance_call_measure(nonius::chronometer& meter) {
		// Unsupported?
		// Ask author
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		LuaIntf::LuaBinding(lua)
			.beginClass<complex_base_a>("complex_base_a")
			.addConstructor(LUA_ARGS())
			.addFunction("a_func", &complex_base_a::a_func)
			.addVariable("a", &complex_base_a::a)
			.endClass();

		LuaIntf::LuaBinding(lua)
			.beginClass<complex_base_b>("complex_base_b")
			.addConstructor(LUA_ARGS())
			.addFunction("b_func", &complex_base_b::b_func)
			.addVariable("b", &complex_base_b::b)
			.endClass();

		LuaIntf::LuaBinding(lua)
			.beginClass<complex_ab>("complex_ab")
			.addConstructor(LUA_ARGS())
			.addFunction("ab_func", &complex_ab::ab_func)
			.addVariable("ab", &complex_ab::ab)
			.endClass();

		lua.doString("b = complex_ab()");
		auto code = repeated_code("b:b_func()");
		meter.measure([&lua, &code]() {
			lua.doString(code.c_str());
		});
	}

}
