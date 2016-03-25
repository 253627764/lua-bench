#include "lua_bench.hpp"
#include <selene.h>

namespace lb {

	void selene_global_string_get_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua["value"] = 24;
		meter.measure([&](int i) {
			int x = lua["value"];
			return x;
		});
	}

	void selene_global_string_set_measure(nonius::chronometer& meter) {
		sel::State lua;
		meter.measure([&](int i) {
			lua["value"] = i;
		});
	}

	void selene_chained_get_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua["value"]["warble"] = 24;
		meter.measure([&](int i) {
			int x = lua["value"]["warble"];
			return x;
		});
	}

	void selene_chained_set_measure(nonius::chronometer& meter) {
		sel::State lua;
		meter.measure([&](int i) {
			lua["value"]["warble"] = 24;
		});
	}

	void selene_table_get_measure(nonius::chronometer& meter) {
		sel::State lua;
		auto t = lua["value"];
		t["warble"] = 24;
		meter.measure([&](int i) {
			int x = t["warble"];
			return x;
		});
	}

	void selene_table_set_measure(nonius::chronometer& meter) {
		sel::State lua;
		auto t = lua["value"];
		meter.measure([&](int i) {
			t["warble"] = 24;
		});
	}

	void selene_c_function_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua["f"] = basic_call;
		lua["run"] = 0;
		meter.measure([&](int i) {
			lua(R"(
				f(run)
				run += 1
			)");
		});
	}

	void selene_lua_function_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua(R"(function f (i)
			return i;
		end)");
		sel::function<int(int)> f = lua["f"];
		meter.measure([&](int i) {
			int x = f(i);
			return x;
		});
	}

	void selene_c_through_lua_function_measure(nonius::chronometer& meter) {
		sel::State lua;
		lua["f"] = basic_call;
		sel::function<int(int)> f = lua["f"];
		meter.measure([&](int i) {
			int x = f(i);
			return x;
		});
	}

	void selene_member_function_call(nonius::chronometer& meter) {
		sel::State lua;
		lua["A"].SetClass<basic>(
			"get", &basic::get,
			"set", &basic::set
		);
		lua("b = basic.new()");
		meter.measure([&](int i) {
			lua("b:set(20)\nb:get()");
		});
	}

	void selene_member_variable_set(nonius::chronometer& meter) {
		sel::State lua;
		lua["A"].SetClass<basic>(
			"var", &basic::var,
			"set", &basic::set,
			"get", &basic::get
		);
		lua("b = basic.new()");
		meter.measure([&](int i) {
			lua("b:set_var(20)");
		});
	}

	void selene_member_variable_get(nonius::chronometer& meter) {
		sel::State lua;
		lua["basic"].SetClass<basic>(
			"var", &basic::var,
			"set", &basic::set,
			"get", &basic::get
			);
		lua("b = basic.new()");
		meter.measure([&](int i) {
			lua("b:var()");
		});
	}

}
