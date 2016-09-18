#pragma once

#include <nonius.h++>

namespace lb {

	void plain_c_global_string_get_measure(nonius::chronometer& meter);
	void sol_global_string_get_measure(nonius::chronometer& meter);
	void old_sol_global_string_get_measure(nonius::chronometer& meter);
	void kaguya_global_string_get_measure(nonius::chronometer& meter);
	void lua_api_pp_global_string_get_measure(nonius::chronometer& meter);
	void luabind_global_string_get_measure(nonius::chronometer& meter);
	void lua_intf_global_string_get_measure(nonius::chronometer& meter);
	void luawrapper_global_string_get_measure(nonius::chronometer& meter);
	void oolua_global_string_get_measure(nonius::chronometer& meter);
	void selene_global_string_get_measure(nonius::chronometer& meter);
	void luacppinterface_global_string_get_measure(nonius::chronometer& meter);
	void slb3_global_string_get_measure(nonius::chronometer& meter);
	void swig_global_string_get_measure(nonius::chronometer& meter);
	void luwra_global_string_get_measure(nonius::chronometer& meter);

	void plain_c_global_string_set_measure(nonius::chronometer& meter);
	void sol_global_string_set_measure(nonius::chronometer& meter);
	void old_sol_global_string_set_measure(nonius::chronometer& meter);
	void kaguya_global_string_set_measure(nonius::chronometer& meter);
	void lua_api_pp_global_string_set_measure(nonius::chronometer& meter);
	void luabind_global_string_set_measure(nonius::chronometer& meter);
	void lua_intf_global_string_set_measure(nonius::chronometer& meter);
	void luawrapper_global_string_set_measure(nonius::chronometer& meter);
	void oolua_global_string_set_measure(nonius::chronometer& meter);
	void selene_global_string_set_measure(nonius::chronometer& meter);
	void luacppinterface_global_string_set_measure(nonius::chronometer& meter);
	void slb3_global_string_set_measure(nonius::chronometer& meter);
	void swig_global_string_set_measure(nonius::chronometer& meter);
	void luwra_global_string_set_measure(nonius::chronometer& meter);

	void plain_c_chained_get_measure(nonius::chronometer& meter);
	void sol_chained_get_measure(nonius::chronometer& meter);
	void old_sol_chained_get_measure(nonius::chronometer& meter);
	void kaguya_chained_get_measure(nonius::chronometer& meter);
	void lua_api_pp_chained_get_measure(nonius::chronometer& meter);
	void luabind_chained_get_measure(nonius::chronometer& meter);
	void lua_intf_chained_get_measure(nonius::chronometer& meter);
	void luawrapper_chained_get_measure(nonius::chronometer& meter);
	void oolua_chained_get_measure(nonius::chronometer& meter);
	void selene_chained_get_measure(nonius::chronometer& meter);
	void luacppinterface_chained_get_measure(nonius::chronometer& meter);
	void slb3_chained_get_measure(nonius::chronometer& meter);
	void swig_chained_get_measure(nonius::chronometer& meter);
	void luwra_chained_get_measure(nonius::chronometer& meter);

	void plain_c_chained_set_measure(nonius::chronometer& meter);
	void sol_chained_set_measure(nonius::chronometer& meter);
	void old_sol_chained_set_measure(nonius::chronometer& meter);
	void kaguya_chained_set_measure(nonius::chronometer& meter);
	void lua_api_pp_chained_set_measure(nonius::chronometer& meter);
	void luabind_chained_set_measure(nonius::chronometer& meter);
	void lua_intf_chained_set_measure(nonius::chronometer& meter);
	void luawrapper_chained_set_measure(nonius::chronometer& meter);
	void oolua_chained_set_measure(nonius::chronometer& meter);
	void selene_chained_set_measure(nonius::chronometer& meter);
	void luacppinterface_chained_set_measure(nonius::chronometer& meter);
	void slb3_chained_set_measure(nonius::chronometer& meter);
	void swig_chained_set_measure(nonius::chronometer& meter);
	void luwra_chained_set_measure(nonius::chronometer& meter);

