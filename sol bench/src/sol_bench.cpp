#include "bench_cpp_function.hpp"
#include "bench_lua_function.hpp"
#include "bench_get.hpp"
#include "bench_set.hpp"
#include "bench_usertype.hpp"
#include "platform.hpp"

int main(int argc, char* argv[]) {
#ifndef INTERNAL_BENCHMARKS

#else
#ifdef LUA_BENCH_DEBUG
	std::string configurationname = "Debug";
#else
	std::string configurationname = "Release";
#endif
#ifdef LUA_BENCH_x64
	std::string platformname = "x64";
#else
	std::string platformname = "x86";
#endif
	bench_lua_function("results/", configurationname, platformname);
	bench_cpp_function("results/", configurationname, platformname);
	bench_get("results/", configurationname, platformname);
	bench_set("results/", configurationname, platformname);
	bench_usertype("results/", configurationname, platformname);
#endif
}
