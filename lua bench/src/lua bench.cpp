#include "lua bench.hpp"
#include <nonius.h++>

int main(int argc, char* argv[]) {
	static const char global_string_get_measure_name[] = "global get";
	static const char global_string_set_measure_name[] = "global set";
	static const char table_get_measure_name[] = "table get";
	static const char table_set_measure_name[] = "table set";
	static const char table_chained_get_measure_name[] = "table chained get";
	static const char table_chained_set_measure_name[] = "table chained set";
	static const char c_function_measure_name[] = "c function";
	static const char c_through_lua_function_measure_name[] = "c function through lua";
	static const char lua_function_measure_name[] = "lua function";
	static const char member_function_call_measure_name[] = "member function calls";
	static const char userdata_variable_access_measure_name[] = "userdata variable access";
	static const char userdata_variable_access_large_measure_name[] = "many userdata variables access";
	static const char userdata_variable_access_last_measure_name[] = "many userdata variables access, last registered";
	static const char member_function_call_simple_measure_name[] = "member function calls (simple)";
	static const char userdata_variable_access_simple_measure_name[] = "userdata variable access (simple)";
	static const char userdata_variable_access_large_simple_measure_name[] = "many userdata variable access (simple)";
	static const char userdata_variable_access_last_simple_measure_name[] = "many userdata variables access, last registered (simple)";
	static const char multi_return_measure_name[] = "multi return";
	static const char stateful_function_object_measure_name[] = "stateful c function";
	static const char base_derived_measure_name[] = "base from derived";
	static const char return_userdata_measure_name[] = "return userdata";
	static const char optional_measure_name[] = "get optional";
	static const char implicit_inheritance_call_measure_name[] = "base call on derived";

	static const std::string kaguya_name = "kaguya";
	static const std::string lua_api_pp_name = "lua-api-pp";
	static const std::string luabind_name = "luabind";
	static const std::string luacppinterface_name = "luacppinterface";
	static const std::string lua_intf_name = "lua intf";
	static const std::string luawrapper_name = "luawrapper";
	static const std::string luwra_name = "luwra";
	static const std::string oolua_name = "oolua";
	static const std::string plain_c_name = "plain_c";
	static const std::string selene_name = "selene";
	static const std::string slb3_name = "slb3";
	static const std::string sol_name = "sol";
	static const std::string old_sol_name = "old sol";
	static const std::string swig_name = "swig";
	static const std::string lualite_name = "lualite";

#if _DEBUG
	static const bool do_kaguya = true;
	static const bool do_lua_api_pp = true;
	static const bool do_luabind = true;
	static const bool do_luacppinterface = true;
	static const bool do_lua_intf = true;
	static const bool do_luawrapper = true;
	static const bool do_luwra = true;
	static const bool do_oolua = true;
	static const bool do_plain_c = true;
	static const bool do_selene = true;
	static const bool do_slb3 = true;
	static const bool do_sol = true;
	static const bool do_old_sol = true;
	static const bool do_swig = true;
	static const bool do_lualite = true;
#else
	static const bool do_kaguya = true;
	static const bool do_lua_api_pp = true;
	static const bool do_luabind = true;
	static const bool do_luacppinterface = true;
	static const bool do_lua_intf = true;
	static const bool do_luawrapper = true;
	static const bool do_luwra = true;
	static const bool do_oolua = true;
	static const bool do_plain_c = true;
	static const bool do_selene = true;
	static const bool do_slb3 = true;
	static const bool do_sol = true;
	static const bool do_old_sol = true;
	static const bool do_swig = true;
	static const bool do_lualite = true;
#endif
	nonius::configuration rootcfg{};
	rootcfg.summary = true;
	rootcfg.output_file = "lua bench tests";
	rootcfg.title = "lua bench tests";
	rootcfg.verbose = true;
#ifdef _DEBUG
	rootcfg.samples = 1;
	rootcfg.resamples = 1;
#else
	rootcfg.samples = 600;
	rootcfg.resamples = 600;
#endif

	if (do_plain_c) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(plain_c_name + " - " + global_string_get_measure_name, lb::plain_c_global_string_get_measure),
			nonius::benchmark(plain_c_name + " - " + global_string_set_measure_name, lb::plain_c_global_string_set_measure),
			nonius::benchmark(plain_c_name + " - " + table_get_measure_name, lb::plain_c_table_get_measure),
			nonius::benchmark(plain_c_name + " - " + table_set_measure_name, lb::plain_c_table_set_measure),
			nonius::benchmark(plain_c_name + " - " + table_chained_get_measure_name, lb::plain_c_chained_get_measure),
			nonius::benchmark(plain_c_name + " - " + table_chained_set_measure_name, lb::plain_c_chained_set_measure),
			nonius::benchmark(plain_c_name + " - " + c_function_measure_name, lb::plain_c_c_function_measure),
			nonius::benchmark(plain_c_name + " - " + c_through_lua_function_measure_name, lb::plain_c_c_through_lua_function_measure),
			nonius::benchmark(plain_c_name + " - " + lua_function_measure_name, lb::plain_c_lua_function_measure),
			nonius::benchmark(plain_c_name + " - " + member_function_call_measure_name, lb::plain_c_member_function_call_measure),
			nonius::benchmark(plain_c_name + " - " + member_function_call_simple_measure_name, lb::plain_c_member_function_call_measure),
			nonius::benchmark(plain_c_name + " - " + userdata_variable_access_measure_name, lb::plain_c_userdata_variable_access_measure),
			nonius::benchmark(plain_c_name + " - " + userdata_variable_access_simple_measure_name, lb::plain_c_userdata_variable_access_measure),
			nonius::benchmark(plain_c_name + " - " + userdata_variable_access_large_measure_name, lb::plain_c_userdata_variable_access_large_measure),
			nonius::benchmark(plain_c_name + " - " + userdata_variable_access_large_simple_measure_name, lb::plain_c_userdata_variable_access_large_measure),
			nonius::benchmark(plain_c_name + " - " + userdata_variable_access_last_measure_name, lb::plain_c_userdata_variable_access_last_measure),
			nonius::benchmark(plain_c_name + " - " + userdata_variable_access_last_simple_measure_name, lb::plain_c_userdata_variable_access_last_measure),
			nonius::benchmark(plain_c_name + " - " + multi_return_measure_name, lb::plain_c_multi_return_measure),
			nonius::benchmark(plain_c_name + " - " + stateful_function_object_measure_name, lb::plain_c_stateful_function_object_measure),
			nonius::benchmark(plain_c_name + " - " + base_derived_measure_name, lb::plain_c_base_derived_measure),
			nonius::benchmark(plain_c_name + " - " + return_userdata_measure_name, lb::plain_c_return_userdata_measure),
			nonius::benchmark(plain_c_name + " - " + optional_measure_name, lb::plain_c_optional_measure),
			nonius::benchmark(plain_c_name + " - " + implicit_inheritance_call_measure_name, lb::plain_c_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " plain C";
		cfg.output_file += " plain C.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}

	if (do_sol) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(sol_name + " - " + global_string_get_measure_name, lb::sol_global_string_get_measure),
			nonius::benchmark(sol_name + " - " + global_string_set_measure_name, lb::sol_global_string_set_measure),
			nonius::benchmark(sol_name + " - " + table_get_measure_name, lb::sol_table_get_measure),
			nonius::benchmark(sol_name + " - " + table_set_measure_name, lb::sol_table_set_measure),
			nonius::benchmark(sol_name + " - " + table_chained_get_measure_name, lb::sol_chained_get_measure),
			nonius::benchmark(sol_name + " - " + table_chained_set_measure_name, lb::sol_chained_set_measure),
			nonius::benchmark(sol_name + " - " + c_function_measure_name, lb::sol_c_function_measure),
			nonius::benchmark(sol_name + " - " + c_through_lua_function_measure_name, lb::sol_c_through_lua_function_measure),
			nonius::benchmark(sol_name + " - " + lua_function_measure_name, lb::sol_lua_function_measure),
			nonius::benchmark(sol_name + " - " + member_function_call_measure_name, lb::sol_member_function_call_measure),
			nonius::benchmark(sol_name + " - " + member_function_call_simple_measure_name, lb::sol_member_function_call_simple_measure),
			nonius::benchmark(sol_name + " - " + userdata_variable_access_measure_name, lb::sol_userdata_variable_access_measure),
			nonius::benchmark(sol_name + " - " + userdata_variable_access_large_measure_name, lb::sol_userdata_variable_access_complex_measure),
			nonius::benchmark(sol_name + " - " + userdata_variable_access_last_measure_name, lb::sol_userdata_variable_access_last_measure),
			nonius::benchmark(sol_name + " - " + userdata_variable_access_simple_measure_name, lb::sol_userdata_variable_access_simple_measure),
			nonius::benchmark(sol_name + " - " + userdata_variable_access_large_simple_measure_name, lb::sol_userdata_variable_access_complex_simple_measure),
			nonius::benchmark(sol_name + " - " + userdata_variable_access_last_simple_measure_name, lb::sol_userdata_variable_access_last_simple_measure),
			nonius::benchmark(sol_name + " - " + multi_return_measure_name, lb::sol_multi_return_measure),
			nonius::benchmark(sol_name + " - " + stateful_function_object_measure_name, lb::sol_stateful_function_object_measure),
			nonius::benchmark(sol_name + " - " + base_derived_measure_name, lb::sol_base_derived_measure),
			nonius::benchmark(sol_name + " - " + return_userdata_measure_name, lb::sol_return_userdata_measure),
			nonius::benchmark(sol_name + " - " + optional_measure_name, lb::sol_optional_measure),
			nonius::benchmark(sol_name + " - " + implicit_inheritance_call_measure_name, lb::sol_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " sol";
		cfg.output_file += " sol.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}

	if (do_old_sol) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(old_sol_name + " - " + global_string_get_measure_name, lb::old_sol_global_string_get_measure),
			nonius::benchmark(old_sol_name + " - " + global_string_set_measure_name, lb::old_sol_global_string_set_measure),
			nonius::benchmark(old_sol_name + " - " + table_get_measure_name, lb::old_sol_table_get_measure),
			nonius::benchmark(old_sol_name + " - " + table_set_measure_name, lb::old_sol_table_set_measure),
			nonius::benchmark(old_sol_name + " - " + table_chained_get_measure_name, lb::old_sol_chained_get_measure),
			nonius::benchmark(old_sol_name + " - " + table_chained_set_measure_name, lb::old_sol_chained_set_measure),
			nonius::benchmark(old_sol_name + " - " + c_function_measure_name, lb::old_sol_c_function_measure),
			nonius::benchmark(old_sol_name + " - " + c_through_lua_function_measure_name, lb::old_sol_c_through_lua_function_measure),
			nonius::benchmark(old_sol_name + " - " + lua_function_measure_name, lb::old_sol_lua_function_measure),
			nonius::benchmark(old_sol_name + " - " + member_function_call_measure_name, lb::old_sol_member_function_call_measure),
			nonius::benchmark(old_sol_name + " - " + member_function_call_simple_measure_name, lb::old_sol_member_function_call_measure),
			nonius::benchmark(old_sol_name + " - " + userdata_variable_access_measure_name, lb::old_sol_userdata_variable_access_measure),
			nonius::benchmark(old_sol_name + " - " + userdata_variable_access_large_measure_name, lb::old_sol_userdata_variable_access_complex_measure),
			nonius::benchmark(old_sol_name + " - " + userdata_variable_access_last_measure_name, lb::old_sol_userdata_variable_access_last_measure),
			nonius::benchmark(old_sol_name + " - " + userdata_variable_access_simple_measure_name, lb::old_sol_userdata_variable_access_measure),
			nonius::benchmark(old_sol_name + " - " + userdata_variable_access_large_simple_measure_name, lb::old_sol_userdata_variable_access_complex_measure),
			nonius::benchmark(old_sol_name + " - " + userdata_variable_access_last_simple_measure_name, lb::old_sol_userdata_variable_access_last_measure),
			nonius::benchmark(old_sol_name + " - " + multi_return_measure_name, lb::old_sol_multi_return_measure),
			nonius::benchmark(old_sol_name + " - " + stateful_function_object_measure_name, lb::old_sol_stateful_function_object_measure),
			//nonius::benchmark(old_sol_name + " - " + base_derived_measure_name, lb::old_sol_base_derived_measure),
			nonius::benchmark(old_sol_name + " - " + return_userdata_measure_name, lb::old_sol_return_userdata_measure),
			//nonius::benchmark(old_sol_name + " - " + optional_measure_name, lb::old_sol_optional_measure),
			//nonius::benchmark(old_sol_name + " - " + implicit_inheritance_call_measure_name, lb::old_sol_implicit_inheritance_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " old-sol";
		cfg.output_file += " old-sol.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}

	if (do_selene) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(selene_name + " - " + global_string_get_measure_name, lb::selene_global_string_get_measure),
			nonius::benchmark(selene_name + " - " + global_string_set_measure_name, lb::selene_global_string_set_measure),
			nonius::benchmark(selene_name + " - " + table_get_measure_name, lb::selene_table_get_measure),
			nonius::benchmark(selene_name + " - " + table_set_measure_name, lb::selene_table_set_measure),
			nonius::benchmark(selene_name + " - " + table_chained_get_measure_name, lb::selene_chained_get_measure),
			nonius::benchmark(selene_name + " - " + table_chained_set_measure_name, lb::selene_chained_set_measure),
			nonius::benchmark(selene_name + " - " + c_function_measure_name, lb::selene_c_function_measure),
			nonius::benchmark(selene_name + " - " + c_through_lua_function_measure_name, lb::selene_c_through_lua_function_measure),
			nonius::benchmark(selene_name + " - " + lua_function_measure_name, lb::selene_lua_function_measure),
			nonius::benchmark(selene_name + " - " + member_function_call_measure_name, lb::selene_member_function_call_measure),
			nonius::benchmark(selene_name + " - " + member_function_call_simple_measure_name, lb::selene_member_function_call_measure),
			//nonius::benchmark(selene_name + " - " + userdata_variable_access_measure_name, lb::selene_userdata_variable_access_measure),
			//nonius::benchmark(selene_name + " - " + userdata_variable_access_simple_measure_name, lb::selene_userdata_variable_access_measure),
			//nonius::benchmark(selene_name + " - " + userdata_variable_access_last_measure_name, lb::selene_userdata_variable_access_measure),
			//nonius::benchmark(selene_name + " - " + userdata_variable_access_last_simple_measure_name, lb::selene_userdata_variable_access_measure),
			//nonius::benchmark(selene_name + " - " + userdata_variable_access_large_measure_name, lb::selene_userdata_variable_access_measure),
			//nonius::benchmark(selene_name + " - " + userdata_variable_access_large_simple_measure_name, lb::selene_userdata_variable_access_measure),
			nonius::benchmark(selene_name + " - " + multi_return_measure_name, lb::selene_multi_return_measure),
			nonius::benchmark(selene_name + " - " + stateful_function_object_measure_name, lb::selene_stateful_function_object_measure),
			//nonius::benchmark(selene_name + " - " + base_derived_measure_name, lb::selene_base_derived_measure),
			nonius::benchmark(selene_name + " - " + return_userdata_measure_name, lb::selene_return_userdata_measure),
			//nonius::benchmark(selene_name + " - " + optional_measure_name, lb::selene_optional_measure),
			//nonius::benchmark(selene_name + " - " + implicit_inheritance_call_measure_name, lb::selene_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " selene";
		cfg.output_file += " selene.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	
	if (do_kaguya) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(kaguya_name + " - " + global_string_get_measure_name, lb::kaguya_global_string_get_measure),
			nonius::benchmark(kaguya_name + " - " + global_string_set_measure_name, lb::kaguya_global_string_set_measure),
			nonius::benchmark(kaguya_name + " - " + table_get_measure_name, lb::kaguya_table_get_measure),
			nonius::benchmark(kaguya_name + " - " + table_set_measure_name, lb::kaguya_table_set_measure),
			nonius::benchmark(kaguya_name + " - " + table_chained_get_measure_name, lb::kaguya_chained_get_measure),
			nonius::benchmark(kaguya_name + " - " + table_chained_set_measure_name, lb::kaguya_chained_set_measure),
			nonius::benchmark(kaguya_name + " - " + c_function_measure_name, lb::kaguya_c_function_measure),
			nonius::benchmark(kaguya_name + " - " + c_through_lua_function_measure_name, lb::kaguya_c_through_lua_function_measure),
			nonius::benchmark(kaguya_name + " - " + lua_function_measure_name, lb::kaguya_lua_function_measure),
			nonius::benchmark(kaguya_name + " - " + member_function_call_measure_name, lb::kaguya_member_function_call_measure),
			nonius::benchmark(kaguya_name + " - " + member_function_call_simple_measure_name, lb::kaguya_member_function_call_measure),
			//nonius::benchmark(kaguya_name + " - " + userdata_variable_access_measure_name, lb::kaguya_userdata_variable_access_measure),
			//nonius::benchmark(kaguya_name + " - " + userdata_variable_access_simple_measure_name, lb::kaguya_userdata_variable_access_measure),
			nonius::benchmark(kaguya_name + " - " + multi_return_measure_name, lb::kaguya_multi_return_measure),
			nonius::benchmark(kaguya_name + " - " + stateful_function_object_measure_name, lb::kaguya_stateful_function_object_measure),
			nonius::benchmark(kaguya_name + " - " + base_derived_measure_name, lb::kaguya_base_derived_measure),
			nonius::benchmark(kaguya_name + " - " + optional_measure_name, lb::kaguya_optional_measure),
			nonius::benchmark(kaguya_name + " - " + return_userdata_measure_name, lb::kaguya_return_userdata_measure),
			nonius::benchmark(kaguya_name + " - " + implicit_inheritance_call_measure_name, lb::kaguya_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " kaguya";
		cfg.output_file += " kaguya.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	
	if (do_slb3) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(slb3_name + " - " + global_string_get_measure_name, lb::slb3_global_string_get_measure),
			nonius::benchmark(slb3_name + " - " + global_string_set_measure_name, lb::slb3_global_string_set_measure),
			//nonius::benchmark(slb3_name + " - " + table_get_measure_name, lb::slb3_table_get_measure),
			//nonius::benchmark(slb3_name + " - " + table_set_measure_name, lb::slb3_table_set_measure),
			//nonius::benchmark(slb3_name + " - " + table_chained_get_measure_name, lb::slb3_chained_get_measure),
			//nonius::benchmark(slb3_name + " - " + table_chained_set_measure_name, lb::slb3_chained_set_measure),
			nonius::benchmark(slb3_name + " - " + c_function_measure_name, lb::slb3_c_function_measure),
			//nonius::benchmark(slb3_name + " - " + c_through_lua_function_measure_name, lb::slb3_c_through_lua_function_measure),
			//nonius::benchmark(slb3_name + " - " + lua_function_measure_name, lb::slb3_lua_function_measure),
			nonius::benchmark(slb3_name + " - " + member_function_call_measure_name, lb::slb3_member_function_call_measure),
			nonius::benchmark(slb3_name + " - " + member_function_call_simple_measure_name, lb::slb3_member_function_call_measure),
			//nonius::benchmark(slb3_name + " - " + userdata_variable_access_measure_name, lb::slb3_userdata_variable_access_measure),
			//nonius::benchmark(slb3_name + " - " + multi_return_measure_name, lb::slb3_multi_return_measure),
			//nonius::benchmark(slb3_name + " - " + stateful_function_object_measure_name, lb::slb3_stateful_function_object_measure),
			//nonius::benchmark(slb3_name + " - " + base_derived_measure_name, lb::slb3_base_derived_measure),
			//nonius::benchmark(slb3_name + " - " + optional_measure_name, lb::slb3_optional_measure),
			//nonius::benchmark(slb3_name + " - " + return_userdata_measure_name, lb::slb3_return_userdata_measure),
			//nonius::benchmark(slb3_name + " - " + implicit_inheritance_call_measure_name, lb::slb3_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " slb3";
		cfg.output_file += " slb3.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	
	if (do_luawrapper) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(luawrapper_name + " - " + global_string_get_measure_name, lb::luawrapper_global_string_get_measure),
			nonius::benchmark(luawrapper_name + " - " + global_string_set_measure_name, lb::luawrapper_global_string_set_measure),
			nonius::benchmark(luawrapper_name + " - " + table_get_measure_name, lb::luawrapper_table_get_measure),
			nonius::benchmark(luawrapper_name + " - " + table_set_measure_name, lb::luawrapper_table_set_measure),
			nonius::benchmark(luawrapper_name + " - " + table_chained_get_measure_name, lb::luawrapper_chained_get_measure),
			nonius::benchmark(luawrapper_name + " - " + table_chained_set_measure_name, lb::luawrapper_chained_set_measure),
			nonius::benchmark(luawrapper_name + " - " + c_function_measure_name, lb::luawrapper_c_function_measure),
			nonius::benchmark(luawrapper_name + " - " + c_through_lua_function_measure_name, lb::luawrapper_c_through_lua_function_measure),
			nonius::benchmark(luawrapper_name + " - " + lua_function_measure_name, lb::luawrapper_lua_function_measure),
			nonius::benchmark(luawrapper_name + " - " + member_function_call_measure_name, lb::luawrapper_member_function_call_measure),
			nonius::benchmark(luawrapper_name + " - " + member_function_call_simple_measure_name, lb::luawrapper_member_function_call_measure),
			nonius::benchmark(luawrapper_name + " - " + userdata_variable_access_measure_name, lb::luawrapper_userdata_variable_access_measure),
			nonius::benchmark(luawrapper_name + " - " + userdata_variable_access_large_measure_name, lb::luawrapper_userdata_variable_access_complex_measure),
			nonius::benchmark(luawrapper_name + " - " + userdata_variable_access_last_measure_name, lb::luawrapper_userdata_variable_access_last_measure),
			nonius::benchmark(luawrapper_name + " - " + userdata_variable_access_simple_measure_name, lb::luawrapper_userdata_variable_access_measure),
			nonius::benchmark(luawrapper_name + " - " + userdata_variable_access_large_simple_measure_name, lb::luawrapper_userdata_variable_access_complex_measure),
			nonius::benchmark(luawrapper_name + " - " + userdata_variable_access_last_simple_measure_name, lb::luawrapper_userdata_variable_access_last_measure),
			nonius::benchmark(luawrapper_name + " - " + multi_return_measure_name, lb::luawrapper_multi_return_measure),
			nonius::benchmark(luawrapper_name + " - " + stateful_function_object_measure_name, lb::luawrapper_stateful_function_object_measure),
			//nonius::benchmark(luawrapper_name + " - " + base_derived_measure_name, lb::luawrapper_base_derived_measure),
			nonius::benchmark(luawrapper_name + " - " + return_userdata_measure_name, lb::luawrapper_return_userdata_measure),
			//nonius::benchmark(luawrapper_name + " - " + optional_measure_name, lb::luawrapper_optional_measure),
			//nonius::benchmark(luawrapper_name + " - " + implicit_inheritance_call_measure_name, lb::luawrapper_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " luawrapper";
		cfg.output_file += " luawrapper.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	
	if (do_swig) {
		nonius::benchmark benchmarks[] = {
			//nonius::benchmark(swig_name + " - " + global_string_get_measure_name, lb::swig_global_string_get_measure),
			//nonius::benchmark(swig_name + " - " + global_string_set_measure_name, lb::swig_global_string_set_measure),
			//nonius::benchmark(swig_name + " - " + table_get_measure_name, lb::swig_table_get_measure),
			//nonius::benchmark(vtable_set_measure_name, lb::swig_table_set_measure),
			//nonius::benchmark(vtable_chained_get_measure_name, lb::swig_chained_get_measure),
			//nonius::benchmark(swig_name + " - " + table_chained_set_measure_name, lb::swig_chained_set_measure),
			nonius::benchmark(swig_name + " - " + c_function_measure_name, lb::swig_c_function_measure),
			nonius::benchmark(swig_name + " - " + c_through_lua_function_measure_name, lb::swig_c_through_lua_function_measure),
			nonius::benchmark(swig_name + " - " + lua_function_measure_name, lb::swig_lua_function_measure),
			nonius::benchmark(swig_name + " - " + member_function_call_measure_name, lb::swig_member_function_call_measure),
			nonius::benchmark(swig_name + " - " + member_function_call_simple_measure_name, lb::swig_member_function_call_measure),
			nonius::benchmark(swig_name + " - " + userdata_variable_access_measure_name, lb::swig_userdata_variable_access_measure),
			nonius::benchmark(swig_name + " - " + userdata_variable_access_large_measure_name, lb::swig_userdata_variable_access_complex_measure),
			nonius::benchmark(swig_name + " - " + userdata_variable_access_last_measure_name, lb::swig_userdata_variable_access_last_measure),
			nonius::benchmark(swig_name + " - " + userdata_variable_access_simple_measure_name, lb::swig_userdata_variable_access_measure),
			nonius::benchmark(swig_name + " - " + userdata_variable_access_large_simple_measure_name, lb::swig_userdata_variable_access_complex_measure),
			nonius::benchmark(swig_name + " - " + userdata_variable_access_last_simple_measure_name, lb::swig_userdata_variable_access_last_measure),
			//nonius::benchmark(swig_name + " - " + multi_return_measure_name, lb::swig_multi_return_measure),
			//nonius::benchmark(swig_name + " - " + stateful_function_object_measure_name, lb::swig_stateful_function_object_measure),
			//nonius::benchmark(swig_name + " - " + base_derived_measure_name, lb::swig_base_derived_measure),
			nonius::benchmark(swig_name + " - " + return_userdata_measure_name, lb::swig_return_userdata_measure),
			//nonius::benchmark(swig_name + " - " + optional_measure_name, lb::swig_optional_measure),
			//nonius::benchmark(swig_name + " - " + implicit_inheritance_call_measure_name, lb::swig_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " swig";
		cfg.output_file += " swig.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	
	if (do_oolua) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(oolua_name + " - " + global_string_get_measure_name, lb::oolua_global_string_get_measure),
			nonius::benchmark(oolua_name + " - " + global_string_set_measure_name, lb::oolua_global_string_set_measure),
			nonius::benchmark(oolua_name + " - " + table_get_measure_name, lb::oolua_table_get_measure),
			nonius::benchmark(oolua_name + " - " + table_set_measure_name, lb::oolua_table_set_measure),
			nonius::benchmark(oolua_name + " - " + table_chained_get_measure_name, lb::oolua_chained_get_measure),
			nonius::benchmark(oolua_name + " - " + table_chained_set_measure_name, lb::oolua_chained_set_measure),
			nonius::benchmark(oolua_name + " - " + c_function_measure_name, lb::oolua_c_function_measure),
			nonius::benchmark(oolua_name + " - " + c_through_lua_function_measure_name, lb::oolua_c_through_lua_function_measure),
			nonius::benchmark(oolua_name + " - " + lua_function_measure_name, lb::oolua_lua_function_measure),
			nonius::benchmark(oolua_name + " - " + member_function_call_measure_name, lb::oolua_member_function_call_measure),
			nonius::benchmark(oolua_name + " - " + member_function_call_simple_measure_name, lb::oolua_member_function_call_measure),
			//nonius::benchmark(oolua_name + " - " + userdata_variable_access_measure_name, lb::oolua_userdata_variable_access_measure),
			//nonius::benchmark(oolua_name + " - " + userdata_variable_access_simple_measure_name, lb::oolua_userdata_variable_access_measure),
			//nonius::benchmark(oolua_name + " - " + multi_return_measure_name, lb::oolua_multi_return_measure),
			//nonius::benchmark(oolua_name + " - " + stateful_function_object_measure_name, lb::oolua_stateful_function_object_measure),
			//nonius::benchmark(oolua_name + " - " + base_derived_measure_name, lb::oolua_base_derived_measure),
			nonius::benchmark(oolua_name + " - " + return_userdata_measure_name, lb::oolua_return_userdata_measure),
			//nonius::benchmark(oolua_name + " - " + optional_measure_name, lb::oolua_optional_measure),
			nonius::benchmark(oolua_name + " - " + implicit_inheritance_call_measure_name, lb::oolua_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " oolua";
		cfg.output_file += " oolua.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	
	if (do_luacppinterface) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(luacppinterface_name + " - " + global_string_get_measure_name, lb::luacppinterface_global_string_get_measure),
			nonius::benchmark(luacppinterface_name + " - " + global_string_set_measure_name, lb::luacppinterface_global_string_set_measure),
			nonius::benchmark(luacppinterface_name + " - " + table_get_measure_name, lb::luacppinterface_table_get_measure),
			nonius::benchmark(luacppinterface_name + " - " + table_set_measure_name, lb::luacppinterface_table_set_measure),
			nonius::benchmark(luacppinterface_name + " - " + table_chained_get_measure_name, lb::luacppinterface_chained_get_measure),
			nonius::benchmark(luacppinterface_name + " - " + table_chained_set_measure_name, lb::luacppinterface_chained_set_measure),
			nonius::benchmark(luacppinterface_name + " - " + c_function_measure_name, lb::luacppinterface_c_function_measure),
			nonius::benchmark(luacppinterface_name + " - " + c_through_lua_function_measure_name, lb::luacppinterface_c_through_lua_function_measure),
			nonius::benchmark(luacppinterface_name + " - " + lua_function_measure_name, lb::luacppinterface_lua_function_measure),
			nonius::benchmark(luacppinterface_name + " - " + member_function_call_measure_name, lb::luacppinterface_member_function_call_measure),
			nonius::benchmark(luacppinterface_name + " - " + member_function_call_simple_measure_name, lb::luacppinterface_member_function_call_measure),
			//nonius::benchmark(luacppinterface_name + " - " + userdata_variable_access_measure_name, lb::luacppinterface_userdata_variable_access_measure),
			//nonius::benchmark(luacppinterface_name + " - " + userdata_variable_access_simple_measure_name, lb::luacppinterface_userdata_variable_access_measure),
			//nonius::benchmark(luacppinterface_name + " - " + multi_return_measure_name, lb::luacppinterface_multi_return_measure),
			//nonius::benchmark(luacppinterface_name + " - " + stateful_function_object_measure_name, lb::luacppinterface_stateful_function_object_measure),
			//nonius::benchmark(luacppinterface_name + " - " + base_derived_measure_name, lb::luacppinterface_base_derived_measure),
			nonius::benchmark(luacppinterface_name + " - " + return_userdata_measure_name, lb::luacppinterface_return_userdata_measure),
			//nonius::benchmark(luacppinterface_name + " - " + optional_measure_name, lb::luacppinterface_optional_measure),
			//nonius::benchmark(luacppinterface_name + " - " + implicit_inheritance_call_measure_name, lb::luacppinterface_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " luacppinterface";
		cfg.output_file += " luacppinterface.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}

	if (do_luwra) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(luwra_name + " - " + global_string_get_measure_name, lb::luwra_global_string_get_measure),
			nonius::benchmark(luwra_name + " - " + global_string_set_measure_name, lb::luwra_global_string_set_measure),
			nonius::benchmark(luwra_name + " - " + table_get_measure_name, lb::luwra_table_get_measure),
			nonius::benchmark(luwra_name + " - " + table_set_measure_name, lb::luwra_table_set_measure),
			nonius::benchmark(luwra_name + " - " + table_chained_get_measure_name, lb::luwra_chained_get_measure),
			nonius::benchmark(luwra_name + " - " + table_chained_set_measure_name, lb::luwra_chained_set_measure),
			nonius::benchmark(luwra_name + " - " + c_function_measure_name, lb::luwra_c_function_measure),
			nonius::benchmark(luwra_name + " - " + c_through_lua_function_measure_name, lb::luwra_c_through_lua_function_measure),
			nonius::benchmark(luwra_name + " - " + lua_function_measure_name, lb::luwra_lua_function_measure),
			nonius::benchmark(luwra_name + " - " + member_function_call_measure_name, lb::luwra_member_function_call_measure),
			nonius::benchmark(luwra_name + " - " + member_function_call_simple_measure_name, lb::luwra_member_function_call_measure),
			//nonius::benchmark(luwra_name + " - " + userdata_variable_access_measure_name, lb::luwra_userdata_variable_access_measure),
			//nonius::benchmark(luwra_name + " - " + userdata_variable_access_simple_measure_name, lb::luwra_userdata_variable_access_simple_measure),
			//nonius::benchmark(luwra_name + " - " + multi_return_measure_name, lb::luwra_multi_return_measure),
			nonius::benchmark(luwra_name + " - " + stateful_function_object_measure_name, lb::luwra_stateful_function_object_measure),
			//nonius::benchmark(luwra_name + " - " + base_derived_measure_name, lb::luwra_base_derived_measure),
			//nonius::benchmark(luwra_name + " - " + return_userdata_measure_name, lb::luwra_return_userdata_measure),
			//nonius::benchmark(luwra_name + " - " + optional_measure_name, lb::luwra_optional_measure),
			//nonius::benchmark(luwra_name + " - " + implicit_inheritance_call_measure_name, lb::luwra_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " luwra";
		cfg.output_file += " luwra.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	
	if (do_lua_api_pp) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(lua_api_pp_name + " - " + global_string_get_measure_name, lb::lua_api_pp_global_string_get_measure),
			nonius::benchmark(lua_api_pp_name + " - " + global_string_set_measure_name, lb::lua_api_pp_global_string_set_measure),
			nonius::benchmark(lua_api_pp_name + " - " + table_get_measure_name, lb::lua_api_pp_table_get_measure),
			nonius::benchmark(lua_api_pp_name + " - " + table_set_measure_name, lb::lua_api_pp_table_set_measure),
			nonius::benchmark(lua_api_pp_name + " - " + table_chained_get_measure_name, lb::lua_api_pp_chained_get_measure),
			nonius::benchmark(lua_api_pp_name + " - " + table_chained_set_measure_name, lb::lua_api_pp_chained_set_measure),
			nonius::benchmark(lua_api_pp_name + " - " + c_function_measure_name, lb::lua_api_pp_c_function_measure),
			nonius::benchmark(lua_api_pp_name + " - " + c_through_lua_function_measure_name, lb::lua_api_pp_c_through_lua_function_measure),
			nonius::benchmark(lua_api_pp_name + " - " + lua_function_measure_name, lb::lua_api_pp_lua_function_measure),
			nonius::benchmark(lua_api_pp_name + " - " + member_function_call_measure_name, lb::lua_api_pp_member_function_call_measure),
			nonius::benchmark(lua_api_pp_name + " - " + member_function_call_simple_measure_name, lb::lua_api_pp_member_function_call_measure),
			//nonius::benchmark(lua_api_pp_name + " - " + userdata_variable_access_measure_name, lb::lua_api_pp_userdata_variable_access_measure),
			//nonius::benchmark(lua_api_pp_name + " - " + userdata_variable_access_simple_measure_name, lb::lua_api_pp_userdata_variable_access_measure),
			nonius::benchmark(lua_api_pp_name + " - " + multi_return_measure_name, lb::lua_api_pp_multi_return_measure),
			//nonius::benchmark(lua_api_pp_name + " - " + stateful_function_object_measure_name, lb::lua_api_pp_stateful_function_object_measure),
			//nonius::benchmark(lua_api_pp_name + " - " + base_derived_measure_name, lb::lua_api_pp_base_derived_measure),
			nonius::benchmark(lua_api_pp_name + " - " + return_userdata_measure_name, lb::lua_api_pp_return_userdata_measure),
			//nonius::benchmark(lua_api_pp_name + " - " + optional_measure_name, lb::lua_api_pp_optional_measure),
			//nonius::benchmark(lua_api_pp_name + " - " + implicit_inheritance_call_measure_name, lb::lua_api_pp_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " lua-api-pp";
		cfg.output_file += " lua-api-pp.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}

	if (do_luabind) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(luabind_name + " - " + global_string_get_measure_name, lb::luabind_global_string_get_measure),
			nonius::benchmark(luabind_name + " - " + global_string_set_measure_name, lb::luabind_global_string_set_measure),
			nonius::benchmark(luabind_name + " - " + table_get_measure_name, lb::luabind_table_get_measure),
			nonius::benchmark(luabind_name + " - " + table_set_measure_name, lb::luabind_table_set_measure),
			nonius::benchmark(luabind_name + " - " + table_chained_get_measure_name, lb::luabind_chained_get_measure),
			nonius::benchmark(luabind_name + " - " + table_chained_set_measure_name, lb::luabind_chained_set_measure),
			nonius::benchmark(luabind_name + " - " + c_function_measure_name, lb::luabind_c_function_measure),
			nonius::benchmark(luabind_name + " - " + c_through_lua_function_measure_name, lb::luabind_c_through_lua_function_measure),
			nonius::benchmark(luabind_name + " - " + lua_function_measure_name, lb::luabind_lua_function_measure),
			nonius::benchmark(luabind_name + " - " + member_function_call_measure_name, lb::luabind_member_function_call_measure),
			nonius::benchmark(luabind_name + " - " + member_function_call_simple_measure_name, lb::luabind_member_function_call_measure),
			nonius::benchmark(luabind_name + " - " + userdata_variable_access_measure_name, lb::luabind_userdata_variable_access_measure),
			nonius::benchmark(luabind_name + " - " + userdata_variable_access_large_measure_name, lb::luabind_userdata_variable_access_complex_measure),
			nonius::benchmark(luabind_name + " - " + userdata_variable_access_last_measure_name, lb::luabind_userdata_variable_access_last_measure),
			nonius::benchmark(luabind_name + " - " + userdata_variable_access_simple_measure_name, lb::luabind_userdata_variable_access_measure),
			nonius::benchmark(luabind_name + " - " + userdata_variable_access_large_simple_measure_name, lb::luabind_userdata_variable_access_complex_measure),
			nonius::benchmark(luabind_name + " - " + userdata_variable_access_last_simple_measure_name, lb::luabind_userdata_variable_access_last_measure),
			//nonius::benchmark(luabind_name + " - " + multi_return_measure_name, lb::luabind_multi_return_measure),
			nonius::benchmark(luabind_name + " - " + stateful_function_object_measure_name, lb::luabind_stateful_function_object_measure),
			//nonius::benchmark(luabind_name + " - " + base_derived_measure_name, lb::luabind_base_derived_measure),
			nonius::benchmark(luabind_name + " - " + return_userdata_measure_name, lb::luabind_return_userdata_measure),
			//nonius::benchmark(luabind_name + " - " + optional_measure_name, lb::luabind_optional_measure),
			//nonius::benchmark(luabind_name + " - " + implicit_inheritance_call_measure_name, lb::luabind_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " luabind";
		cfg.output_file += " luabind.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}

	if (do_lua_intf) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(lua_intf_name + " - " + global_string_get_measure_name, lb::lua_intf_global_string_get_measure),
			nonius::benchmark(lua_intf_name + " - " + global_string_set_measure_name, lb::lua_intf_global_string_set_measure),
			nonius::benchmark(lua_intf_name + " - " + table_get_measure_name, lb::lua_intf_table_get_measure),
			nonius::benchmark(lua_intf_name + " - " + table_set_measure_name, lb::lua_intf_table_set_measure),
			nonius::benchmark(lua_intf_name + " - " + table_chained_get_measure_name, lb::lua_intf_chained_get_measure),
			nonius::benchmark(lua_intf_name + " - " + table_chained_set_measure_name, lb::lua_intf_chained_set_measure),
			nonius::benchmark(lua_intf_name + " - " + c_function_measure_name, lb::lua_intf_c_function_measure),
			nonius::benchmark(lua_intf_name + " - " + c_through_lua_function_measure_name, lb::lua_intf_c_through_lua_function_measure),
			nonius::benchmark(lua_intf_name + " - " + lua_function_measure_name, lb::lua_intf_lua_function_measure),
			nonius::benchmark(lua_intf_name + " - " + member_function_call_measure_name, lb::lua_intf_member_function_call_measure),
			nonius::benchmark(lua_intf_name + " - " + member_function_call_simple_measure_name, lb::lua_intf_member_function_call_measure),
			nonius::benchmark(lua_intf_name + " - " + userdata_variable_access_measure_name, lb::lua_intf_userdata_variable_access_measure),
			nonius::benchmark(lua_intf_name + " - " + userdata_variable_access_large_measure_name, lb::lua_intf_userdata_variable_access_complex_measure),
			nonius::benchmark(lua_intf_name + " - " + userdata_variable_access_last_measure_name, lb::lua_intf_userdata_variable_access_last_measure),
			nonius::benchmark(lua_intf_name + " - " + userdata_variable_access_simple_measure_name, lb::lua_intf_userdata_variable_access_measure),
			nonius::benchmark(lua_intf_name + " - " + userdata_variable_access_large_simple_measure_name, lb::lua_intf_userdata_variable_access_complex_measure),
			nonius::benchmark(lua_intf_name + " - " + userdata_variable_access_last_simple_measure_name, lb::lua_intf_userdata_variable_access_last_measure),
			nonius::benchmark(lua_intf_name + " - " + multi_return_measure_name, lb::lua_intf_multi_return_measure),
			nonius::benchmark(lua_intf_name + " - " + stateful_function_object_measure_name, lb::lua_intf_stateful_function_object_measure),
			//nonius::benchmark(lua_intf_name + " - " + base_derived_measure_name, lb::lua_intf_base_derived_measure),
			nonius::benchmark(lua_intf_name + " - " + return_userdata_measure_name, lb::lua_intf_return_userdata_measure),
			nonius::benchmark(lua_intf_name + " - " + optional_measure_name, lb::lua_intf_optional_measure),
			//nonius::benchmark(lua_intf_name + " - " + implicit_inheritance_call_measure_name, lb::lua_intf_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " lua-intf";
		cfg.output_file += " lua-intf.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}

	/*
	if (do_lualite) {
		nonius::benchmark benchmarks[] = {
			nonius::benchmark(lualite_name + " - " + global_string_get_measure_name, lb::lualite_global_string_get_measure),
			nonius::benchmark(lualite_name + " - " + global_string_set_measure_name, lb::lualite_global_string_set_measure),
			nonius::benchmark(lualite_name + " - " + table_get_measure_name, lb::lualite_table_get_measure),
			nonius::benchmark(lualite_name + " - " + table_set_measure_name, lb::lualite_table_set_measure),
			nonius::benchmark(lualite_name + " - " + table_chained_get_measure_name, lb::lualite_chained_get_measure),
			nonius::benchmark(lualite_name + " - " + table_chained_set_measure_name, lb::lualite_chained_set_measure),
			nonius::benchmark(lualite_name + " - " + c_function_measure_name, lb::lualite_c_function_measure),
			nonius::benchmark(lualite_name + " - " + c_through_lua_function_measure_name, lb::lualite_c_through_lua_function_measure),
			nonius::benchmark(lualite_name + " - " + lua_function_measure_name, lb::lualite_lua_function_measure),
			nonius::benchmark(lualite_name + " - " + member_function_call_measure_name, lb::lualite_member_function_call_measure),
			nonius::benchmark(lualite_name + " - " + member_function_call_simple_measure_name, lb::lualite_member_function_call_measure),
			nonius::benchmark(lualite_name + " - " + userdata_variable_access_measure_name, lb::lualite_userdata_variable_access_measure),
			nonius::benchmark(lualite_name + " - " + userdata_variable_access_large_measure_name, lb::lualite_userdata_variable_access_complex_measure),
			nonius::benchmark(lualite_name + " - " + userdata_variable_access_last_measure_name, lb::lualite_userdata_variable_access_last_measure),
			nonius::benchmark(lualite_name + " - " + userdata_variable_access_simple_measure_name, lb::lualite_userdata_variable_access_measure),
			nonius::benchmark(lualite_name + " - " + userdata_variable_access_large_simple_measure_name, lb::lualite_userdata_variable_access_complex_measure),
			nonius::benchmark(lualite_name + " - " + userdata_variable_access_last_simple_measure_name, lb::lualite_userdata_variable_access_last_measure),
			nonius::benchmark(lualite_name + " - " + multi_return_measure_name, lb::lualite_multi_return_measure),
			nonius::benchmark(lualite_name + " - " + stateful_function_object_measure_name, lb::lualite_stateful_function_object_measure),
			//nonius::benchmark(lualite_name + " - " + base_derived_measure_name, lb::lualite_base_derived_measure),
			nonius::benchmark(lualite_name + " - " + return_userdata_measure_name, lb::lualite_return_userdata_measure),
			nonius::benchmark(lualite_name + " - " + optional_measure_name, lb::lualite_optional_measure),
			//nonius::benchmark(lualite_name + " - " + implicit_inheritance_call_measure_name, lb::lualite_implicit_inheritance_call_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " lualite";
		cfg.output_file += " lualite.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	*/

	return 0;
}