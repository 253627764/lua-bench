#pragma once

#include "basic.hpp"
#include <lua.hpp>

inline int basic_call_wrap(lua_State* L) {
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

inline void lua_do_or_die(lua_State* L, const char* code) {
	if (luaL_dostring(L, code))
		lua_error(L);
}

inline void lua_do_or_die(lua_State* L, const std::string& code) {
	lua_do_or_die(L, code.c_str());
}

inline int panic_throw(lua_State* L) {
	const char* message = lua_tostring(L, -1);
	std::string err = message ? message : "An unexpected error occurred and forced the lua state to call atpanic";
	throw std::runtime_error(err);
}

