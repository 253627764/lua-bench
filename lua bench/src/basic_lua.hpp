#pragma once

#include "basic.hpp"
#include <lua.hpp>
#include <unordered_map>

namespace lb {

	template <typename T>
	inline int gc_wrap(lua_State* L) {
		T* b = static_cast<T*>(lua_touserdata(L, 1));
		b->~T();
		return 0;
	}

	inline int basic_call_wrap(lua_State* L) {
		int x = basic_call(static_cast<int>(lua_tointeger(L, -1)));
		lua_pushinteger(L, x);
		return 1;
	}

	inline int basic_stateful_wrap(lua_State* L) {
		basic_stateful& bs = *static_cast<basic_stateful*>(lua_touserdata(L, lua_upvalueindex(1)));
		int x = bs(static_cast<int>(lua_tointeger(L, -1)));
		lua_pushinteger(L, x);
		return 1;
	}

	inline int basic_multi_return_wrap(lua_State* L) {
		int x, y;
		std::tie(x, y) = basic_multi_return(static_cast<int>(lua_tointeger(L, -1)));
		lua_pushinteger(L, x);
		lua_pushinteger(L, y);
		return 2;
	}

	inline int basic_return_wrap(lua_State* L) {
		basic* data = static_cast<basic*>(lua_newuserdata(L, sizeof(basic)));
		new (data) basic(basic_return(static_cast<int>(lua_tointeger(L, -1))));
		if (luaL_newmetatable(L, "basic") == 0) {
			lua_pushcclosure(L, &gc_wrap<basic>, 0);
			lua_setfield(L, -2, "__gc");
		}
		lua_setmetatable(L, -2);
		return 1;
	}

	inline int basic_get_wrap(lua_State* L) {
		void* x = lua_touserdata(L, 1);
		basic* b = static_cast<basic*>(x);
		lua_pop(L, 1);
		lua_pushinteger(L, b->get());
		return 1;
	}

	inline int basic_set_wrap(lua_State* L) {
		void* x = lua_touserdata(L, 1);
		int arg1 = static_cast<int>(lua_tointeger(L, 2));
		basic* b = static_cast<basic*>(x);
		lua_pop(L, 2);
		b->set(arg1);
		return 0;
	}

	inline int complex_ab_ab_func_wrap(lua_State* L) {
		void* x = lua_touserdata(L, 1);
		complex_ab* b = *static_cast<complex_ab**>(x);
		lua_pop(L, 1);
		lua_pushinteger(L, b->ab_func());
		return 1;
	}

	inline int complex_ab_b_func_wrap(lua_State* L) {
		void* x = lua_touserdata(L, 1);
		complex_ab* b = *static_cast<complex_ab**>(x);
		lua_pop(L, 1);
		lua_pushinteger(L, b->b_func());
		return 1;
	}

	inline int complex_ab_a_func_wrap(lua_State* L) {
		void* x = lua_touserdata(L, 1);
		complex_ab* b = *static_cast<complex_ab**>(x);
		lua_pop(L, 1);
		lua_pushinteger(L, b->a_func());
		return 1;
	}

	inline int complex_ab_index_wrap(lua_State* L) {
		std::size_t sz;
		const char* name = lua_tolstring(L, 2, &sz);
		if (strcmp(name, "ab_func") == 0) {
			lua_pushcclosure(L, complex_ab_ab_func_wrap, 0);
			return 1;
		}
		if (strcmp(name, "a_func") == 0) {
			lua_pushcclosure(L, complex_ab_a_func_wrap, 0);
			return 1;
		}
		if (strcmp(name, "b_func") == 0) {
			lua_pushcclosure(L, complex_ab_b_func_wrap, 0);
			return 1;
		}
		void* x = lua_touserdata(L, 1);
		complex_ab* b = static_cast<complex_ab*>(x);
		if (strcmp(name, "ab") == 0) {
			lua_pop(L, 1);
			lua_pushinteger(L, b->ab);
			return 1;
		}
		if (strcmp(name, "a") == 0) {
			lua_pop(L, 1);
			lua_pushinteger(L, b->a);
			return 1;
		}
		if (strcmp(name, "b") == 0) {
			lua_pop(L, 1);
			lua_pushinteger(L, b->b);
			return 1;
		}
		lua_pop(L, 2);
		return 0;
	}

