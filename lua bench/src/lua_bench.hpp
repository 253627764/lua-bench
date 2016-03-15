#pragma once

#include <nonius.h++>

namespace lb {

	void plain_global_string_get_measure(nonius::chronometer& meter);
	void sol_global_string_get_measure(nonius::chronometer& meter);
	void kaguya_global_string_get_measure(nonius::chronometer& meter);
	void lua_api_pp_global_string_get_measure(nonius::chronometer& meter);
	void luabind_global_string_get_measure(nonius::chronometer& meter);
	void lua_intf_global_string_get_measure(nonius::chronometer& meter);
	void luawrapper_global_string_get_measure(nonius::chronometer& meter);
	void oolua_global_string_get_measure(nonius::chronometer& meter);
	void selene_global_string_get_measure(nonius::chronometer& meter);
	void luwra_global_string_get_measure(nonius::chronometer& meter);

	void plain_global_string_set_measure(nonius::chronometer& meter);
	void sol_global_string_set_measure(nonius::chronometer& meter);
	void kaguya_global_string_set_measure(nonius::chronometer& meter);
	void lua_api_pp_global_string_set_measure(nonius::chronometer& meter);
	void luabind_global_string_set_measure(nonius::chronometer& meter);
	void lua_intf_global_string_set_measure(nonius::chronometer& meter);
	void luawrapper_global_string_set_measure(nonius::chronometer& meter);
	void oolua_global_string_set_measure(nonius::chronometer& meter);
	void selene_global_string_set_measure(nonius::chronometer& meter);
	void luwra_global_string_set_measure(nonius::chronometer& meter);

	void plain_chained_get_measure(nonius::chronometer& meter);
	void sol_chained_get_measure(nonius::chronometer& meter);
	void kaguya_chained_get_measure(nonius::chronometer& meter);
	void lua_api_pp_chained_get_measure(nonius::chronometer& meter);
	void luabind_chained_get_measure(nonius::chronometer& meter);
	void lua_intf_chained_get_measure(nonius::chronometer& meter);
	void luawrapper_chained_get_measure(nonius::chronometer& meter);
	void oolua_chained_get_measure(nonius::chronometer& meter);
	void selene_chained_get_measure(nonius::chronometer& meter);
	void luwra_chained_get_measure(nonius::chronometer& meter);

	void plain_chained_set_measure(nonius::chronometer& meter);
	void sol_chained_set_measure(nonius::chronometer& meter);
	void kaguya_chained_set_measure(nonius::chronometer& meter);
	void lua_api_pp_chained_set_measure(nonius::chronometer& meter);
	void luabind_chained_set_measure(nonius::chronometer& meter);
	void lua_intf_chained_set_measure(nonius::chronometer& meter);
	void luawrapper_chained_set_measure(nonius::chronometer& meter);
	void oolua_chained_set_measure(nonius::chronometer& meter);
	void selene_chained_set_measure(nonius::chronometer& meter);
	void luwra_chained_set_measure(nonius::chronometer& meter);

	void plain_table_get_measure(nonius::chronometer& meter);
	void sol_table_get_measure(nonius::chronometer& meter);
	void kaguya_table_get_measure(nonius::chronometer& meter);
	void lua_api_pp_table_get_measure(nonius::chronometer& meter);
	void luabind_table_get_measure(nonius::chronometer& meter);
	void lua_intf_table_get_measure(nonius::chronometer& meter);
	void luawrapper_table_get_measure(nonius::chronometer& meter);
	void oolua_table_get_measure(nonius::chronometer& meter);
	void selene_table_get_measure(nonius::chronometer& meter);
	void luwra_table_get_measure(nonius::chronometer& meter);

	void plain_table_set_measure(nonius::chronometer& meter);
	void sol_table_set_measure(nonius::chronometer& meter);
	void kaguya_table_set_measure(nonius::chronometer& meter);
	void lua_api_pp_table_set_measure(nonius::chronometer& meter);
	void luabind_table_set_measure(nonius::chronometer& meter);
	void lua_intf_table_set_measure(nonius::chronometer& meter);
	void luawrapper_table_set_measure(nonius::chronometer& meter);
	void oolua_table_set_measure(nonius::chronometer& meter);
	void selene_table_set_measure(nonius::chronometer& meter);
	void luwra_table_set_measure(nonius::chronometer& meter);

