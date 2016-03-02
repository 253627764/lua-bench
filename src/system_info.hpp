#pragma once


#include <string>
#include <cstddef>

namespace lb {
	enum class compiler {
		vcxx,
		mingw,
		gcc,
		clang,
		edg
	};

	enum class arch {
		x16,
		x86,
		x64,
		armx16,
		armx86,
		armx64,
	};

	struct system_info {
		compiler compiled_with;
		arch target_arch;
		std::string cpu_vendor;
		int64_t clockspeed;
	};
}
