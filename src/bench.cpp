#include "bench_cpp_function.hpp"
#include "bench_lua_function.hpp"
#include "bench_get.hpp"
#include "bench_set.hpp"
#include "bench_usertype.hpp"
#include "nonius/nonius.h++"

int main( int argc, char* argv[] ) {
	bench_lua_function( "bench/" );
	bench_cpp_function( "bench/" );
	bench_get( "bench/" );
	bench_set( "bench/" );
	bench_usertype( "bench/" );
}
