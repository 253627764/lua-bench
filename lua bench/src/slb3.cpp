#include "lua_bench.hpp"
#include "basic.hpp"
#include <SLB/slb.hpp>

namespace lb {

	inline int panic_throw(lua_State* L) {
		const char* message = lua_tostring(L, -1);
		std::string err = message ? message : "An unexpected error occurred and forced the lua state to call panic_throw";
		throw std::runtime_error(err);
	}

	struct ShitScript : SLB::Script {
		using Script::Script;
		lua_State* lua_state() {
			return getState();
		}
	};

	void slb3_global_string_get_measure(nonius::chronometer& meter) {
		SLB::Manager m;
		ShitScript lua(&m);
		lua.set("value", 24);
		meter.measure([&lua]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua.get<int>("value");
				x += v;
			}
			return x;
		});
	}

	void slb3_global_string_set_measure(nonius::chronometer& meter) {
		SLB::Manager m;
		ShitScript lua(&m);
		lua.set("value", 24);
		meter.measure([&lua]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				lua.set("value", 24);
			}
		});
	}

	void slb3_chained_get_measure(nonius::chronometer& meter) {
		// Unsupported
		//meter.measure([]() {});
	}

	void slb3_chained_set_measure(nonius::chronometer& meter) {
		// Unsupported
		//meter.measure([]() {});
	}

	void slb3_table_get_measure(nonius::chronometer& meter) {
		// Unsupported
		//meter.measure([]() {});
	}

	void slb3_table_set_measure(nonius::chronometer& meter) {
		// Unsupported
		//meter.measure([]() {});
	}

	void slb3_c_function_measure(nonius::chronometer& meter) {
		SLB::Manager m;
		ShitScript lua(&m);
		m.set("f", SLB::FuncCall::create(basic_call));
		std::string code = repeated_code("f(i)");
		meter.measure([&]() {
			lua.doString(code.c_str());
		});
	}

	void slb3_lua_function_measure(nonius::chronometer& meter) {
		SLB::Manager m;
		ShitScript lua(&m);
		
		lua_atpanic(lua.lua_state(), panic_throw);

		lua.doString(R"(function f (i)
			return i;
		end)");
		SLB::LuaCall<int(int)> f(lua.lua_state(), "f");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void slb3_c_through_lua_function_measure(nonius::chronometer& meter) {
		// Broken as fuck
		/*SLB::Manager m;
		ShitScript lua(&m);
		m.set("f", SLB::FuncCall::create(basic_call));
		SLB::LuaCall<int(int)> f(lua.lua_state(), "f");
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});*/
		// Unsupported
		//meter.measure([]() {});
	}

	void slb3_member_function_call(nonius::chronometer& meter) {
		SLB::Manager m;
		ShitScript lua(&m);
		SLB::Class<basic>("basic", &m)
			.constructor()
			.set("get", &basic::get)
			.set("set", &basic::set);
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			lua.doString(code.c_str());
		});
	}

	void slb3_member_variable(nonius::chronometer& meter) {
		// Unsupported
		//meter.measure([]() {});
	}

	void slb3_stateful_function_object_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

	void slb3_multi_return_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}

	void slb3_base_derived_measure(nonius::chronometer& meter) {
		meter.measure([&]() {
		});
	}


}