	void plain_c_function_measure(nonius::chronometer& meter);
	void sol_c_function_measure(nonius::chronometer& meter);
	void kaguya_c_function_measure(nonius::chronometer& meter);
	void lua_api_pp_c_function_measure(nonius::chronometer& meter);
	void luabind_c_function_measure(nonius::chronometer& meter);
	void lua_intf_c_function_measure(nonius::chronometer& meter);
	void luawrapper_c_function_measure(nonius::chronometer& meter);
	void oolua_c_function_measure(nonius::chronometer& meter);
	void selene_c_function_measure(nonius::chronometer& meter);
	void luwra_c_function_measure(nonius::chronometer& meter);

	void plain_lua_function_measure(nonius::chronometer& meter);
	void sol_lua_function_measure(nonius::chronometer& meter);
	void kaguya_lua_function_measure(nonius::chronometer& meter);
	void lua_api_pp_lua_function_measure(nonius::chronometer& meter);
	void luabind_lua_function_measure(nonius::chronometer& meter);
	void lua_intf_lua_function_measure(nonius::chronometer& meter);
	void luawrapper_lua_function_measure(nonius::chronometer& meter);
	void oolua_lua_function_measure(nonius::chronometer& meter);
	void selene_lua_function_measure(nonius::chronometer& meter);
	void luwra_lua_function_measure(nonius::chronometer& meter);

	void plain_c_through_lua_function_measure(nonius::chronometer& meter);
	void sol_c_through_lua_function_measure(nonius::chronometer& meter);
	void kaguya_c_through_lua_function_measure(nonius::chronometer& meter);
	void lua_api_pp_c_through_lua_function_measure(nonius::chronometer& meter);
	void luabind_c_through_lua_function_measure(nonius::chronometer& meter);
	void lua_intf_c_through_lua_function_measure(nonius::chronometer& meter);
	void luawrapper_c_through_lua_function_measure(nonius::chronometer& meter);
	void oolua_c_through_lua_function_measure(nonius::chronometer& meter);
	void selene_c_through_lua_function_measure(nonius::chronometer& meter);
	void luwra_c_through_lua_function_measure(nonius::chronometer& meter);

	void plain_member_function_call(nonius::chronometer& meter);
	void sol_member_function_call(nonius::chronometer& meter);
	void kaguya_member_function_call(nonius::chronometer& meter);
	void lua_api_pp_member_function_call(nonius::chronometer& meter);
	void luabind_member_function_call(nonius::chronometer& meter);
	void lua_intf_member_function_call(nonius::chronometer& meter);
	void luawrapper_member_function_call(nonius::chronometer& meter);
	void oolua_member_function_call(nonius::chronometer& meter);
	void selene_member_function_call(nonius::chronometer& meter);
	void luwra_member_function_call(nonius::chronometer& meter);

	void plain_member_variable_set(nonius::chronometer& meter);
	void sol_member_variable_set(nonius::chronometer& meter);
	void kaguya_member_variable_set(nonius::chronometer& meter);
	void lua_api_pp_member_variable_set(nonius::chronometer& meter);
	void luabind_member_variable_set(nonius::chronometer& meter);
	void lua_intf_member_variable_set(nonius::chronometer& meter);
	void luawrapper_member_variable_set(nonius::chronometer& meter);
	void oolua_member_variable_set(nonius::chronometer& meter);
	void selene_member_variable_set(nonius::chronometer& meter);
	void luwra_member_variable_set(nonius::chronometer& meter);

	void plain_member_variable_get(nonius::chronometer& meter);
	void sol_member_variable_get(nonius::chronometer& meter);
	void kaguya_member_variable_get(nonius::chronometer& meter);
	void lua_api_pp_member_variable_get(nonius::chronometer& meter);
	void lua_intf_member_variable_get(nonius::chronometer& meter);
	void luabind_member_variable_get(nonius::chronometer& meter);
	void luawrapper_member_variable_get(nonius::chronometer& meter);
	void oolua_member_variable_get(nonius::chronometer& meter);
	void selene_member_variable_get(nonius::chronometer& meter);
	void luwra_member_variable_get(nonius::chronometer& meter);

}
