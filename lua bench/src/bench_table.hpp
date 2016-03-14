#pragma once

#include <cassert>

namespace lb { namespace table {
	const char key_c_str[] = "value";
	const int key_int = 0;
	const void* key_light_user_data = nullptr;
	const int value = 0;
	
	struct generic_get {

	}

	template <typename T>
	void get_setup(T&& tableobject, Key&& key) {
		tableobject[key] = 0;
	}

	template <typename T, typename Key>
	int get_bench(T&& tableobject, Key&& key) {
		int r = 0;
		for (int i = 0; i < 100; ++i) {
			int v = tableobject[key];
			r += v;
		}
		return r;
	}

	template <typename T, typename Key0, typename Key1>
	void get_chain_setup(T&& tableobject, Key0&& key0, Key1&& key1) {
		tableobject[key0][key1] = 0;
	}

	template <typename T, typename Key0, typename Key1>
	int get_chain_bench(T&& tableobject, Key0&& key0, Key1&& key1) {
		int r = 0;
		for (int i = 0; i < 100; ++i) {
			int v = tableobject[key];
			r += v;
		}
		return r;
	}

	template <typename T, typename Key>
	int set_bench(T&& tableobject, Key&& key) {
		for (int i = 0; i < 100; ++i) {
			tableobject[key] = i;
		}
	}

	template <typename T, typename Key0, typename Key1>
	int set_chain_bench(T&& tableobject, Key0&& key0, Key1&& key1) {
		for (int i = 0; i < 100; ++i) {
			tableobject[key0][key1] = i;
		}
	}
}}
