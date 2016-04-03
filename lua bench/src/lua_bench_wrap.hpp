#pragma once

#include "lua_bench.hpp"
#include "basic.hpp"
#include <lua.hpp>

namespace lb {

	int basic_call_wrap(lua_State* L) {
		int x = basic_call(static_cast<int>(lua_tointeger(L, -1)));
		lua_pushinteger(L, x);
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

	inline int basic_index_wrap(lua_State* L) {
		std::size_t sz;
		const char* name = lua_tolstring(L, 2, &sz);
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

}
