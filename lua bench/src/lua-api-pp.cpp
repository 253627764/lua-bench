#include <luapp/lua.hpp>
#include <lua.hpp>
#include "lua bench.hpp"
#include "basic.hpp"
#include "basic_lua.hpp"

LUAPP_USERDATA(basic, "basic");
LUAPP_USERDATA(complex_base_a, "complex_base_a");
LUAPP_USERDATA(complex_base_b, "complex_base_b");
LUAPP_USERDATA(complex_ab, "complex_ab");

namespace lb {
	
	lua::Retval setup(lua::Context& c) {
		c.mt<basic>() = lua::Table::records(c,
			"__index", lua::Table::records(c,
				"var", &basic::var,
				"get", &basic::get,
				"set", &basic::set
			)
		);
		c.global["basic_new"] = static_cast<basic(*)()>([]() {return basic(); });
		return c.ret();
	}

	lua::Retval basic_multi_return_setup(lua::Context& c) {
		auto r = basic_multi_return(c.args[1].to<int>());
		return c.ret(std::get<0>(r), std::get<1>(r));
	}
	
	void lua_api_pp_global_string_get_measure(nonius::chronometer& meter) {
		lua::State l;
		lua_atpanic(l.getRawState(), panic_throw);
		
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
		lua_atpanic(l.getRawState(), panic_throw);

		lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
		meter.measure([&L]() {
			for (int i = 0; i < repetition; ++i) {
				L.global.set("value", 24);
			}
		});
	}

	void lua_api_pp_chained_get_measure(nonius::chronometer& meter) {
		lua::State l;
		lua_atpanic(l.getRawState(), panic_throw);

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
		lua_atpanic(l.getRawState(), panic_throw);

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
		lua_atpanic(l.getRawState(), panic_throw);

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
		lua_atpanic(l.getRawState(), panic_throw);

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
		lua_atpanic(l.getRawState(), panic_throw);

		lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
		L.global.set("f", basic_call);
		std::string code = repeated_code("f(i)");
		meter.measure([&]() {
			l.runString(code);
		});
	}

	void lua_api_pp_lua_function_measure(nonius::chronometer& meter) {
		lua::State l;
		lua_atpanic(l.getRawState(), panic_throw);

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
		lua_atpanic(l.getRawState(), panic_throw);

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
		lua::State l;
		lua_atpanic(l.getRawState(), panic_throw);

		l.call(lua::mkcf<setup>);
		l.runString("b = basic_new()");
		std::string code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			l.runString(code);
		});
	}

	void lua_api_pp_member_variable(nonius::chronometer& meter) {
		// Unsupported
		/*lua::State l;
		lua_atpanic(l.getRawState(), panic_throw);

		l.call(lua::mkcf<setup>);
		l.runString("b = basic_new()");
		std::string code = repeated_code("b.var = i\nx = b.var");
		meter.measure([&]() {
			l.runString(code);
		});*/
	}

	void lua_api_pp_stateful_function_object_measure(nonius::chronometer& meter) {
		// Unsupported
		meter.measure([&]() {
		});
	}

	void lua_api_pp_multi_return_measure(nonius::chronometer& meter) {
		lua::State l;
		lua_atpanic(l.getRawState(), panic_throw);

		lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
		L.global.set("f", lua::mkcf<basic_multi_return_setup>);
		meter.measure([&L]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = L.global["f"](i);
				x += v;
			}
			return x;
		});
	}

	void lua_api_pp_base_derived_measure(nonius::chronometer& meter) {
		// Unsupported
		meter.measure([&]() {
		});
	}

}
