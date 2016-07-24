#include "lua bench.hpp"
#include "basic_lua.hpp"
#include <oolua.h>

OOLUA_PROXY(basic)
OOLUA_MGET_MSET(var)
OOLUA_MFUNC_CONST(get)
OOLUA_MFUNC(set)
OOLUA_PROXY_END

OOLUA_PROXY(complex_base_a)
OOLUA_PROXY_END

OOLUA_PROXY(complex_base_b)
OOLUA_PROXY_END

OOLUA_PROXY(complex_ab, complex_base_a, complex_base_b)
OOLUA_PROXY_END

OOLUA_EXPORT_FUNCTIONS_CONST(basic, get)
OOLUA_EXPORT_FUNCTIONS(basic, set)

OOLUA_CFUNC(basic_call, oo_basic_call)
//OOLUA_CFUNC(basic_multi_return, oo_basic_multi_return)

namespace lb {

	static const int oolua_value = 24;

	void oolua_global_string_get_measure(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		lua_atpanic(vm, panic_throw);
		set_global(vm, "value", oolua_value);
		meter.measure([&vm]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = 0;
				get_global(vm, "", v);
				x += v;
			}
			return x;
		});
	}

	void oolua_global_string_set_measure(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		lua_atpanic(vm, panic_throw);
		
		set_global(vm, "value", oolua_value);
		meter.measure([&vm]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = 0;
				set_global(vm, "value", i);
				x += v;
			}
			return x;
		});
	}

	void oolua_chained_get_measure(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		lua_atpanic(vm, panic_throw);
		
		Table tu = new_table(vm);
		set_global(vm, "ulahibe", tu);
		Table tw = new_table(vm);
		tu.set("warble", tw);
		tw.set("value", 24);

		meter.measure([&vm]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = 0;
				Table tw;
				Table tu;
				get_global(vm, "ulahibe", tu);
				tu.at("warble", tw);
				tw.at("value", v);
				x += v;
			}
			return x;
		});
	}

	void oolua_chained_set_measure(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		lua_atpanic(vm, panic_throw);
		
		Table tu = new_table(vm);
		set_global(vm, "ulahibe", tu);
		Table tw = new_table(vm);
		tu.set("warble", tw);
		tw.set("value", 24);

		meter.measure([&vm]() {
			for (int i = 0; i < repetition; ++i) {
				Table tw;
				Table tu;
				get_global(vm, "ulahibe", tu);
				tu.at("warble", tw);
				tw.set("value", i);
			}
		});
	}

	void oolua_table_get_measure(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		lua_atpanic(vm, panic_throw);
		
		Table tu = new_table(vm);
		set_global(vm, "warble", tu);
		Table tw;
		get_global(vm, "warble", tw);
		tw.set("value", 24);

		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = 0;
				tw.at("value", v);
				x += v;
			}
			return x;
		});
	}

	void oolua_table_set_measure(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		lua_atpanic(vm, panic_throw);
		
		Table tu = new_table(vm);
		set_global(vm, "warble", tu);
		Table tw;
		get_global(vm, "warble", tw);
		
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				tw.set("value", i);
			}
		});
	}

	void oolua_c_function_measure(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		lua_atpanic(vm, panic_throw);
		
		set_global(vm, "f", oo_basic_call);
		std::string code = repeated_code("f(i)");
		meter.measure([&]() {
			if (!vm.run_chunk(code)) {
				auto str = OOLUA::get_last_error(vm);
				luaL_error(vm, str.c_str());
			}
		});
	}

	void oolua_lua_function_measure(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		lua_atpanic(vm, panic_throw);
		
		vm.run_chunk(R"(function f (i)
			return i;
		end)");
		Lua_function f(vm);
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f("f", i);
				x += v;
			}
			return x;
		});
	}

	void oolua_c_through_lua_function_measure(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		lua_atpanic(vm, panic_throw);
		
		set_global(vm, "f", oo_basic_call);
		Lua_function f(vm);
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f("f", i);
				x += v;
			}
			return x;
		});
	}

	void oolua_member_function_call(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		lua_atpanic(vm, panic_throw);
		
		vm.register_class<basic>();
		vm.run_chunk("b = basic.new()");
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			if (!vm.run_chunk(code)) {
				auto str = OOLUA::get_last_error(vm);
				luaL_error(vm, str.c_str());
			}
		});
	}

	void oolua_member_variable(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		lua_atpanic(vm, panic_throw);
		
		vm.register_class<basic>();
		vm.run_chunk("b = basic.new()");
		std::string code = repeated_code("b.var = i\nx = b.var");
		meter.measure([&]() {
			if (!vm.run_chunk(code)) {
				auto str = OOLUA::get_last_error(vm);
				luaL_error(vm, str.c_str());
			}
		});
	}

	void oolua_stateful_function_object_measure(nonius::chronometer& meter) {
		// Unsupported
		meter.measure([&]() {
		});
	}

	void oolua_multi_return_measure(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		lua_atpanic(vm, panic_throw);
		
		//set_global(vm, "f", oo_basic_multi_return);
		Lua_function f(vm);
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f("f", i);
				x += v;
			}
			return x;
		});
	}

	void oolua_base_derived_measure(nonius::chronometer& meter) {
		// Unsupported?
		meter.measure([&]() {
		});
	}

}
