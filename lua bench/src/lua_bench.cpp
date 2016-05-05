#include "lua_bench.hpp"
#include <nonius.h++>

int main(int argc, char* argv[]) {

	nonius::configuration rootcfg;
	rootcfg.output_file = "lua bench tests";
	rootcfg.title = "lua bench tests";
	rootcfg.samples = 100;
	rootcfg.list_benchmarks = true;
	rootcfg.list_reporters = true;
	rootcfg.verbose = true;

	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("plain C - global get", lb::plain_global_string_get_measure),
			nonius::benchmark("plain C - global set", lb::plain_global_string_set_measure),
			nonius::benchmark("plain C - table get", lb::plain_table_get_measure),
			nonius::benchmark("plain C - table set", lb::plain_table_set_measure),
			nonius::benchmark("plain C - table chained get", lb::plain_chained_get_measure),
			nonius::benchmark("plain C - table chained set", lb::plain_chained_set_measure),
			nonius::benchmark("plain C - c function", lb::plain_c_function_measure),
			nonius::benchmark("plain C - c function through lua", lb::plain_c_through_lua_function_measure),
			nonius::benchmark("plain C - lua function", lb::plain_lua_function_measure),
			nonius::benchmark("plain C - member function calls", lb::plain_member_function_call),
			nonius::benchmark("plain C - member variable", lb::plain_member_variable),
		};
		auto cfg = rootcfg;
		cfg.output_file += " plain C";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}

	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("sol - global get", lb::sol_global_string_get_measure),
			nonius::benchmark("sol - global set", lb::sol_global_string_set_measure),
			nonius::benchmark("sol - table get", lb::sol_table_get_measure),
			nonius::benchmark("sol - table set", lb::sol_table_set_measure),
			nonius::benchmark("sol - table chained get", lb::sol_chained_get_measure),
			nonius::benchmark("sol - table chained set", lb::sol_chained_set_measure),
			nonius::benchmark("sol - c function", lb::sol_c_function_measure),
			nonius::benchmark("sol - c function through lua", lb::sol_c_through_lua_function_measure),
			nonius::benchmark("sol - lua function", lb::sol_lua_function_measure),
			nonius::benchmark("sol - member function calls", lb::sol_member_function_call),
			nonius::benchmark("sol - member variable", lb::sol_member_variable),
		};
		auto cfg = rootcfg;
		cfg.output_file += " sol";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("selene - global get", lb::selene_global_string_get_measure),
			nonius::benchmark("selene - global set", lb::selene_global_string_set_measure),
			nonius::benchmark("selene - table get", lb::selene_table_get_measure),
			nonius::benchmark("selene - table set", lb::selene_table_set_measure),
			nonius::benchmark("selene - table chained get", lb::selene_chained_get_measure),
			nonius::benchmark("selene - table chained set", lb::selene_chained_set_measure),
			nonius::benchmark("selene - c function", lb::selene_c_function_measure),
			nonius::benchmark("selene - c function through lua", lb::selene_c_through_lua_function_measure),
			nonius::benchmark("selene - lua function", lb::selene_lua_function_measure),
			nonius::benchmark("selene - member function calls", lb::selene_member_function_call),
//			nonius::benchmark("selene - member variable", lb::selene_member_variable),
		};
		auto cfg = rootcfg;
		cfg.output_file += " selene";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("kaguya - global get", lb::kaguya_global_string_get_measure),
			nonius::benchmark("kaguya - global set", lb::kaguya_global_string_set_measure),
			nonius::benchmark("kaguya - table get", lb::kaguya_table_get_measure),
			nonius::benchmark("kaguya - table set", lb::kaguya_table_set_measure),
			nonius::benchmark("kaguya - table chained get", lb::kaguya_chained_get_measure),
			nonius::benchmark("kaguya - table chained set", lb::kaguya_chained_set_measure),
			nonius::benchmark("kaguya - c function", lb::kaguya_c_function_measure),
			nonius::benchmark("kaguya - c function through lua", lb::kaguya_c_through_lua_function_measure),
			nonius::benchmark("kaguya - lua function", lb::kaguya_lua_function_measure),
			nonius::benchmark("kaguya - member function calls", lb::kaguya_member_function_call),