	const std::unordered_map<std::string, decltype(&basic_large::var)> basic_large_members = {
		{ "var", &basic_large::var },
		{ "var0", &basic_large::var0 },
		{ "var1", &basic_large::var1 },
		{ "var2", &basic_large::var2 },
		{ "var3", &basic_large::var3 },
		{ "var4", &basic_large::var4 },
		{ "var5", &basic_large::var5 },
		{ "var6", &basic_large::var6 },
		{ "var7", &basic_large::var7 },
		{ "var8", &basic_large::var8 },
		{ "var9", &basic_large::var9 },
		{ "var10", &basic_large::var10 },
		{ "var11", &basic_large::var11 },
		{ "var12", &basic_large::var12 },
		{ "var13", &basic_large::var13 },
		{ "var14", &basic_large::var14 },
		{ "var15", &basic_large::var15 },
		{ "var16", &basic_large::var16 },
		{ "var17", &basic_large::var17 },
		{ "var18", &basic_large::var18 },
		{ "var19", &basic_large::var19 },
		{ "var20", &basic_large::var20 },
		{ "var21", &basic_large::var21 },
		{ "var22", &basic_large::var22 },
		{ "var23", &basic_large::var23 },
		{ "var24", &basic_large::var24 },
		{ "var25", &basic_large::var25 },
		{ "var26", &basic_large::var26 },
		{ "var27", &basic_large::var27 },
		{ "var28", &basic_large::var28 },
		{ "var29", &basic_large::var29 },
		{ "var30", &basic_large::var30 },
		{ "var31", &basic_large::var31 },
		{ "var32", &basic_large::var32 },
		{ "var33", &basic_large::var33 },
		{ "var34", &basic_large::var34 },
		{ "var35", &basic_large::var35 },
		{ "var36", &basic_large::var36 },
		{ "var37", &basic_large::var37 },
		{ "var38", &basic_large::var38 },
		{ "var39", &basic_large::var39 },
		{ "var40", &basic_large::var40 },
		{ "var41", &basic_large::var41 },
		{ "var42", &basic_large::var42 },
		{ "var43", &basic_large::var43 },
		{ "var44", &basic_large::var44 },
		{ "var45", &basic_large::var45 },
		{ "var46", &basic_large::var46 },
		{ "var47", &basic_large::var47 },
		{ "var48", &basic_large::var48 },
		{ "var49", &basic_large::var49 }
	};

	inline int basic_index_wrap(lua_State* L) {
		std::size_t sz;
		const char* name = lua_tolstring(L, 2, &sz);
		if (strcmp(name, "get") == 0) {
			lua_pushcclosure(L, basic_get_wrap, 0);
			return 1;
		}
		if (strcmp(name, "set") == 0) {
			lua_pushcclosure(L, basic_set_wrap, 0);
			return 1;
		}
		if (strcmp(name, "var") != 0) {
			lua_pop(L, 2);
			return 0;
		}
		void* x = lua_touserdata(L, 1);
		basic* b = static_cast<basic*>(x);
		lua_pop(L, 1);
		lua_pushinteger(L, b->var);
		return 1;
	}

	inline int basic_newindex_wrap(lua_State* L) {
		std::size_t sz;
		const char* name = lua_tolstring(L, 2, &sz);
		if (strcmp(name, "var") != 0) {
			lua_pop(L, 3);
			return 0;
		}
		void* x = lua_touserdata(L, 1);
		int arg1 = static_cast<int>(lua_tointeger(L, 3));
		basic* b = static_cast<basic*>(x);
		lua_pop(L, 3);
		b->var = arg1;
		return 0;
	}

	inline int basic_large_index_wrap(lua_State* L) {
		std::size_t sz;
		const char* name = lua_tolstring(L, 2, &sz);
		if (strcmp(name, "get") == 0) {
			lua_pushcclosure(L, basic_get_wrap, 0);
			return 1;
		}
		if (strcmp(name, "set") == 0) {
			lua_pushcclosure(L, basic_set_wrap, 0);
			return 1;
		}
		void* x = lua_touserdata(L, 1);
		basic_large* b = static_cast<basic_large*>(x);
		auto it = basic_large_members.find(name);
		if (it != basic_large_members.cend()) {
			const auto& bv = it->second;
			lua_pop(L, 3);
			lua_pushinteger(L, (b->*bv));
			return 1;
		}
		return 0;
	}

