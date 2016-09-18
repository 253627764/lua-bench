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
		auto code = repeated_code(member_function_call_code);
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
			.addVariable("var", &basic::var)
			.addVariable("var0", &basic::var0)
			.addVariable("var1", &basic::var1)
			.addVariable("var2", &basic::var2)
			.addVariable("var3", &basic::var3)
			.addVariable("var4", &basic::var4)
			.endClass();

		lua.doString("b = basic()");
		auto code = repeated_code(
			member_variable_code
		);
		meter.measure([&lua, &code]() {
			lua.doString(code.c_str());
		});
	}

	void lua_intf_member_variable_complex_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		LuaIntf::LuaBinding(lua)
			.beginClass<basic_large>("basic_large")
			.addConstructor(LUA_ARGS())
			.addVariable("var", &basic_large::var)
			.addVariable("var0", &basic_large::var0)
			.addVariable("var1", &basic_large::var1)
			.addVariable("var2", &basic_large::var2)
			.addVariable("var3", &basic_large::var3)
			.addVariable("var4", &basic_large::var4)
			.addVariable("var5", &basic_large::var5)
			.addVariable("var6", &basic_large::var6)
			.addVariable("var7", &basic_large::var7)
			.addVariable("var8", &basic_large::var8)
			.addVariable("var9", &basic_large::var9)
			.addVariable("var10", &basic_large::var10)
			.addVariable("var11", &basic_large::var11)
			.addVariable("var12", &basic_large::var12)
			.addVariable("var13", &basic_large::var13)
			.addVariable("var14", &basic_large::var14)
			.addVariable("var15", &basic_large::var15)
			.addVariable("var16", &basic_large::var16)
			.addVariable("var17", &basic_large::var17)
			.addVariable("var18", &basic_large::var18)
			.addVariable("var19", &basic_large::var19)
			.addVariable("var20", &basic_large::var20)
			.addVariable("var21", &basic_large::var21)
			.addVariable("var22", &basic_large::var22)
			.addVariable("var23", &basic_large::var23)
			.addVariable("var24", &basic_large::var24)
			.addVariable("var25", &basic_large::var25)
			.addVariable("var26", &basic_large::var26)
			.addVariable("var27", &basic_large::var27)
			.addVariable("var28", &basic_large::var28)
			.addVariable("var29", &basic_large::var29)
			.addVariable("var30", &basic_large::var30)
			.addVariable("var31", &basic_large::var31)
			.addVariable("var32", &basic_large::var32)
			.addVariable("var33", &basic_large::var33)
			.addVariable("var34", &basic_large::var34)
			.addVariable("var35", &basic_large::var35)
			.addVariable("var36", &basic_large::var36)
			.addVariable("var37", &basic_large::var37)
			.addVariable("var38", &basic_large::var38)
			.addVariable("var39", &basic_large::var39)
			.addVariable("var40", &basic_large::var40)
			.addVariable("var41", &basic_large::var41)
			.addVariable("var42", &basic_large::var42)
			.addVariable("var43", &basic_large::var43)
			.addVariable("var44", &basic_large::var44)
			.addVariable("var45", &basic_large::var45)
			.addVariable("var46", &basic_large::var46)
			.addVariable("var47", &basic_large::var47)
			.addVariable("var48", &basic_large::var48)
			.addVariable("var49", &basic_large::var49)
			.endClass();

		lua.doString("b = basic_large()");
		auto code = repeated_code(
			member_variable_large_code
		);
		meter.measure([&lua, &code]() {
			lua.doString(code.c_str());
		});
	}

	void lua_intf_member_variable_last_measure(nonius::chronometer& meter) {
		LuaIntf::LuaContext lua;
		lua_atpanic(lua, panic_throw);

		LuaIntf::LuaBinding(lua)
			.beginClass<basic_large>("basic_large")
			.addConstructor(LUA_ARGS())
			.addVariable("var", &basic_large::var)
			.addVariable("var0", &basic_large::var0)
			.addVariable("var1", &basic_large::var1)
			.addVariable("var2", &basic_large::var2)
			.addVariable("var3", &basic_large::var3)
			.addVariable("var4", &basic_large::var4)
			.addVariable("var5", &basic_large::var5)
			.addVariable("var6", &basic_large::var6)
			.addVariable("var7", &basic_large::var7)
			.addVariable("var8", &basic_large::var8)
			.addVariable("var9", &basic_large::var9)
			.addVariable("var10", &basic_large::var10)
			.addVariable("var11", &basic_large::var11)
			.addVariable("var12", &basic_large::var12)
			.addVariable("var13", &basic_large::var13)
			.addVariable("var14", &basic_large::var14)
			.addVariable("var15", &basic_large::var15)
			.addVariable("var16", &basic_large::var16)
			.addVariable("var17", &basic_large::var17)
			.addVariable("var18", &basic_large::var18)
			.addVariable("var19", &basic_large::var19)
			.addVariable("var20", &basic_large::var20)
			.addVariable("var21", &basic_large::var21)
			.addVariable("var22", &basic_large::var22)
			.addVariable("var23", &basic_large::var23)
			.addVariable("var24", &basic_large::var24)
			.addVariable("var25", &basic_large::var25)
			.addVariable("var26", &basic_large::var26)
			.addVariable("var27", &basic_large::var27)
			.addVariable("var28", &basic_large::var28)
			.addVariable("var29", &basic_large::var29)
			.addVariable("var30", &basic_large::var30)
			.addVariable("var31", &basic_large::var31)
			.addVariable("var32", &basic_large::var32)
			.addVariable("var33", &basic_large::var33)
			.addVariable("var34", &basic_large::var34)
			.addVariable("var35", &basic_large::var35)
			.addVariable("var36", &basic_large::var36)
			.addVariable("var37", &basic_large::var37)
			.addVariable("var38", &basic_large::var38)
			.addVariable("var39", &basic_large::var39)
			.addVariable("var40", &basic_large::var40)
			.addVariable("var41", &basic_large::var41)
			.addVariable("var42", &basic_large::var42)
			.addVariable("var43", &basic_large::var43)
			.addVariable("var44", &basic_large::var44)
			.addVariable("var45", &basic_large::var45)
			.addVariable("var46", &basic_large::var46)
			.addVariable("var47", &basic_large::var47)
			.addVariable("var48", &basic_large::var48)
			.addVariable("var49", &basic_large::var49)
			.endClass();

		lua.doString("b = basic_large()");
		auto code = repeated_code(
			member_variable_large_last_code
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
