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

	struct basic_binding_base {
		virtual int indexing(lua_State* L) = 0;
		virtual int new_indexing(lua_State* L) = 0;
		virtual ~basic_binding_base() {}
	};

	template <typename F>
	struct variable_binding : basic_binding_base {
		F f;
		variable_binding(F f) : f(std::move(f)) {}

		virtual int indexing(lua_State* L) override {
			void* x = lua_touserdata(L, 1);
			basic_large** pb = static_cast<basic_large**>(x);
			basic_large& b = **pb;
			auto value = (b.*f);
			if (std::is_integral<decltype(value)>::value) {
				lua_pushinteger(L, static_cast<lua_Integer>(value));
			}
			else {
				lua_pushnumber(L, static_cast<lua_Number>(value));
			}
			return 1;
		}

		virtual int new_indexing(lua_State* L) override {
			void* x = lua_touserdata(L, 1);
			basic_large** pb = static_cast<basic_large**>(x);
			basic_large& b = **pb;
			typedef std::decay_t<decltype((b.*f))> T;
			if (std::is_integral<T>::value) {
				lua_Integer arg1 = lua_tointeger(L, 3);
				(b.*f) = static_cast<T>(arg1);
			}
			else {
				lua_Number arg1 = lua_tonumber(L, 3);
				(b.*f) = static_cast<T>(arg1);
			}
			return 0;
		}
	};

	template <typename Base, typename T, typename... Args>
	inline std::unique_ptr<Base> make_base_unique(Args&&... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	inline auto& basic_large_members() {
		static std::unordered_map<std::string, std::unique_ptr<basic_binding_base>> members = []() {
			std::unordered_map<std::string, std::unique_ptr<basic_binding_base>> m;
			m.emplace_hint(m.cend(), "var", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var)>>(&basic_large::var));
			m.emplace_hint(m.cend(), "var0", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var0)>>(&basic_large::var0));
			m.emplace_hint(m.cend(), "var1", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var1)>>(&basic_large::var1));
			m.emplace_hint(m.cend(), "var2", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var2)>>(&basic_large::var2));
			m.emplace_hint(m.cend(), "var3", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var3)>>(&basic_large::var3));
			m.emplace_hint(m.cend(), "var4", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var4)>>(&basic_large::var4));
			m.emplace_hint(m.cend(), "var5", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var5)>>(&basic_large::var5));
			m.emplace_hint(m.cend(), "var6", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var6)>>(&basic_large::var6));
			m.emplace_hint(m.cend(), "var7", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var7)>>(&basic_large::var7));
			m.emplace_hint(m.cend(), "var8", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var8)>>(&basic_large::var8));
			m.emplace_hint(m.cend(), "var9", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var9)>>(&basic_large::var9));
			m.emplace_hint(m.cend(), "var10", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var10)>>(&basic_large::var10));
			m.emplace_hint(m.cend(), "var11", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var11)>>(&basic_large::var11));
			m.emplace_hint(m.cend(), "var12", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var12)>>(&basic_large::var12));
			m.emplace_hint(m.cend(), "var13", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var13)>>(&basic_large::var13));
			m.emplace_hint(m.cend(), "var14", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var14)>>(&basic_large::var14));
			m.emplace_hint(m.cend(), "var15", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var15)>>(&basic_large::var15));
			m.emplace_hint(m.cend(), "var16", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var16)>>(&basic_large::var16));
			m.emplace_hint(m.cend(), "var17", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var17)>>(&basic_large::var17));
			m.emplace_hint(m.cend(), "var18", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var18)>>(&basic_large::var18));
			m.emplace_hint(m.cend(), "var19", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var19)>>(&basic_large::var19));
			m.emplace_hint(m.cend(), "var20", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var20)>>(&basic_large::var20));
			m.emplace_hint(m.cend(), "var21", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var21)>>(&basic_large::var21));
			m.emplace_hint(m.cend(), "var22", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var22)>>(&basic_large::var22));
			m.emplace_hint(m.cend(), "var23", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var23)>>(&basic_large::var23));
			m.emplace_hint(m.cend(), "var24", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var24)>>(&basic_large::var24));
			m.emplace_hint(m.cend(), "var25", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var25)>>(&basic_large::var25));
			m.emplace_hint(m.cend(), "var26", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var26)>>(&basic_large::var26));
			m.emplace_hint(m.cend(), "var27", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var27)>>(&basic_large::var27));
			m.emplace_hint(m.cend(), "var28", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var28)>>(&basic_large::var28));
			m.emplace_hint(m.cend(), "var29", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var29)>>(&basic_large::var29));
			m.emplace_hint(m.cend(), "var30", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var30)>>(&basic_large::var30));
			m.emplace_hint(m.cend(), "var31", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var31)>>(&basic_large::var31));
			m.emplace_hint(m.cend(), "var32", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var32)>>(&basic_large::var32));
			m.emplace_hint(m.cend(), "var33", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var33)>>(&basic_large::var33));
			m.emplace_hint(m.cend(), "var34", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var34)>>(&basic_large::var34));
			m.emplace_hint(m.cend(), "var35", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var35)>>(&basic_large::var35));
			m.emplace_hint(m.cend(), "var36", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var36)>>(&basic_large::var36));
			m.emplace_hint(m.cend(), "var37", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var37)>>(&basic_large::var37));
			m.emplace_hint(m.cend(), "var38", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var38)>>(&basic_large::var38));
			m.emplace_hint(m.cend(), "var39", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var39)>>(&basic_large::var39));
			m.emplace_hint(m.cend(), "var40", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var40)>>(&basic_large::var40));
			m.emplace_hint(m.cend(), "var41", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var41)>>(&basic_large::var41));
			m.emplace_hint(m.cend(), "var42", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var42)>>(&basic_large::var42));
			m.emplace_hint(m.cend(), "var43", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var43)>>(&basic_large::var43));
			m.emplace_hint(m.cend(), "var44", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var44)>>(&basic_large::var44));
			m.emplace_hint(m.cend(), "var45", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var45)>>(&basic_large::var45));
			m.emplace_hint(m.cend(), "var46", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var46)>>(&basic_large::var46));
			m.emplace_hint(m.cend(), "var47", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var47)>>(&basic_large::var47));
			m.emplace_hint(m.cend(), "var48", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var48)>>(&basic_large::var48));
			m.emplace_hint(m.cend(), "var49", make_base_unique<basic_binding_base, variable_binding<decltype(&basic_large::var49)>>(&basic_large::var49));
			return m;
		}();
		return members;
	}

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
		basic* b = *static_cast<basic**>(x);
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
		basic* b = *static_cast<basic**>(x);
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
		basic_large** pb = static_cast<basic_large**>(x);
		basic_large& b = **pb;
		auto it = basic_large_members().find(name);
		if (it != basic_large_members().cend()) {
			auto& bv = it->second;
			return bv->indexing(L);
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
		basic_large** pb = static_cast<basic_large**>(x);
		basic_large& b = **pb;
		int arg1 = static_cast<int>(lua_tointeger(L, 3));
		auto it = basic_large_members().find(name);
		if (it != basic_large_members().cend()) {
			auto& bv = it->second;
			return bv->new_indexing(L);
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

	const std::string userdata_variable_access_code = "b.var = i x = b.var";
	const std::string userdata_variable_access_large_last_code = "b.var49 = i x = b.var49";
	const std::string userdata_variable_access_large_code = "b.var = i x = b.var "
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
