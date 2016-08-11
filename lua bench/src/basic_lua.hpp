#pragma once

#include "basic.hpp"
#include <lua.hpp>

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
