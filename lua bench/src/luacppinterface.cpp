#include "lua_bench.hpp"
#include "basic.hpp"
#include <luacppinterface.h>

namespace lb {

	void luacppinterface_global_string_get_measure(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua.Set("value", 24);
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i)
				x += lua.Get<int>("value");
			return x;
		});
	}

	void luacppinterface_global_string_set_measure(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				lua.Set("value", i);
		});
	}

	void luacppinterface_table_get_measure(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua.Set("warble", l.CreateTable());
		LuaTable t = lua.Get<LuaTable>("warble");
		t.Set("value", 24);

		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i)
				x += t.Get<int>("value");
			return x;
		});
	}

	void luacppinterface_table_set_measure(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua.Set("warble", l.CreateTable());
		LuaTable t = lua.Get<LuaTable>("warble");
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				t.Set("value", i);
		});
	}

	void luacppinterface_chained_get_measure(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua.Set("ulahibe", l.CreateTable());
		LuaTable tu = lua.Get<LuaTable>("ulahibe");
		tu.Set("warble", l.CreateTable());
		LuaTable tw = tu.Get<LuaTable>("warble");
		tw.Set("value", 24);
		meter.measure([&]() {
			int x = lua.Get<LuaTable>("ulahibe").Get<LuaTable>("warble").Get<int>("value");
			return x;
		});
	}

	void luacppinterface_chained_set_measure(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua.Set("ulahibe", l.CreateTable());
		LuaTable tu = lua.Get<LuaTable>("ulahibe");
		tu.Set("warble", l.CreateTable());
		LuaTable tw = tu.Get<LuaTable>("warble");
		tw.Set("value", 24);
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				lua.Get<LuaTable>("ulahibe").Get<LuaTable>("warble").Set("value", i);
		});
	}

	void luacppinterface_c_function_measure(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua.Set("f", l.CreateFunction<int(int)>(basic_call));
		std::string code = repeated_code("f(run)");
		meter.measure([&]() {
			l.RunScript(code);
		});
	}

	void luacppinterface_lua_function_measure(nonius::chronometer& meter) {
		// Fucking broken
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		l.RunScript(R"(function f (i)
			return i;
		end)");
		
		auto f = lua.Get<LuaFunction<int(int)>>("f");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i)
				x += f.Invoke(i);
			return x;
		});
	}

	void luacppinterface_c_through_lua_function_measure(nonius::chronometer& meter) {
		// Broken as shit
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua.Set("f", l.CreateFunction<int(int)>(basic_call));
		
		auto f = lua.Get<LuaFunction<int(int)>>("f");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i)
				x += f.Invoke(i);
			return x;
		});
	}

	void luacppinterface_member_function_call(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		auto image = l.CreateUserdata<basic>(new basic());
		lua.Set("b", image);
		image.Bind<void>("set", &basic::set);
		image.Bind<int>("get", &basic::get);
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			l.RunScript(code);
		});
	}

	void luacppinterface_member_variable(nonius::chronometer& meter) {
		// Unsupported
		//meter.measure([]() {});
	}

}