	void plain_c_table_get_measure(nonius::chronometer& meter);
	void sol_table_get_measure(nonius::chronometer& meter);
	void old_sol_table_get_measure(nonius::chronometer& meter);
	void kaguya_table_get_measure(nonius::chronometer& meter);
	void lua_api_pp_table_get_measure(nonius::chronometer& meter);
	void luabind_table_get_measure(nonius::chronometer& meter);
	void lua_intf_table_get_measure(nonius::chronometer& meter);
	void luawrapper_table_get_measure(nonius::chronometer& meter);
	void oolua_table_get_measure(nonius::chronometer& meter);
	void selene_table_get_measure(nonius::chronometer& meter);
	void luacppinterface_table_get_measure(nonius::chronometer& meter);
	void slb3_table_get_measure(nonius::chronometer& meter);
	void swig_table_get_measure(nonius::chronometer& meter);
	void luwra_table_get_measure(nonius::chronometer& meter);

	void plain_c_table_set_measure(nonius::chronometer& meter);
	void sol_table_set_measure(nonius::chronometer& meter);
	void old_sol_table_set_measure(nonius::chronometer& meter);
	void kaguya_table_set_measure(nonius::chronometer& meter);
	void lua_api_pp_table_set_measure(nonius::chronometer& meter);
	void luabind_table_set_measure(nonius::chronometer& meter);
	void lua_intf_table_set_measure(nonius::chronometer& meter);
	void luawrapper_table_set_measure(nonius::chronometer& meter);
	void oolua_table_set_measure(nonius::chronometer& meter);
	void selene_table_set_measure(nonius::chronometer& meter);
	void luacppinterface_table_set_measure(nonius::chronometer& meter);
	void slb3_table_set_measure(nonius::chronometer& meter);
	void swig_table_set_measure(nonius::chronometer& meter);
	void luwra_table_set_measure(nonius::chronometer& meter);

	void plain_c_c_function_measure(nonius::chronometer& meter);
	void sol_c_function_measure(nonius::chronometer& meter);
	void old_sol_c_function_measure(nonius::chronometer& meter);
	void kaguya_c_function_measure(nonius::chronometer& meter);
	void lua_api_pp_c_function_measure(nonius::chronometer& meter);
	void luabind_c_function_measure(nonius::chronometer& meter);
	void lua_intf_c_function_measure(nonius::chronometer& meter);
	void luawrapper_c_function_measure(nonius::chronometer& meter);
	void oolua_c_function_measure(nonius::chronometer& meter);
	void selene_c_function_measure(nonius::chronometer& meter);
	void luacppinterface_c_function_measure(nonius::chronometer& meter);
	void slb3_c_function_measure(nonius::chronometer& meter);
	void swig_c_function_measure(nonius::chronometer& meter);
	void luwra_c_function_measure(nonius::chronometer& meter);

	void plain_c_lua_function_measure(nonius::chronometer& meter);
	void sol_lua_function_measure(nonius::chronometer& meter);
	void old_sol_lua_function_measure(nonius::chronometer& meter);
	void kaguya_lua_function_measure(nonius::chronometer& meter);
	void lua_api_pp_lua_function_measure(nonius::chronometer& meter);
	void luabind_lua_function_measure(nonius::chronometer& meter);
	void lua_intf_lua_function_measure(nonius::chronometer& meter);
	void luawrapper_lua_function_measure(nonius::chronometer& meter);
	void oolua_lua_function_measure(nonius::chronometer& meter);
	void selene_lua_function_measure(nonius::chronometer& meter);
	void luacppinterface_lua_function_measure(nonius::chronometer& meter);
	void slb3_lua_function_measure(nonius::chronometer& meter);
	void swig_lua_function_measure(nonius::chronometer& meter);
	void luwra_lua_function_measure(nonius::chronometer& meter);

	void plain_c_c_through_lua_function_measure(nonius::chronometer& meter);
	void sol_c_through_lua_function_measure(nonius::chronometer& meter);
	void old_sol_c_through_lua_function_measure(nonius::chronometer& meter);
	void kaguya_c_through_lua_function_measure(nonius::chronometer& meter);
	void lua_api_pp_c_through_lua_function_measure(nonius::chronometer& meter);
	void luabind_c_through_lua_function_measure(nonius::chronometer& meter);
	void lua_intf_c_through_lua_function_measure(nonius::chronometer& meter);
	void luawrapper_c_through_lua_function_measure(nonius::chronometer& meter);
	void oolua_c_through_lua_function_measure(nonius::chronometer& meter);
	void selene_c_through_lua_function_measure(nonius::chronometer& meter);
	void luacppinterface_c_through_lua_function_measure(nonius::chronometer& meter);
	void slb3_c_through_lua_function_measure(nonius::chronometer& meter);
	void swig_c_through_lua_function_measure(nonius::chronometer& meter);
	void luwra_c_through_lua_function_measure(nonius::chronometer& meter);

