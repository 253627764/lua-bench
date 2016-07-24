#include "lua bench.hpp"
#include <nonius.h++>

int main(int argc, char* argv[]) {

	nonius::configuration rootcfg;
	rootcfg.output_file = "lua bench tests";
	rootcfg.title = "lua bench tests";
#ifdef _DEBUG
	rootcfg.samples = 1;
	rootcfg.resamples = 1;
#else
	rootcfg.samples = 250;
	rootcfg.resamples = 250;
#endif
#if 0
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("global get", lb::plain_global_string_get_measure),
			nonius::benchmark("global set", lb::plain_global_string_set_measure),
			nonius::benchmark("table get", lb::plain_table_get_measure),
			nonius::benchmark("table set", lb::plain_table_set_measure),
			nonius::benchmark("table chained get", lb::plain_chained_get_measure),
			nonius::benchmark("table chained set", lb::plain_chained_set_measure),
			nonius::benchmark("c function", lb::plain_c_function_measure),
			nonius::benchmark("c function through lua", lb::plain_c_through_lua_function_measure),
			nonius::benchmark("lua function", lb::plain_lua_function_measure),
			nonius::benchmark("member function calls", lb::plain_member_function_call),
			nonius::benchmark("member variable", lb::plain_member_variable),
		};
		auto cfg = rootcfg;
		cfg.title += " plain C";
		cfg.output_file += " plain C.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}

	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("global get", lb::sol_global_string_get_measure),
			nonius::benchmark("global set", lb::sol_global_string_set_measure),
			nonius::benchmark("table get", lb::sol_table_get_measure),
			nonius::benchmark("table set", lb::sol_table_set_measure),
			nonius::benchmark("table chained get", lb::sol_chained_get_measure),
			nonius::benchmark("table chained set", lb::sol_chained_set_measure),
			nonius::benchmark("c function", lb::sol_c_function_measure),
			nonius::benchmark("c function through lua", lb::sol_c_through_lua_function_measure),
			nonius::benchmark("lua function", lb::sol_lua_function_measure),
			nonius::benchmark("member function calls", lb::sol_member_function_call),
			nonius::benchmark("member variable", lb::sol_member_variable),
			nonius::benchmark("multi return", lb::sol_multi_return_measure),
			nonius::benchmark("stateful c function", lb::sol_stateful_function_object_measure),
			nonius::benchmark("base from derived", lb::sol_base_derived_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " sol";
		cfg.output_file += " sol.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("global get", lb::selene_global_string_get_measure),
			nonius::benchmark("global set", lb::selene_global_string_set_measure),
			nonius::benchmark("table get", lb::selene_table_get_measure),
			nonius::benchmark("table set", lb::selene_table_set_measure),
			nonius::benchmark("table chained get", lb::selene_chained_get_measure),
			nonius::benchmark("table chained set", lb::selene_chained_set_measure),
			nonius::benchmark("c function", lb::selene_c_function_measure),
			nonius::benchmark("c function through lua", lb::selene_c_through_lua_function_measure),
			nonius::benchmark("lua function", lb::selene_lua_function_measure),
			nonius::benchmark("member function calls", lb::selene_member_function_call),
			//nonius::benchmark("member variable", lb::selene_member_variable),
			nonius::benchmark("multi return", lb::selene_multi_return_measure),
			nonius::benchmark("stateful c function", lb::selene_stateful_function_object_measure),
			//nonius::benchmark("base from derived", lb::selene_base_derived_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " selene";
		cfg.output_file += " selene.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("global get", lb::kaguya_global_string_get_measure),
			nonius::benchmark("global set", lb::kaguya_global_string_set_measure),
			nonius::benchmark("table get", lb::kaguya_table_get_measure),
			nonius::benchmark("table set", lb::kaguya_table_set_measure),
			nonius::benchmark("table chained get", lb::kaguya_chained_get_measure),
			nonius::benchmark("table chained set", lb::kaguya_chained_set_measure),
			nonius::benchmark("c function", lb::kaguya_c_function_measure),
			nonius::benchmark("c function through lua", lb::kaguya_c_through_lua_function_measure),
			nonius::benchmark("lua function", lb::kaguya_lua_function_measure),
			nonius::benchmark("member function calls", lb::kaguya_member_function_call),
			//nonius::benchmark("member variable", lb::kaguya_member_variable),
			nonius::benchmark("multi return", lb::kaguya_multi_return_measure),
			nonius::benchmark("stateful c function", lb::kaguya_stateful_function_object_measure),
			nonius::benchmark("base from derived", lb::kaguya_base_derived_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " kaguya";
		cfg.output_file += " kaguya.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("global get", lb::slb3_global_string_get_measure),
			nonius::benchmark("global set", lb::slb3_global_string_set_measure),
			//nonius::benchmark("table get", lb::slb3_table_get_measure),
			//nonius::benchmark("table set", lb::slb3_table_set_measure),
			//nonius::benchmark("table chained get", lb::slb3_chained_get_measure),
			//nonius::benchmark("table chained set", lb::slb3_chained_set_measure),
			nonius::benchmark("c function", lb::slb3_c_function_measure),
			//nonius::benchmark("c function through lua", lb::slb3_c_through_lua_function_measure),
			//nonius::benchmark("lua function", lb::slb3_lua_function_measure),
			nonius::benchmark("member function calls", lb::slb3_member_function_call),
			//nonius::benchmark("member variable", lb::slb3_member_variable),
			//nonius::benchmark("multi return", lb::slb3_multi_return_measure),
			//nonius::benchmark("stateful c function", lb::slb3_stateful_function_object_measure),
			//nonius::benchmark("base from derived", lb::slb3_base_derived_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " slb3";
		cfg.output_file += " slb3.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("global get", lb::luawrapper_global_string_get_measure),
			nonius::benchmark("global set", lb::luawrapper_global_string_set_measure),
			nonius::benchmark("table get", lb::luawrapper_table_get_measure),
			nonius::benchmark("table set", lb::luawrapper_table_set_measure),
			nonius::benchmark("table chained get", lb::luawrapper_chained_get_measure),
			nonius::benchmark("table chained set", lb::luawrapper_chained_set_measure),
			nonius::benchmark("c function", lb::luawrapper_c_function_measure),
			nonius::benchmark("c function through lua", lb::luawrapper_c_through_lua_function_measure),
			nonius::benchmark("lua function", lb::luawrapper_lua_function_measure),
			nonius::benchmark("member function calls", lb::luawrapper_member_function_call),
			nonius::benchmark("member variable", lb::luawrapper_member_variable),

		};
		auto cfg = rootcfg;
		cfg.title += " luawrapper";
		cfg.output_file += " luawrapper.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	{
		nonius::benchmark benchmarks[] = {
			//nonius::benchmark("global get", lb::swig_global_string_get_measure),
			//nonius::benchmark("global set", lb::swig_global_string_set_measure),
			//nonius::benchmark("table get", lb::swig_table_get_measure),
			//nonius::benchmark("table set", lb::swig_table_set_measure),
			//nonius::benchmark("table chained get", lb::swig_chained_get_measure),
			//nonius::benchmark("table chained set", lb::swig_chained_set_measure),
			nonius::benchmark("c function", lb::swig_c_function_measure),
			nonius::benchmark("c function through lua", lb::swig_c_through_lua_function_measure),
			nonius::benchmark("lua function", lb::swig_lua_function_measure),
			nonius::benchmark("member function calls", lb::swig_member_function_call),
			nonius::benchmark("member variable", lb::swig_member_variable),

		};
		auto cfg = rootcfg;
		cfg.title += " swig";
		cfg.output_file += " swig.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("global get", lb::oolua_global_string_get_measure),
			nonius::benchmark("global set", lb::oolua_global_string_set_measure),
			nonius::benchmark("table get", lb::oolua_table_get_measure),
			nonius::benchmark("table set", lb::oolua_table_set_measure),
			nonius::benchmark("table chained get", lb::oolua_chained_get_measure),
			nonius::benchmark("table chained set", lb::oolua_chained_set_measure),
			nonius::benchmark("c function", lb::oolua_c_function_measure),
			nonius::benchmark("c function through lua", lb::oolua_c_through_lua_function_measure),
			nonius::benchmark("lua function", lb::oolua_lua_function_measure),
			nonius::benchmark("member function calls", lb::oolua_member_function_call),
			nonius::benchmark("member variable", lb::oolua_member_variable),
		};
		auto cfg = rootcfg;
		cfg.title += " oolua";
		cfg.output_file += " oolua.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("global get", lb::luacppinterface_global_string_get_measure),
			nonius::benchmark("global set", lb::luacppinterface_global_string_set_measure),
			nonius::benchmark("table get", lb::luacppinterface_table_get_measure),
			nonius::benchmark("table set", lb::luacppinterface_table_set_measure),
			nonius::benchmark("table chained get", lb::luacppinterface_chained_get_measure),
			nonius::benchmark("table chained set", lb::luacppinterface_chained_set_measure),
			nonius::benchmark("c function", lb::luacppinterface_c_function_measure),
			nonius::benchmark("c function through lua", lb::luacppinterface_c_through_lua_function_measure),
			nonius::benchmark("lua function", lb::luacppinterface_lua_function_measure),
			nonius::benchmark("member function calls", lb::luacppinterface_member_function_call),
			//nonius::benchmark("member variable", lb::luacppinterface_member_variable),
		};
		auto cfg = rootcfg;
		cfg.title += " luacppinterface";
		cfg.output_file += " luacppinterface.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
