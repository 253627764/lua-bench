#include "lua bench.hpp"
#include "basic_lua.hpp"
#include <kaguya/kaguya.hpp>

namespace lb {

	void kaguya_global_string_get_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["value"] = 24;
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["value"];
				x +=  v;
			}
			return x;
		});
	}

	void kaguya_global_string_set_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua["value"] = i;
			}
		});
	}

	void kaguya_table_get_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["warble"] = kaguya::NewTable();
		lua["warble"]["value"] = 24;
		kaguya::LuaTable t = lua["warble"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = t["value"];
				v += x;
			}
			return x;
		});
	}

	void kaguya_table_set_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["warble"] = kaguya::NewTable();
		kaguya::LuaTable t = lua["warble"];
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				t["value"] = i;
			}
		});
	}

	void kaguya_chained_get_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["ulahibe"] = kaguya::NewTable();
		lua["ulahibe"]["warble"] = kaguya::NewTable();
		lua["ulahibe"]["warble"]["value"] = 24;
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["ulahibe"]["warble"]["value"];
				x += v;
			}
			return x;
		});
	}

	void kaguya_chained_set_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["ulahibe"] = kaguya::NewTable();
		lua["ulahibe"]["warble"] = kaguya::NewTable();
		lua["ulahibe"]["warble"]["value"] = 24;
		meter.measure([&]() {
			for (int i = 0; i < repetition; ++i) {
				lua["ulahibe"]["warble"]["value"] = i;
			}
		});
	}

	void kaguya_c_function_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["f"].setFunction(basic_call);
		auto code = repeated_code("f(i)");
		meter.measure([&]() {
			if (!lua(code)) {
				lua_error(lua.state());
			}
		});
	}

	void kaguya_lua_function_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua(R"(function f (i)
			return i;
		end)");
		kaguya::LuaFunction f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void kaguya_c_through_lua_function_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["f"].setFunction(basic_call);
		kaguya::LuaFunction f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void kaguya_member_function_call_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["basic"].setClass<basic>(kaguya::ClassMetatable<basic>()
			.addConstructor()
			.addMember("var", &basic::var)
			.addMemberFunction("get", &basic::get)
			.addMemberFunction("set", &basic::set)
			);
		lua("b = basic.new()");
		auto code = repeated_code("b:set(i) b:get()");
		meter.measure([&]() {
			if (!lua(code)) {
				lua_error(lua.state());
			}
		});
	}

	void kaguya_member_variable_measure(nonius::chronometer& meter) {
		// Does not support member variable syntax:
		// turns it into a function, unfortunately
		//meter.measure([&]() {
		//});
	}

	void kaguya_stateful_function_object_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["f"] = kaguya::function(basic_stateful());
		kaguya::LuaFunction f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = f(i);
				x += v;
			}
			return x;
		});
	}

	void kaguya_multi_return_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["f"].setFunction(basic_multi_return);
		kaguya::LuaFunction f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int a, b;
				kaguya::tie(a, b) = f(i);
				x += a;
				x += b;
			}
			return x;
		});
	}

	void kaguya_base_derived_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["complex_ab"].setClass(
			kaguya::ClassMetatable<complex_ab, kaguya::MultipleBase<complex_base_a, complex_base_b>>()
			.addMemberFunction("a_func", &complex_ab::a_func)
			.addMemberFunction("b_func", &complex_ab::b_func)
			.addMemberFunction("ab_func", &complex_ab::ab_func)
		);
		complex_ab ab;
		// Set and verify correctness
		lua["b"] = std::ref( ab );
		{
			complex_base_a* va = lua["b"];
			complex_base_b* vb = lua["b"];
			if (va->a_func() != ab.a_func() || va->a != ab.a) {
				throw std::logic_error("proper base class casting not provided: failing benchmark");
			}
			if (vb->b_func() != ab.b_func() || vb->b != ab.b) {
				throw std::logic_error("proper base class casting not provided: failing benchmark");
			}
		}
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				complex_base_a* va = lua["b"];
				complex_base_b* vb = lua["b"];
				x += va->a_func();
				x += vb->b_func();
			}
			return x;
		});
	}

	void kaguya_return_userdata(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["f"].setFunction(basic_return);
		kaguya::LuaFunction f = lua["f"];
		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int a, b;
				kaguya::tie(a, b) = f(i);
				x += a;
				x += b;
			}
			return x;
		});
	}

	void kaguya_optional_measure(nonius::chronometer& meter) {
		// Almost unsupported
		// Converting directly to `optional<T>` fails,
		// have to use value_or on the proxy
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		meter.measure([&]() {
			int x = 0;
			for (int i = 0; i < repetition; ++i) {
				int v = lua["warble"]["value"].value_or<int>(1);
				x += v;
			}
			return x;
		});
	}

	void kaguya_return_userdata_measure(nonius::chronometer& meter) {
		kaguya::State lua;
		lua.setErrorHandler(kaguya_panic_throw);

		lua["f"].setFunction(basic_return);
		auto code = repeated_code("b = f(i)");
		meter.measure([&]() {
			if (!lua(code)) {
				lua_error(lua.state());
			}
		});
	}

}