//			nonius::benchmark("kaguya - member variable", lb::kaguya_member_variable),
		};
		auto cfg = rootcfg;
		cfg.output_file += " kaguya";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("slb3 - global get", lb::slb3_global_string_get_measure),
			nonius::benchmark("slb3 - global set", lb::slb3_global_string_set_measure),
//			nonius::benchmark("slb3 - table get", lb::slb3_table_get_measure),
//			nonius::benchmark("slb3 - table set", lb::slb3_table_set_measure),
//			nonius::benchmark("slb3 - table chained get", lb::slb3_chained_get_measure),
//			nonius::benchmark("slb3 - table chained set", lb::slb3_chained_set_measure),
			nonius::benchmark("slb3 - c function", lb::slb3_c_function_measure),
//			nonius::benchmark("slb3 - c function through lua", lb::slb3_c_through_lua_function_measure),
//			nonius::benchmark("slb3 - lua function", lb::slb3_lua_function_measure),
			nonius::benchmark("slb3 - member function calls", lb::slb3_member_function_call),
//			nonius::benchmark("slb3 - member variable", lb::slb3_member_variable),
		};
		auto cfg = rootcfg;
		cfg.output_file += " slb3";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("luawrapper - global get", lb::luawrapper_global_string_get_measure),
			nonius::benchmark("luawrapper - global set", lb::luawrapper_global_string_set_measure),
			nonius::benchmark("luawrapper - table get", lb::luawrapper_table_get_measure),
			nonius::benchmark("luawrapper - table set", lb::luawrapper_table_set_measure),
			nonius::benchmark("luawrapper - table chained get", lb::luawrapper_chained_get_measure),
			nonius::benchmark("luawrapper - table chained set", lb::luawrapper_chained_set_measure),
			nonius::benchmark("luawrapper - c function", lb::luawrapper_c_function_measure),
			nonius::benchmark("luawrapper - c function through lua", lb::luawrapper_c_through_lua_function_measure),
			nonius::benchmark("luawrapper - lua function", lb::luawrapper_lua_function_measure),
			nonius::benchmark("luawrapper - member function calls", lb::luawrapper_member_function_call),
			nonius::benchmark("luawrapper - member variable", lb::luawrapper_member_variable),

		};
		auto cfg = rootcfg;
		cfg.output_file += " luawrapper";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}
	{
		nonius::benchmark benchmarks[] = {
//			nonius::benchmark("swig - global get", lb::swig_global_string_get_measure),
//			nonius::benchmark("swig - global set", lb::swig_global_string_set_measure),
//			nonius::benchmark("swig - table get", lb::swig_table_get_measure),
//			nonius::benchmark("swig - table set", lb::swig_table_set_measure),
//			nonius::benchmark("swig - table chained get", lb::swig_chained_get_measure),
//			nonius::benchmark("swig - table chained set", lb::swig_chained_set_measure),
			nonius::benchmark("swig - c function", lb::swig_c_function_measure),
			nonius::benchmark("swig - c function through lua", lb::swig_c_through_lua_function_measure),
			nonius::benchmark("swig - lua function", lb::swig_lua_function_measure),
			nonius::benchmark("swig - member function calls", lb::swig_member_function_call),
			nonius::benchmark("swig - member variable", lb::swig_member_variable),

		};
		auto cfg = rootcfg;
		cfg.output_file += " swig";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("oolua - global get", lb::oolua_global_string_get_measure),
			nonius::benchmark("oolua - global set", lb::oolua_global_string_set_measure),
			nonius::benchmark("oolua - table get", lb::oolua_table_get_measure),
			nonius::benchmark("oolua - table set", lb::oolua_table_set_measure),
			nonius::benchmark("oolua - table chained get", lb::oolua_chained_get_measure),
			nonius::benchmark("oolua - table chained set", lb::oolua_chained_set_measure),
			nonius::benchmark("oolua - c function", lb::oolua_c_function_measure),
			nonius::benchmark("oolua - c function through lua", lb::oolua_c_through_lua_function_measure),
			nonius::benchmark("oolua - lua function", lb::oolua_lua_function_measure),
			nonius::benchmark("oolua - member function calls", lb::oolua_member_function_call),
			nonius::benchmark("oolua - member variable", lb::oolua_member_variable),
		};
		auto cfg = rootcfg;
		cfg.output_file += " oolua";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("luacppinterface - global get", lb::luacppinterface_global_string_get_measure),
			nonius::benchmark("luacppinterface - global set", lb::luacppinterface_global_string_set_measure),
			nonius::benchmark("luacppinterface - table get", lb::luacppinterface_table_get_measure),
			nonius::benchmark("luacppinterface - table set", lb::luacppinterface_table_set_measure),
			nonius::benchmark("luacppinterface - table chained get", lb::luacppinterface_chained_get_measure),
			nonius::benchmark("luacppinterface - table chained set", lb::luacppinterface_chained_set_measure),
			nonius::benchmark("luacppinterface - c function", lb::luacppinterface_c_function_measure),