#endif
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("global get", lb::luwra_global_string_get_measure),
			nonius::benchmark("global set", lb::luwra_global_string_set_measure),
			nonius::benchmark("table get", lb::luwra_table_get_measure),
			nonius::benchmark("table set", lb::luwra_table_set_measure),
			nonius::benchmark("table chained get", lb::luwra_chained_get_measure),
			nonius::benchmark("table chained set", lb::luwra_chained_set_measure),
			nonius::benchmark("c function", lb::luwra_c_function_measure),
			nonius::benchmark("c function through lua", lb::luwra_c_through_lua_function_measure),
			nonius::benchmark("lua function", lb::luwra_lua_function_measure),
			nonius::benchmark("member function calls", lb::luwra_member_function_call),
			//nonius::benchmark("member variable", lb::lua_api_pp_member_variable),
			//nonius::benchmark("multi return", lb::luwra_multi_return_measure),
			//nonius::benchmark("stateful c function", lb::luwra_stateful_function_object_measure),
			nonius::benchmark("base from derived", lb::luwra_base_derived_measure),
		};
		auto cfg = rootcfg;
		cfg.title += " luwra";
		cfg.output_file += " luwra.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("global get", lb::lua_api_pp_global_string_get_measure),
			nonius::benchmark("global set", lb::lua_api_pp_global_string_set_measure),
			nonius::benchmark("table get", lb::lua_api_pp_table_get_measure),
			nonius::benchmark("table set", lb::lua_api_pp_table_set_measure),
			nonius::benchmark("table chained get", lb::lua_api_pp_chained_get_measure),
			nonius::benchmark("table chained set", lb::lua_api_pp_chained_set_measure),
			nonius::benchmark("c function", lb::lua_api_pp_c_function_measure),
			nonius::benchmark("c function through lua", lb::lua_api_pp_c_through_lua_function_measure),
			nonius::benchmark("lua function", lb::lua_api_pp_lua_function_measure),
			nonius::benchmark("member function calls", lb::lua_api_pp_member_function_call),
			//nonius::benchmark("member variable", lb::lua_api_pp_member_variable),
		};
		auto cfg = rootcfg;
		cfg.title += " lua-api-pp";
		cfg.output_file += " lua-api-pp.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}

	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("global get", lb::luabind_global_string_get_measure),
			nonius::benchmark("global set", lb::luabind_global_string_set_measure),
			nonius::benchmark("table get", lb::luabind_table_get_measure),
			nonius::benchmark("table set", lb::luabind_table_set_measure),
			nonius::benchmark("table chained get", lb::luabind_chained_get_measure),
			nonius::benchmark("table chained set", lb::luabind_chained_set_measure),
			nonius::benchmark("c function", lb::luabind_c_function_measure),
			nonius::benchmark("c function through lua", lb::luabind_c_through_lua_function_measure),
			nonius::benchmark("lua function", lb::luabind_lua_function_measure),
			nonius::benchmark("member function calls", lb::luabind_member_function_call),
			nonius::benchmark("member variable", lb::luabind_member_variable),
		};
		auto cfg = rootcfg;
		cfg.title += " luabind";
		cfg.output_file += " luabind.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}

	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("global get", lb::lua_intf_global_string_get_measure),
			nonius::benchmark("global set", lb::lua_intf_global_string_set_measure),
			nonius::benchmark("table get", lb::lua_intf_table_get_measure),
			nonius::benchmark("table set", lb::lua_intf_table_set_measure),
			nonius::benchmark("table chained get", lb::lua_intf_chained_get_measure),
			nonius::benchmark("table chained set", lb::lua_intf_chained_set_measure),
			nonius::benchmark("c function", lb::lua_intf_c_function_measure),
			nonius::benchmark("c function through lua", lb::lua_intf_c_through_lua_function_measure),
			nonius::benchmark("lua function", lb::lua_intf_lua_function_measure),
			nonius::benchmark("member function calls", lb::lua_intf_member_function_call),
			nonius::benchmark("member variable", lb::lua_intf_member_variable),
		};
		auto cfg = rootcfg;
		cfg.title += " lua-intf";
		cfg.output_file += " lua-intf.csv";
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::csv_reporter());
	}
}