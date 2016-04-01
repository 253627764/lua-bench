#include "lua_bench.hpp"
#include <nonius.h++>
#include <kaguya/kaguya.hpp>

int main(int argc, char* argv[]) {
	kaguya::State state;
	state("multresfun =function() return 1,2,4 end");//registering multiple results function
	int a, b, c;
	kaguya::tie(a, b, c) = state["multresfun"]();
#if 0
	nonius::configuration cfg;
	cfg.output_file = "lua_bench tests";
	cfg.title = "lua_bench tests";
	cfg.samples = 100;
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
			nonius::benchmark("plain C - member variable get", lb::plain_member_variable_get),
			nonius::benchmark("plain C - member variable set", lb::plain_member_variable_set),
		};
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}

	{
		nonius::benchmark benchmarks[] = {
			nonius::benchmark("sol C - global get", lb::sol_global_string_get_measure),
			nonius::benchmark("sol C - global set", lb::sol_global_string_set_measure),
			nonius::benchmark("sol C - table get", lb::sol_table_get_measure),
			nonius::benchmark("sol C - table set", lb::sol_table_set_measure),
			nonius::benchmark("sol C - table chained get", lb::sol_chained_get_measure),
			nonius::benchmark("sol C - table chained set", lb::sol_chained_set_measure),
			nonius::benchmark("sol C - c function", lb::sol_c_function_measure),
			nonius::benchmark("sol C - c function through lua", lb::sol_c_through_lua_function_measure),
			nonius::benchmark("sol C - lua function", lb::sol_lua_function_measure),
			nonius::benchmark("sol C - member function calls", lb::sol_member_function_call),
			nonius::benchmark("sol C - member variable get", lb::sol_member_variable_get),
			nonius::benchmark("sol C - member variable set", lb::sol_member_variable_set),
		};
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
			nonius::benchmark("selene - member variable get", lb::selene_member_variable_get),
			nonius::benchmark("selene - member variable set", lb::selene_member_variable_set),
		};
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
			nonius::benchmark("kaguya - member variable get", lb::kaguya_member_variable_get),
			nonius::benchmark("kaguya - member variable set", lb::kaguya_member_variable_set),
		};
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}

#if 0
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
			nonius::benchmark("selene - member variable get", lb::selene_member_variable_get),
			nonius::benchmark("selene - member variable set", lb::selene_member_variable_set),
		};
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
			nonius::benchmark("selene - member variable get", lb::selene_member_variable_get),
			nonius::benchmark("selene - member variable set", lb::selene_member_variable_set),
		};
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
			nonius::benchmark("selene - member variable get", lb::selene_member_variable_get),
			nonius::benchmark("selene - member variable set", lb::selene_member_variable_set),
		};
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
			nonius::benchmark("selene - member variable get", lb::selene_member_variable_get),
			nonius::benchmark("selene - member variable set", lb::selene_member_variable_set),
		};
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
			nonius::benchmark("selene - member variable get", lb::selene_member_variable_get),
			nonius::benchmark("selene - member variable set", lb::selene_member_variable_set),
		};
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
			nonius::benchmark("selene - member variable get", lb::selene_member_variable_get),
			nonius::benchmark("selene - member variable set", lb::selene_member_variable_set),
		};
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
			nonius::benchmark("selene - member variable get", lb::selene_member_variable_get),
			nonius::benchmark("selene - member variable set", lb::selene_member_variable_set),
		};
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
			nonius::benchmark("selene - member variable get", lb::selene_member_variable_get),
			nonius::benchmark("selene - member variable set", lb::selene_member_variable_set),
		};
		nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks), nonius::multi_report(nonius::csv_reporter(), nonius::html_reporter()));
	}
#endif
#endif
}