//			nonius::benchmark("luacppinterface - c function through lua", lb::luacppinterface_c_through_lua_function_measure),
//			nonius::benchmark("luacppinterface - lua function", lb::luacppinterface_lua_function_measure),
			nonius::benchmark("luacppinterface - member function calls", lb::luacppinterface_member_function_call),
//			nonius::benchmark("luacppinterface - member variable", lb::luacppinterface_member_variable),
		};
		auto cfg = rootcfg;
		cfg.output_file += " luacppinterface";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("lua_api_pp - global get", lb::lua_api_pp_global_string_get_measure),
			nonius::benchmark("lua_api_pp - global set", lb::lua_api_pp_global_string_set_measure),
			nonius::benchmark("lua_api_pp - table get", lb::lua_api_pp_table_get_measure),
			nonius::benchmark("lua_api_pp - table set", lb::lua_api_pp_table_set_measure),
			nonius::benchmark("lua_api_pp - table chained get", lb::lua_api_pp_chained_get_measure),
			nonius::benchmark("lua_api_pp - table chained set", lb::lua_api_pp_chained_set_measure),
			nonius::benchmark("lua_api_pp - c function", lb::lua_api_pp_c_function_measure),
			nonius::benchmark("lua_api_pp - c function through lua", lb::lua_api_pp_c_through_lua_function_measure),
			nonius::benchmark("lua_api_pp - lua function", lb::lua_api_pp_lua_function_measure),
//			nonius::benchmark("lua_api_pp - member function calls", lb::lua_api_pp_member_function_call),
//			nonius::benchmark("lua_api_pp - member variable", lb::lua_api_pp_member_variable),
		};
		auto cfg = rootcfg;
		cfg.output_file += " lua-api-pp";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}

	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("luabind - global get", lb::luabind_global_string_get_measure),
			nonius::benchmark("luabind - global set", lb::luabind_global_string_set_measure),
			nonius::benchmark("luabind - table get", lb::luabind_table_get_measure),
			nonius::benchmark("luabind - table set", lb::luabind_table_set_measure),
			nonius::benchmark("luabind - table chained get", lb::luabind_chained_get_measure),
			nonius::benchmark("luabind - table chained set", lb::luabind_chained_set_measure),
			nonius::benchmark("luabind - c function", lb::luabind_c_function_measure),
			nonius::benchmark("luabind - c function through lua", lb::luabind_c_through_lua_function_measure),
			nonius::benchmark("luabind - lua function", lb::luabind_lua_function_measure),
			nonius::benchmark("luabind - member function calls", lb::luabind_member_function_call),
			nonius::benchmark("luabind - member variable", lb::luabind_member_variable),
		};
		auto cfg = rootcfg;
		cfg.output_file += " luabind";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}

	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("lua_intf - global get", lb::lua_intf_global_string_get_measure),
			nonius::benchmark("lua_intf - global set", lb::lua_intf_global_string_set_measure),
			nonius::benchmark("lua_intf - table get", lb::lua_intf_table_get_measure),
			nonius::benchmark("lua_intf - table set", lb::lua_intf_table_set_measure),
			nonius::benchmark("lua_intf - table chained get", lb::lua_intf_chained_get_measure),
			nonius::benchmark("lua_intf - table chained set", lb::lua_intf_chained_set_measure),
			nonius::benchmark("lua_intf - c function", lb::lua_intf_c_function_measure),
			nonius::benchmark("lua_intf - c function through lua", lb::lua_intf_c_through_lua_function_measure),
			nonius::benchmark("lua_intf - lua function", lb::lua_intf_lua_function_measure),
			nonius::benchmark("lua_intf - member function calls", lb::lua_intf_member_function_call),
			nonius::benchmark("lua_intf - member variable", lb::lua_intf_member_variable),
		};
		auto cfg = rootcfg;
		cfg.output_file += " lua-intf";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}
}