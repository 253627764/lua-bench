#include "lua bench.hpp"
#include "basic_lua.hpp"
#include <luacppinterface.h>

namespace lb {

	void luacppinterface_global_string_get_measure(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua_atpanic(lua.GetState().get(), panic_throw);
		
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
		lua_atpanic(lua.GetState().get(), panic_throw);

		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i)
				lua.Set("value", i);
		});
	}

	void luacppinterface_table_get_measure(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua_atpanic(lua.GetState().get(), panic_throw);

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
		lua_atpanic(lua.GetState().get(), panic_throw);

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
		lua_atpanic(lua.GetState().get(), panic_throw);

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
		lua_atpanic(lua.GetState().get(), panic_throw);

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
		lua_atpanic(lua.GetState().get(), panic_throw);

		lua.Set("f", l.CreateFunction<int(int)>(basic_call));
		std::string code = repeated_code("f(i)");
		meter.measure([&]() {
			if (l.RunScript(code) != "No errors") {
				lua_error(lua.GetState().get());
			}
		});
	}

	void luacppinterface_lua_function_measure(nonius::chronometer& meter) {
		// Fucking broken
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua_atpanic(lua.GetState().get(), panic_throw);

		if(l.RunScript(R"(function f (i)
			return i;
		end)") != "No errors") {
			lua_error(lua.GetState().get());
		}
		
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
		lua_atpanic(lua.GetState().get(), panic_throw);

		lua.Set("f", l.CreateFunction<int(int)>(basic_call));
		
		auto f = lua.Get<LuaFunction<int(int)>>("f");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i)
				x += f.Invoke(i);
			return x;
		});
	}

	void luacppinterface_member_function_call_measure(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua_atpanic(lua.GetState().get(), panic_throw);

		auto image = l.CreateUserdata<basic>(new basic());
		lua.Set("b", image);
		image.Bind<void>("set", &basic::set);
		image.Bind<int>("get", &basic::get);
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			if (l.RunScript(code) != "No errors") {
				lua_error(lua.GetState().get());
			}
		});
	}

	void luacppinterface_member_variable_measure(nonius::chronometer& meter) {
		// Unsupported
		//meter.measure([]() {});
	}

	void luacppinterface_stateful_function_object_measure(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua_atpanic(lua.GetState().get(), panic_throw);

		lua.Set("f", l.CreateFunction<int(int)>(basic_stateful()));

		auto f = lua.Get<LuaFunction<int(int)>>("f");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i)
				x += f.Invoke(i);
			return x;
		});
	}

	void luacppinterface_multi_return_measure(nonius::chronometer& meter) {
		// Unsupported
		meter.measure([&]() {
		});
	}

	void luacppinterface_base_derived_measure(nonius::chronometer& meter) {
		// Unsupported
		// The userdata pulls out the wrong base class and fails
		// with the exceptions below
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua_atpanic(lua.GetState().get(), panic_throw);

		auto lud = l.CreateUserdata<complex_ab>(new complex_ab());
		lua.Set("b", lud);
		{
			LuaUserdata<complex_ab> lab = lua.Get<LuaUserdata<complex_ab>>("b");
			LuaUserdata<complex_base_a> la = lua.Get<LuaUserdata<complex_base_a>>("b");
			LuaUserdata<complex_base_b> lb = lua.Get<LuaUserdata<complex_base_b>>("b");
			complex_ab& ab = *lab.GetPointer();
			complex_base_a& va = *la.GetPointer();
			complex_base_b& vb = *lb.GetPointer();
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
				LuaUserdata<complex_base_a> la = lua.Get<LuaUserdata<complex_base_a>>("b");
				LuaUserdata<complex_base_b> lb = lua.Get<LuaUserdata<complex_base_b>>("b");
				complex_base_a& va = *la.GetPointer();
				complex_base_b& vb = *lb.GetPointer();
				x += va.a_func();
				x += vb.b_func();
			}
		});
	}

	void luacppinterface_return_userdata_measure(nonius::chronometer& meter) {
		Lua l;
		auto lua = l.GetGlobalEnvironment();
		lua_atpanic(lua.GetState().get(), panic_throw);

		lua.Set("f", l.CreateFunction<LuaUserdata<basic>(int)>([&] (int i) -> LuaUserdata<basic> {
			return l.CreateUserdata(new basic(basic_return(i)));
		}));
		std::string code = repeated_code("f(i)");
		meter.measure([&]() {
			if (l.RunScript(code) != "No errors") {
				lua_error(lua.GetState().get());
			}
		});
	}

	void luacppinterface_optional_measure(nonius::chronometer& meter) {
		// Unsupported
		meter.measure([&]() {
		});
	}

}
