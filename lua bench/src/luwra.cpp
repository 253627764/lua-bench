#include "lua_bench.hpp"
#include "bench_table.hpp"
#include <luwra.hpp>

namespace lb {

	void global_set_setup( lua_State* L ) {
		luwra::setGlobal(L, lb::table::key_c_str, lb::table::value);
	}

	void luwra_global_string_get_measure(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		global_set_setup( L );
		meter.measure([&] {
			return luwra::getGlobal<int>(L, table::key_c_str);
		});
	}

	void luwra_global_string_set_measure(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		meter.measure([&] {
			return luwra::setGlobal(L, table::key_c_str, table::key_int);
		});
	}

	void luwra_chained_get_measure(nonius::chronometer& meter) {
		lua_State* L = lua_newstate(nullptr, nullptr);
		meter.measure([&] {
			return luwra::setFields(L, table::key_c_str, table::key_int);
		});
	}

	void luwra_chained_set_measure(nonius::chronometer& meter) {

	}

	void luwra_table_get_measure(nonius::chronometer& meter) {

	}

	void luwra_table_set_measure(nonius::chronometer& meter) {

	}

	void luwra_c_function_measure(nonius::chronometer& meter) {

	}

	void luwra_lua_function_measure(nonius::chronometer& meter) {

	}

	void luwra_c_through_lua_function_measure(nonius::chronometer& meter) {

	}

	void luwra_member_function_call(nonius::chronometer& meter) {

	}

	void luwra_member_variable_set(nonius::chronometer& meter) {

	}

	void luwra_member_variable_get(nonius::chronometer& meter) {

	}

}