	void plain_c_stateful_function_object_measure(nonius::chronometer& meter);
	void sol_stateful_function_object_measure(nonius::chronometer& meter);
	void old_sol_stateful_function_object_measure(nonius::chronometer& meter);
	void kaguya_stateful_function_object_measure(nonius::chronometer& meter);
	void lua_api_pp_stateful_function_object_measure(nonius::chronometer& meter);
	void luabind_stateful_function_object_measure(nonius::chronometer& meter);
	void lua_intf_stateful_function_object_measure(nonius::chronometer& meter);
	void luawrapper_stateful_function_object_measure(nonius::chronometer& meter);
	void oolua_stateful_function_object_measure(nonius::chronometer& meter);
	void selene_stateful_function_object_measure(nonius::chronometer& meter);
	void luacppinterface_stateful_function_object_measure(nonius::chronometer& meter);
	void slb3_stateful_function_object_measure(nonius::chronometer& meter);
	void swig_stateful_function_object_measure(nonius::chronometer& meter);
	void luwra_stateful_function_object_measure(nonius::chronometer& meter);

	void plain_c_base_derived_measure(nonius::chronometer& meter);
	void sol_base_derived_measure(nonius::chronometer& meter);
	void old_sol_base_derived_measure(nonius::chronometer& meter);
	void kaguya_base_derived_measure(nonius::chronometer& meter);
	void lua_api_pp_base_derived_measure(nonius::chronometer& meter);
	void luabind_base_derived_measure(nonius::chronometer& meter);
	void lua_intf_base_derived_measure(nonius::chronometer& meter);
	void luawrapper_base_derived_measure(nonius::chronometer& meter);
	void oolua_base_derived_measure(nonius::chronometer& meter);
	void selene_base_derived_measure(nonius::chronometer& meter);
	void luacppinterface_base_derived_measure(nonius::chronometer& meter);
	void slb3_base_derived_measure(nonius::chronometer& meter);
	void swig_base_derived_measure(nonius::chronometer& meter);
	void luwra_base_derived_measure(nonius::chronometer& meter);

	void plain_c_multi_return_measure(nonius::chronometer& meter);
	void sol_multi_return_measure(nonius::chronometer& meter);
	void old_sol_multi_return_measure(nonius::chronometer& meter);
	void kaguya_multi_return_measure(nonius::chronometer& meter);
	void lua_api_pp_multi_return_measure(nonius::chronometer& meter);
	void luabind_multi_return_measure(nonius::chronometer& meter);
	void lua_intf_multi_return_measure(nonius::chronometer& meter);
	void luawrapper_multi_return_measure(nonius::chronometer& meter);
	void oolua_multi_return_measure(nonius::chronometer& meter);
	void selene_multi_return_measure(nonius::chronometer& meter);
	void luacppinterface_multi_return_measure(nonius::chronometer& meter);
	void slb3_multi_return_measure(nonius::chronometer& meter);
	void swig_multi_return_measure(nonius::chronometer& meter);
	void luwra_multi_return_measure(nonius::chronometer& meter);

	void plain_c_member_function_call_measure(nonius::chronometer& meter);
	void sol_member_function_call_measure(nonius::chronometer& meter);
	void old_sol_member_function_call_measure(nonius::chronometer& meter);
	void kaguya_member_function_call_measure(nonius::chronometer& meter);
	void lua_api_pp_member_function_call_measure(nonius::chronometer& meter);
	void luabind_member_function_call_measure(nonius::chronometer& meter);
	void lua_intf_member_function_call_measure(nonius::chronometer& meter);
	void luawrapper_member_function_call_measure(nonius::chronometer& meter);
	void oolua_member_function_call_measure(nonius::chronometer& meter);
	void selene_member_function_call_measure(nonius::chronometer& meter);
	void luacppinterface_member_function_call_measure(nonius::chronometer& meter);
	void slb3_member_function_call_measure(nonius::chronometer& meter);
	void swig_member_function_call_measure(nonius::chronometer& meter);
	void luwra_member_function_call_measure(nonius::chronometer& meter);

