#ifndef IMPLEMENTING_STL_QUALIFIERS_TRAITS_H
#define IMPLEMENTING_STL_QUALIFIERS_TRAITS_H

#include "../generic_constructs/type_constructs.h"

namespace impl::traits{
    template<typename T>
    struct remove_ref{
        using type = T;
    };

    template<typename T>
    struct remove_ref<T&> {
        using type = T;
    };

    template<typename T>
    struct remove_ref<T&&> {
        using type = T;
    };

    template<typename T>
    using remove_ref_t = typename remove_ref<T>::type;

    template<typename T>
    struct add_rvalue_ref {
        using type = T &&;
    };

    template <>
    struct add_rvalue_ref<void>{
        using type = void;
    };

    template<typename T>
    using add_rvalue_ref_t = typename add_rvalue_ref<T>::type;

    template<typename T>
    struct add_lvalue_ref {
        using type = T&;
    };

    template <>
    struct add_lvalue_ref<void>{
        using type = void;
    };

    template<typename T>
    using add_lvalue_ref_t = typename add_lvalue_ref<T>::type;

    template<typename T>
    struct add_const{
        using type = const T;
    };

    template <typename T>
    using add_const_t = typename add_const<T>::type;

    template<typename T>
    struct remove_const{
        using type = T;
    };

    template<typename T>
    struct remove_const<const T>{
        using type = T;
    };

    template <typename T>
    using remove_const_t = typename remove_const<T>::type;

    template <typename T>
    struct remove_volatile{
        using type = T;
    };

    template <typename T>
    struct remove_volatile<volatile T>{
        using type = T;
    };

    template <typename T>
    using remove_volatile_t = typename remove_volatile<T>::type;

    template <typename T>
    struct add_volatile{
        using type = volatile T;
    };

    template <typename T>
    using add_volatile_t = typename add_volatile<T>::type;

    template <typename T, typename = std::size_t>
    struct to_pointer{
        using type = T;
    };

    template <typename T>
    struct to_pointer<T[]>{
        using type = T*;
    };

    template <typename T, std::size_t N>
    struct to_pointer<T[N]>{
        using type = T*;
    };

    template <typename T>
    struct to_pointer<T*>{
        using type = T*;
    };

    template<typename T>
    using to_pointer_t = typename to_pointer<T>::type;

    template <typename T>
    struct decay{
        //must discard ref at first, or we get broken logic
        using type = remove_const_t<remove_volatile_t<to_pointer_t<remove_ref_t<T>>>>;
    };

    template <typename T>
    using decay_t = typename decay<T>::type;

    template <typename T>
    struct is_lvalue_ref : generic::false_type{};

    template <typename T>
    struct is_lvalue_ref<T&> : generic::true_type{};

    template <typename T>
    inline constexpr bool is_lvalue_ref_t = is_lvalue_ref<T>::value;

    template <typename T>
    struct is_rvalue_ref : generic::false_type{};

    template <typename T>
    struct is_rvalue_ref<T&&> : generic::true_type{};

    template <typename T>
    inline constexpr bool is_rvalue_ref_v = is_rvalue_ref<T>::value;

    template <typename T>
    inline constexpr bool is_ref_v = is_lvalue_ref_t<T> || is_rvalue_ref_v<T>;
}

#endif //IMPLEMENTING_STL_QUALIFIERS_TRAITS_H
