#include "lua_bench.hpp"
#include "basic.hpp"
#include "lua_bench_wrap.hpp"
#include <luapp/lua.hpp>
#include <lua.hpp>

LUAPP_USERDATA(basic, "basic");

namespace lb {
	
	basic basic_new() {
		return basic(); 
	}
	
	void basic_gc(basic& self) {
		self.~basic();
	}
	
	int basic_get(basic& self) {
		return self.get();
	}

	void basic_set(basic& self, int x) {
		self.set(x);
	}

	lua::Retval setup(lua::Context& c) {
		c.mt<basic>() = lua::Table::records(c,
			"get", basic_get,
			"set", basic_set,
			"__index", basic_index_wrap,
			"__gc", basic_gc
		);
		c.global["basic_new"] = basic_new;
		return c.ret();
	}
	
	void lua_api_pp_global_string_get_measure(nonius::chronometer& meter) {
		lua::State l;
		lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
		L.global.set("value", 24);
		meter.measure([&L]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = L.global["value"];
				x += v;
			}
			return x;
		});
	}

	void lua_api_pp_global_string_set_measure(nonius::chronometer& meter) {
		lua::State l;
		lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
		meter.measure([&L]() {
			for (int i = 0; i < repetition; ++i) {
				L.global.set("value", 24);
			}
		});
	}

	void lua_api_pp_chained_get_measure(nonius::chronometer& meter) {
		lua::State l;
		lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
		L.global.set("ulahibe", lua::Table::records(L, "warble", lua::Table::records(L, "value", 24)));
		meter.measure([&L]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = L.global["ulahibe"]["warble"]["value"];
				v += x;
			}
			return x;
		});
	}

	void lua_api_pp_chained_set_measure(nonius::chronometer& meter) {
		lua::State l;
		lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
		L.global.set("ulahibe", lua::Table::records(L, "warble", lua::Table::records(L, "value", 24)));
		meter.measure([&L]() {
			for (int i = 0; i < repetition; ++i) {
				L.global["ulahibe"]["warble"]["value"] = 24;
			}
		});
	}

	void lua_api_pp_table_get_measure(nonius::chronometer& meter) {
		lua::State l;
		lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
		L.global.set("warble", lua::Table::records(L, "value", 24));
		lua::Table t = L.global["warble"];
		meter.measure([&t]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = t["value"];
				x += v;
			}
			return x;
		});
	}

	void lua_api_pp_table_set_measure(nonius::chronometer& meter) {
		lua::State l;
		lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
		L.global.set("warble", lua::Table::records(L, "value", 24));
		lua::Table t = L.global["warble"];
		meter.measure([&t]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = t["value"];
				x += v;
			}
			return x;
		});
	}

	void lua_api_pp_c_function_measure(nonius::chronometer& meter) {
		lua::State l;
		lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
		L.global.set("f", basic_call);
		std::string code = repeated_code("f(i)");
		meter.measure([&]() {
			l.runString(code);
		});
	}

	void lua_api_pp_lua_function_measure(nonius::chronometer& meter) {
		lua::State l;
		l.runString("function f (i) return i end");
		lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
		meter.measure([&L]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = L.global["f"](i);
				x += v;
			}
			return x;
		});
	}

	void lua_api_pp_c_through_lua_function_measure(nonius::chronometer& meter) {
		lua::State l;
		lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
		L.global.set("f", basic_call);
		meter.measure([&L]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = L.global["f"](i);
				x += v;
			}
			return x;
		});
	}

	void lua_api_pp_member_function_call(nonius::chronometer& meter) {
		// this framework is dumb as bricks
		lua::State l;
		l.call(lua::mkcf<setup>);
		l.runString("b = basic_new()");
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			l.runString(code);
		});
	}

	void lua_api_pp_member_variable(nonius::chronometer& meter) {
		//meter.measure([]() {
		//});
	}

}
