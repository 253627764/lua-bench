#pragma once

#include <functional>
#include <vector>
#include <type_traits>

namespace detail {
	template<typename T, template<typename...> class Templ>
	struct is_specialization_of : std::false_type { };
	template<typename... T, template<typename...> class Templ>
	struct is_specialization_of<Templ<T...>, Templ> : std::true_type { };

	template <typename C>
	inline auto adl_begin(C&& c) {
		using std::begin;
		return begin(c);
	}

	template <typename C>
	inline auto adl_end(C&& c) {
		using std::end;
		return end(c);
	}

	template <typename C>
	inline auto adl_cbegin(C&& c) {
		using std::cbegin;
		return cbegin(c);
	}

	template <typename C>
	inline auto adl_cend(C&& c) {
		using std::cend;
		return cend(c);
	}

	template <typename C, typename P, std::enable_if_t<is_specialization_of<std::remove_const_t<std::remove_reference_t<C>>, std::list>::value, int> = 0>
	inline void adl_sort(C&& c, P&& p) {
		c.sort(std::forward<P>(p));
	}

	template <typename C, typename P, std::enable_if_t<!is_specialization_of<std::remove_const_t<std::remove_reference_t<C>>, std::list>::value, int> = 0>
	inline void adl_sort(C&& c, P&& p) {
		std::sort(adl_begin(c), adl_end(c), std::forward<P>(p));
	}
}

template <typename Val, typename Compare = std::less<>, typename Equality = std::equal_to<>, typename Cont = std::vector<Val>>
struct ordered;

template <typename Cont, typename Compare = std::less<>, typename Equality = std::equal_to<>>
using ordered_container = ordered<typename Cont::value_type, Compare, Equality, Cont>;

template <typename Val, typename Compare, typename Equality, typename Cont>
struct ordered {
private:
	Cont container;
	Compare compare_predicate; // TODO: EBCO this member
	Equality equality_predicate; // TODO: EBCO this member

	void do_sort() {
		detail::adl_sort(container, std::ref(compare_predicate));
	}

public:
	typedef typename Cont::value_type key_type;
	typedef typename Cont::value_type value_type;
	typedef typename Cont::reference reference;
	typedef typename Cont::const_reference const_reference;
	typedef typename Cont::pointer pointer;
	typedef typename Cont::const_pointer const_pointer;
	typedef Compare key_compare;
	typedef Equality value_compare;
	typedef typename Cont::allocator_type allocator_type;
	typedef typename Cont::size_type size_type;
	typedef typename Cont::difference_type difference_type;
	typedef size_type index_type;
	typedef typename Cont::iterator begin_iterator;
	typedef typename Cont::iterator end_iterator;
	typedef typename Cont::iterator iterator;
	typedef typename Cont::const_iterator const_iterator;

	ordered(const ordered&) = default;
	ordered(ordered&&) = default;
	ordered& operator=(const ordered&) = default;
	ordered& operator=(ordered&&) = default;
	ordered(std::add_const_t<std::add_lvalue_reference_t<Cont>> c) : container(c), compare_predicate() {}
	ordered(std::add_rvalue_reference_t<Cont> c) : container(std::move(c)), compare_predicate() {}
	template <typename P>
	ordered(std::add_const_t<std::add_lvalue_reference_t<Cont>> c, P&& p) : container(c), compare_predicate(std::forward<P>(p)) {}
	template <typename P>
	ordered(std::add_rvalue_reference_t<Cont> c, P&& p) : container(std::move(c)), compare_predicate(std::forward<P>(p)) {}
	template <typename BeginIt, typename EndIt>
	ordered(BeginIt first, EndIt last) : container(std::move(first), std::move(last)), compare_predicate() {
		do_sort();
	}
	template <typename BeginIt, typename EndIt, typename P>
	ordered(BeginIt first, EndIt last, P&& p) : container(std::move(first), std::move(last)), compare_predicate(std::forward<P>(p)) {
		do_sort();
	}

	template <typename K>
	const_iterator find(K&& k) const {
		auto e = cend();
		if (container.empty()) {
			return e;
		}
		auto elementgreaterthanorequalto = std::lower_bound(cbegin(), e, k, std::ref(compare_predicate));
		if (elementgreaterthanorequalto == e) {
			return elementgreaterthanorequalto;
		}
		decltype(auto) elem = *elementgreaterthanorequalto;
		if (equality_predicate(std::forward<K>(k), elem)) {
			return elementgreaterthanorequalto;
		}
		return e;
	}

	template <typename K>
	iterator find(K&& k) {
		auto e = end();
		if (container.empty()) {
			return e;
		}
		auto elementgreaterthanorequalto = std::lower_bound(begin(), e, k, std::ref(compare_predicate));
		if (elementgreaterthanorequalto == e) {
			return elementgreaterthanorequalto;
		}
		decltype(auto) elem = *elementgreaterthanorequalto;
		if (equality_predicate(std::forward<K>(k), elem)) {
			return elementgreaterthanorequalto;
		}
		return e;
	}

	iterator insert(const value_type& val) {
		if (container.empty()) {
			return container.insert(cend(), val);
		}
		auto elementgreaterthanorequalto = std::lower_bound(cbegin(), cend(), val, std::ref(compare_predicate));
		return container.insert(elementgreaterthanorequalto, val);
	}

	iterator insert(value_type&& val) {
		if (container.empty()) {
			return container.insert(cend(), val);
		}
		auto elementgreaterthanorequalto = std::lower_bound(cbegin(), cend(), val, std::ref(compare_predicate));
		return container.insert(elementgreaterthanorequalto, std::move(val));
	}

	template <typename... Tn>
	iterator emplace(Tn&&... argn) {
		if (container.empty()) {
			return container.emplace(cend(), std::forward<Tn>(argn)...);
		}
		auto elementgreaterthanorequalto = std::lower_bound(cbegin(), cend(), val, std::ref(compare_predicate));
		return container.emplace(elementgreaterthanorequalto, std::forward<Tn>(argn)...);
	}

	iterator erase(index_type i) {
		auto it = std::next(cbegin(), i);
		return erase(it);
	}

	iterator erase(const_iterator i) {
		return container.erase(i);
	}

	void clear() {
		container.clear();
	}

	size_type size() const { return container.size(); }

	auto begin() { return detail::adl_begin(container); }
	auto begin() const { return detail::adl_begin(container); }
	auto cbegin() const { return detail::adl_cbegin(container); }
	auto end() { return detail::adl_end(container); }
	auto end() const { return detail::adl_end(container); }
	auto cend() const { return detail::adl_cend(container); }
};