	inline int basic_large_newindex_wrap(lua_State* L) {
		std::size_t sz;
		const char* name = lua_tolstring(L, 2, &sz);
		if (strcmp(name, "var") != 0) {
			lua_pop(L, 3);
			return 0;
		}
		void* x = lua_touserdata(L, 1);
		basic_large* b = static_cast<basic_large*>(x);
		int arg1 = static_cast<int>(lua_tointeger(L, 3));
		auto it = basic_large_members.find(name);
		if (it != basic_large_members.cend()) {
			const auto& bv = it->second;
			int arg1 = static_cast<int>(lua_tointeger(L, 3));
			(b->*bv) = arg1;
			return 0;
		}
		return 0;
	}

	inline void lua_do_or_die(lua_State* L, const char* code) {
		if (luaL_dostring(L, code))
			lua_error(L);
	}

	inline void lua_do_or_die(lua_State* L, const std::string& code) {
		lua_do_or_die(L, code.c_str());
	}

	inline int do_panic_throw(const std::string& err) {
		throw std::runtime_error(err);
	}

	inline int panic_throw(lua_State* L) {
		const char* message = lua_tostring(L, -1);
		std::string err = message ? message : "An unexpected error occurred and forced the Lua state to panic";
		do_panic_throw(err);
		return 0;
	}

	inline void selene_panic_throw(int, std::string e, std::exception_ptr eptr) {
		try {
			if (eptr) {
				std::rethrow_exception(eptr);
			}
		}
		catch (const std::exception& e) {
			std::string err = e.what();
			do_panic_throw(err);
		}
		do_panic_throw(e);
	}

	inline void kaguya_panic_throw(int, const char* msg) {
		std::string err = msg ? msg : "An unexpected error occurred and forced the Lua state to panic";
		do_panic_throw(err);
	}

	const std::string member_variable_code = "b.var = i x = b.var";
	const std::string member_variable_large_last_code = "b.var49 = i x = b.var49";
	const std::string member_variable_large_code = "b.var = i x = b.var "
		"b.var0 = i x = b.var0 "
		"b.var49 = i x = b.var49 "
		"b.var2 = i x = b.var2 "
		"b.var47 = i x = b.var47 "
		"b.var4 = i x = b.var4 "
		"b.var45 = i x = b.var45 "
		"b.var6 = i x = b.var6 "
		"b.var43 = i x = b.var43 "
		"b.var8 = i x = b.var8 "
		"b.var41 = i x = b.var41 "
		"b.var10 = i x = b.var10 "
		"b.var39 = i x = b.var39 "
		"b.var12 = i x = b.var12 "
		"b.var37 = i x = b.var37 "
		"b.var14 = i x = b.var14 "
		"b.var35 = i x = b.var35 "
		"b.var16 = i x = b.var16 "
		"b.var33 = i x = b.var33 "
		"b.var18 = i x = b.var18 "
		"b.var31 = i x = b.var31 "
		"b.var20 = i x = b.var20 "
		"b.var29 = i x = b.var29 "
		"b.var22 = i x = b.var22 "
		"b.var27 = i x = b.var27 "
		"b.var24 = i x = b.var24 "
		"b.var25 = i x = b.var25 "
		"b.var26 = i x = b.var26 "
		"b.var23 = i x = b.var23 "
		"b.var28 = i x = b.var28 "
		"b.var21 = i x = b.var21 "
		"b.var30 = i x = b.var30 "
		"b.var19 = i x = b.var19 "
		"b.var32 = i x = b.var32 "
		"b.var17 = i x = b.var17 "
		"b.var34 = i x = b.var34 "
		"b.var15 = i x = b.var15 "
		"b.var36 = i x = b.var36 "
		"b.var13 = i x = b.var13 "
		"b.var38 = i x = b.var38 "
		"b.var11 = i x = b.var11 "
		"b.var40 = i x = b.var40 "
		"b.var9 = i x = b.var9 "
		"b.var42 = i x = b.var42 "
		"b.var7 = i x = b.var7 "
		"b.var44 = i x = b.var44 "
		"b.var5 = i x = b.var5 "
		"b.var46 = i x = b.var46 "
		"b.var3 = i x = b.var3 "
		"b.var48 = i x = b.var48 "
		"b.var1 = i x = b.var1 ";
	const std::string member_function_call_code = "b:set(i) b:get()";

}
