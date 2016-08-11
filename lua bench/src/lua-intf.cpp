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
			.addFunction("set", &basic::set)
			.addFunction("get", &basic::get)
			.addVariable("var", &basic::var)
			.endClass();

		lua.doString("b = basic()");
		auto code = repeated_code("b.var = i\nx = b.var");
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
