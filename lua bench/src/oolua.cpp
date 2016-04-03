#include "lua_bench.hpp"
#include "basic.hpp"
#include <lua.hpp>
#include <oolua.h>

namespace lb {
	
/*	OOLUA_PROXY(basic)
//		OOLUA_MGET_MSET(var)
//		OOLUA_MFUNC_CONST(get)
//		OOLUA_MFUNC(set)
	OOLUA_PROXY_END
	*/

	OOLUA_CFUNC(basic_call, oo_basic_call);
	static const int oolua_value = 24;

	void oolua_global_string_get_measure(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
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
		set_global(vm, "f", oo_basic_call);
		std::string code = repeated_code("f(i)");
		meter.measure([&](int i) {
			vm.run_chunk(code);
		});
	}

	void oolua_lua_function_measure(nonius::chronometer& meter) {
		using namespace OOLUA;
		Script vm;
		vm.run_chunk(R"(function f (i)
			return i;
		end)");
		Lua_function f(vm);
		meter.measure([&](int i) {
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
		set_global(vm, "f", oo_basic_call);
		Lua_function f(vm);
		meter.measure([&](int i) {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f("f", i);
				x += v;
			}
			return x;
		});
	}

	void oolua_member_function_call(nonius::chronometer& meter) {
		meter.measure([&](int i) {
		});
	}

	void oolua_member_variable_set(nonius::chronometer& meter) {
		meter.measure([&](int i) {
		});
	}

	void oolua_member_variable_get(nonius::chronometer& meter) {
		meter.measure([&](int i) {
		});
	}

}
