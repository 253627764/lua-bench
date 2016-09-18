#include <old_sol.hpp>
#include "lua bench.hpp"
#include "basic.hpp"
#include "basic_lua.hpp"

namespace lb {

	void old_sol_global_string_get_measure(nonius::chronometer& meter) {
		old_sol::state lua;
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

	void old_sol_global_string_set_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua.set("value", i);
			}
		});
	}

	void old_sol_table_get_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.script("warble = { value = 24 }");
		old_sol::table t = lua["warble"].get<old_sol::table>();
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = t["value"];
				x += v;
			}
			return x;
		});
	}

	void old_sol_table_set_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.create_table("warble", 0, 0);
		old_sol::table x = lua["warble"].get<old_sol::table>();
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				x.set("value", i);
		});
	}

	void old_sol_chained_get_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.script("ulahibe = { warble = { value = 24 } }");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["ulahibe"].get<old_sol::table>()["warble"].get<old_sol::table>()["value"];
				x += v;
			}
			return x;
		});
	}

	void old_sol_chained_set_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.script("ulahibe = { warble = { value = 24 } }");
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				lua["ulahibe"].get<old_sol::table>()["warble"].get<old_sol::table>()["value"] = i;
		});
	}

	void old_sol_c_function_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.set_function("f", &basic_call);
		std::string code = repeated_code("f(i)");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void old_sol_lua_function_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.script(R"(function f (i)
			return i;
		end)");
		old_sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f.call<int>(i);
				x += v;
			}
			return x;
		});
	}

	void old_sol_c_through_lua_function_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.set_function("f", basic_call);
		old_sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f.call<int>(i);
				x += v;
			}
			return x;
		});
	}

	void old_sol_member_function_call_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.new_usertype<basic>("basic",
			"get", &basic::get,
			"set", &basic::set
		);
		lua.script("b = basic:new()");
		std::string code = repeated_code(member_function_call_code);
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void old_sol_member_variable_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.new_usertype<basic_large>("basic_large",
			"var", &basic_large::var,
			"var0", &basic_large::var0,
			"var1", &basic_large::var1,
			"var2", &basic_large::var2,
			"var3", &basic_large::var3,
			"var4", &basic_large::var4
		);
		lua.script("b = basic_large:new()");
		std::string code = repeated_code(
			member_variable_code
		);

		meter.measure([&]() {
			lua.script(code);
		});
	}

	void old_sol_member_variable_complex_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.new_usertype<basic_large>("basic_large",
			"var", &basic_large::var,
			"var0", &basic_large::var0,
			"var1", &basic_large::var1,
			"var2", &basic_large::var2,
			"var3", &basic_large::var3,
			"var4", &basic_large::var4,
			"var5", &basic_large::var5,
			"var6", &basic_large::var6,
			"var7", &basic_large::var7,
			"var8", &basic_large::var8,
			"var9", &basic_large::var9,
			"var10", &basic_large::var10,
			"var11", &basic_large::var11,
			"var12", &basic_large::var12,
			"var13", &basic_large::var13,
			"var14", &basic_large::var14,
			"var15", &basic_large::var15,
			"var16", &basic_large::var16,
			"var17", &basic_large::var17,
			"var18", &basic_large::var18,
			"var19", &basic_large::var19,
			"var20", &basic_large::var20,
			"var21", &basic_large::var21,
			"var22", &basic_large::var22,
			"var23", &basic_large::var23,
			"var24", &basic_large::var24,
			"var25", &basic_large::var25,
			"var26", &basic_large::var26,
			"var27", &basic_large::var27,
			"var28", &basic_large::var28,
			"var29", &basic_large::var29,
			"var30", &basic_large::var30,
			"var31", &basic_large::var31,
			"var32", &basic_large::var32,
			"var33", &basic_large::var33,
			"var34", &basic_large::var34,
			"var35", &basic_large::var35,
			"var36", &basic_large::var36,
			"var37", &basic_large::var37,
			"var38", &basic_large::var38,
			"var39", &basic_large::var39,
			"var40", &basic_large::var40,
			"var41", &basic_large::var41,
			"var42", &basic_large::var42,
			"var43", &basic_large::var43,
			"var44", &basic_large::var44,
			"var45", &basic_large::var45,
			"var46", &basic_large::var46,
			"var47", &basic_large::var47,
			"var48", &basic_large::var48,
			"var49", &basic_large::var49
		);

		lua.script("b = basic_large:new()");
		std::string code = repeated_code(
			member_variable_large_code
		);
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void old_sol_member_variable_last_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.new_usertype<basic_large>("basic_large",
			"var", &basic_large::var,
			"var0", &basic_large::var0,
			"var1", &basic_large::var1,
			"var2", &basic_large::var2,
			"var3", &basic_large::var3,
			"var4", &basic_large::var4,
			"var5", &basic_large::var5,
			"var6", &basic_large::var6,
			"var7", &basic_large::var7,
			"var8", &basic_large::var8,
			"var9", &basic_large::var9,
			"var10", &basic_large::var10,
			"var11", &basic_large::var11,
			"var12", &basic_large::var12,
			"var13", &basic_large::var13,
			"var14", &basic_large::var14,
			"var15", &basic_large::var15,
			"var16", &basic_large::var16,
			"var17", &basic_large::var17,
			"var18", &basic_large::var18,
			"var19", &basic_large::var19,
			"var20", &basic_large::var20,
			"var21", &basic_large::var21,
			"var22", &basic_large::var22,
			"var23", &basic_large::var23,
			"var24", &basic_large::var24,
			"var25", &basic_large::var25,
			"var26", &basic_large::var26,
			"var27", &basic_large::var27,
			"var28", &basic_large::var28,
			"var29", &basic_large::var29,
			"var30", &basic_large::var30,
			"var31", &basic_large::var31,
			"var32", &basic_large::var32,
			"var33", &basic_large::var33,
			"var34", &basic_large::var34,
			"var35", &basic_large::var35,
			"var36", &basic_large::var36,
			"var37", &basic_large::var37,
			"var38", &basic_large::var38,
			"var39", &basic_large::var39,
			"var40", &basic_large::var40,
			"var41", &basic_large::var41,
			"var42", &basic_large::var42,
			"var43", &basic_large::var43,
			"var44", &basic_large::var44,
			"var45", &basic_large::var45,
			"var46", &basic_large::var46,
			"var47", &basic_large::var47,
			"var48", &basic_large::var48,
			"var49", &basic_large::var49
		);

		lua.script("b = basic_large:new()");
		std::string code = repeated_code(
			member_variable_large_last_code
		);
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void old_sol_stateful_function_object_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		int storage = 0;
		lua.set_function("f", basic_stateful());
		old_sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f.call<int>(i);
				x += v;
			}
			return x;
		});
	}

	void old_sol_multi_return_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.set_function("f", basic_multi_return);
		old_sol::function f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				std::tuple<int, int> v = f.call<int, int>(i);
				x += static_cast<int>(std::get<0>(v));
				x += static_cast<int>(std::get<1>(v));
			}
			return x;
		});
	}

	void old_sol_base_derived_measure(nonius::chronometer& meter) {
		/* Unsupported */
	}

	void old_sol_optional_measure(nonius::chronometer& meter) {
		/* Unsupported */
	}

	void old_sol_return_userdata_measure(nonius::chronometer& meter) {
		old_sol::state lua;
		lua_atpanic(lua.lua_state(), panic_throw);
		lua.set_function("f", basic_return);
		std::string code = repeated_code("b = f(i)");
		meter.measure([&]() {
			lua.script(code);
		});
	}

	void old_sol_implicit_inheritance_call_measure(nonius::chronometer& meter) {
		/* Unsupported */
	}

}
