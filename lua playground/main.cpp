#include <oolua.h>

struct basic {
	int var = 500;

	int get() const {
		return var;
	}

	void set(int x) {
		var = x;
	}
};

inline int panic_throw(lua_State* L) {
	const char* message = lua_tostring(L, -1);
	std::string err = message ? message : "An unexpected error occurred and forced the lua state to call atpanic";
	throw std::runtime_error(err);
}

namespace OOLUA {
	template<> 
	class Proxy_class<basic> {
	public: 
		typedef INTERNAL::Proxy_type<Proxy_class>::Type class_; 
		typedef Proxy_class<class_> this_type; 
		typedef int (Proxy_class::*mfp)(lua_State * const); 
		typedef int (Proxy_class::*mfp_const)(lua_State * const)const; 
		struct Reg_type { const char *name; mfp mfunc; }; 
		struct Reg_type_const { const char *name; mfp_const mfunc; }; 
		static char const class_name[]; 
		static char const class_name_const[]; 
		static Reg_type class_methods[]; 
		static Reg_type_const class_methods_const[]; 
		
		class_ * m_this; 
		
		Proxy_class() :m_this(0) {} 
		Proxy_class(class_* p) :m_this(p) { set_this_ptr(); } 
		Proxy_class& operator = (Proxy_class const &); Proxy_class(Proxy_class const &); 
		virtual ~Proxy_class() {} 
	private: 
		void set_this_ptr() { 
			INTERNAL::Set_this_ptr< this_type, AllBases, 0, TYPELIST::At_default< AllBases, 0, TYPE::Null_type >::Result > ptr; 
			ptr(this, m_this); 
		} 
	public: 
		typedef TYPE::Null_type Bases; 
		typedef INTERNAL::FindAllBases<class_>::Result AllBases;
		int get_var(lua_State* vm) const { OOLUA::INTERNAL::PushPublicMember::push(vm, &m_this->var); return 1; } 
		int set_var(lua_State* vm) { OOLUA::INTERNAL::GetPublicMember::get(vm, &m_this->var); return 0; }
		int get(lua_State* vm) const { return OOLUA::INTERNAL::constproxy_member_function_with_default_traits(vm, m_this, &class_::get); }
		int set(lua_State* vm) { return OOLUA::INTERNAL::proxy_member_function_with_default_traits(vm, m_this, &class_::set); }
	};
}

namespace OOLUA {
	char const OOLUA::Proxy_class< basic >::class_name_const[] = "basic" "_const"; 
	OOLUA::Proxy_class< basic >::Reg_type_const OOLUA::Proxy_class< basic >::class_methods_const[] = { { "get", &OOLUA::Proxy_class< basic >::get },{ 0, 0 } };
}
namespace OOLUA {
	char const OOLUA::Proxy_class< basic >::class_name[] = "basic"; 
	OOLUA::Proxy_class< basic >::Reg_type OOLUA::Proxy_class< basic >::class_methods[] = { { "set", &OOLUA::Proxy_class< basic >::set },{ 0, 0 } };
}


int main(int argc, char* argv[]) {
	
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, panic_throw);

	vm.register_class<basic>();
	if (!vm.run_chunk("b = basic.new()")) {
		auto str = OOLUA::get_last_error(vm);
		luaL_error(vm, str.c_str());
	}

	std::string fcode = "b:set(1) b:get()";
	if (!vm.run_chunk(fcode)) {
		auto str = OOLUA::get_last_error(vm);
		luaL_error(vm, str.c_str());
	}


	std::string code = "b.var = 1\nx = b.var";
	if (!vm.run_chunk(code)) {
		auto str = OOLUA::get_last_error(vm);
		luaL_error(vm, str.c_str());
	}
	
	return 0;
}
