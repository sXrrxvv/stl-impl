#ifndef IMPLEMENTING_STL_UTILITY_H
#define IMPLEMENTING_STL_UTILITY_H
#include "../traits/qualifiers_traits.h"

namespace impl {

    template<typename... Args>
    using void_t = void;

    template<typename T>
    constexpr impl::traits::add_rvalue_ref_t<T> declval() noexcept;

    // move impl
    // suppose we pass int with some ref qualifiers, variants are:

    // 1) pass int, so T deduced to int and decltype(val) = int&&, return type is int&& and we cast to int&&
    // 2) pass int&, so T deduced to int& and decltype(val) = int&, return type is int&& and we are done by casting lvalue ref to rvalue ref
    // 3) pass int&&, so T deduced to int, decltype(val) = int&&, similar to first variant.

    // notice that we cant return/cast to T&&, because due to reference collapsing rules, if we pass int&, both T and T&& are int& and we have broken move logic in that case.
    template <typename T>
    constexpr impl::traits::remove_ref_t<T>&& move(T&& val) noexcept{
        return static_cast<impl::traits::remove_ref_t<T>&&>(val);
    }

    //forward impl:
    //similar to move. Add remove_ref_t here to disable deduction
    template <typename T>
    T&& forward(impl::traits::remove_ref_t<T>& val){
        return static_cast<T&&>(val);
    }

    template <typename T>
    T&& forward(impl::traits::remove_ref_t<T>&& val){
        return static_cast<T&&>(val);
    }

//   //interesting example : suppose we explicitly call this with T substituted with some ref type (either lvalue ref or rvalue ref)
//   //const will be applied to T, and T is ref, so const does nothing. For example : T -> int&, so we get (const (int&))&& == int&
//  my question :
// https://stackoverflow.com/questions/75915549/decltype-of-function-call-discards-const-qualifiers

//    template <typename T>
//    const T&& interesting_const_example();


    template<typename Out, typename In, size_t... Ind>
    Out create_from_indexes(const In &from, generic::index_sequence<Ind...> indexes) {
        Out created{};
        (created.push_back(from[Ind - 1]), ... );
        return created;
    }
}
#endif //IMPLEMENTING_STL_UTILITY_H