	void plain_c_member_variable_measure(nonius::chronometer& meter);
	void sol_member_variable_measure(nonius::chronometer& meter);
	void old_sol_member_variable_measure(nonius::chronometer& meter);
	void kaguya_member_variable_measure(nonius::chronometer& meter);
	void lua_api_pp_member_variable_measure(nonius::chronometer& meter);
	void luabind_member_variable_measure(nonius::chronometer& meter);
	void lua_intf_member_variable_measure(nonius::chronometer& meter);
	void luawrapper_member_variable_measure(nonius::chronometer& meter);
	void oolua_member_variable_measure(nonius::chronometer& meter);
	void selene_member_variable_measure(nonius::chronometer& meter);
	void luacppinterface_member_variable_measure(nonius::chronometer& meter);
	void slb3_member_variable_measure(nonius::chronometer& meter);
	void swig_member_variable_measure(nonius::chronometer& meter);
	void luwra_member_variable_measure(nonius::chronometer& meter);

	void plain_c_member_variable_complex_measure(nonius::chronometer& meter);
	void sol_member_variable_complex_measure(nonius::chronometer& meter);
	void old_sol_member_variable_complex_measure(nonius::chronometer& meter);
	void swig_member_variable_complex_measure(nonius::chronometer& meter);
	void luabind_member_variable_complex_measure(nonius::chronometer& meter);
	void lua_intf_member_variable_complex_measure(nonius::chronometer& meter);
	void luawrapper_member_variable_complex_measure(nonius::chronometer& meter);
	
	void plain_c_member_variable_last_measure(nonius::chronometer& meter);
	void sol_member_variable_last_measure(nonius::chronometer& meter);
	void old_sol_member_variable_last_measure(nonius::chronometer& meter);
	void swig_member_variable_last_measure(nonius::chronometer& meter);
	void luabind_member_variable_last_measure(nonius::chronometer& meter);
	void lua_intf_member_variable_last_measure(nonius::chronometer& meter);
	void luawrapper_member_variable_last_measure(nonius::chronometer& meter);
	
	void sol_member_variable_simple_measure(nonius::chronometer& meter);

	void sol_member_variable_complex_simple_measure(nonius::chronometer& meter);

	void sol_member_variable_last_simple_measure(nonius::chronometer& meter);

	void sol_member_function_call_simple_measure(nonius::chronometer& meter);

	void plain_c_return_userdata_measure(nonius::chronometer& meter);
	void sol_return_userdata_measure(nonius::chronometer& meter);
	void old_sol_return_userdata_measure(nonius::chronometer& meter);
	void kaguya_return_userdata_measure(nonius::chronometer& meter);
	void lua_api_pp_return_userdata_measure(nonius::chronometer& meter);
	void luabind_return_userdata_measure(nonius::chronometer& meter);
	void lua_intf_return_userdata_measure(nonius::chronometer& meter);
	void luawrapper_return_userdata_measure(nonius::chronometer& meter);
	void oolua_return_userdata_measure(nonius::chronometer& meter);
	void selene_return_userdata_measure(nonius::chronometer& meter);
	void luacppinterface_return_userdata_measure(nonius::chronometer& meter);
	void slb3_return_userdata_measure(nonius::chronometer& meter);
	void swig_return_userdata_measure(nonius::chronometer& meter);
	void luwra_return_userdata_measure(nonius::chronometer& meter);

	void plain_c_optional_measure(nonius::chronometer& meter);
	void sol_optional_measure(nonius::chronometer& meter);
	void old_sol_optional_measure(nonius::chronometer& meter);
	void kaguya_optional_measure(nonius::chronometer& meter);
	void lua_api_pp_optional_measure(nonius::chronometer& meter);
	void luabind_optional_measure(nonius::chronometer& meter);
	void lua_intf_optional_measure(nonius::chronometer& meter);
	void luawrapper_optional_measure(nonius::chronometer& meter);
	void oolua_optional_measure(nonius::chronometer& meter);
	void selene_optional_measure(nonius::chronometer& meter);
	void luacppinterface_optional_measure(nonius::chronometer& meter);
	void slb3_optional_measure(nonius::chronometer& meter);
	void swig_optional_measure(nonius::chronometer& meter);
	void luwra_optional_measure(nonius::chronometer& meter);

	void plain_c_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void sol_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void old_sol_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void kaguya_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void lua_api_pp_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void luabind_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void lua_intf_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void luawrapper_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void oolua_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void selene_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void luacppinterface_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void slb3_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void swig_implicit_inheritance_call_measure(nonius::chronometer& meter);
	void luwra_implicit_inheritance_call_measure(nonius::chronometer& meter);


	const int repetition = 100;
	const std::string repetition_s = "100";

	template <typename Fx>
	void repeated(Fx&& fx) {
		for (int i = 0; i < repetition; ++i)
			fx();
	}

	inline std::string repeated_code(std::string code) {
		return "for i=0," + repetition_s + " do " + code + " end";
	}
}
