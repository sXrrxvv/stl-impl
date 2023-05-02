#ifndef IMPLEMENTING_STL_SFINAE_TRAITS_H
#define IMPLEMENTING_STL_SFINAE_TRAITS_H

#include "../generic_constructs/type_constructs.h"
#include "../utility/utility.h"

namespace impl::traits{

    template<typename T, typename = void_t<T>>
    struct has_size_type : generic::false_type {};

    template<typename T>
    //we should check even reference to type, so use remove_ref on type
    struct has_size_type<T, void_t<typename remove_ref_t<T>::size_type> > : generic::true_type {};

    template < typename T>
    inline constexpr bool has_size_type_v = has_size_type<T>::value;

    template<typename T, typename = void_t<T>>
    struct has_first : generic::false_type {};

    template<typename T>
    struct has_first<T, void_t<decltype(declval<T>().first)> > : generic::true_type{};

    template<typename T>
    constexpr inline bool has_first_v = has_first<T>::value;

    template<typename T, typename = void_t<T>>
    struct is_default_constructable : generic::false_type{};

    template<typename T>
    //let it be like in std, don't decay ref to type, so applied to ref = false
    struct is_default_constructable<T, void_t<decltype(T())>> : generic::true_type{};

    template<>
    struct is_default_constructable<void> : generic::false_type{};

    template<typename T>
    inline constexpr bool is_default_constructable_v = is_default_constructable<T>::value;

    template <typename To>
    struct is_convertible{

        constexpr static void helper(To){};

        template<typename From, typename = void_t<From>>
        struct is_convertible_helper : generic::false_type{};

        template <typename From>
        //why cant call helper if not make it static? need to handle it
        //is_convertible_helper<int, void_t<decltype(helper(int&&)) can't bind non const lvalue ref to xvalue
        struct is_convertible_helper<From, void_t<decltype(helper(declval<From>()))>> : generic::true_type{};

    };

    template <typename From, typename To>
    inline constexpr bool is_convertible_v = is_convertible<To>::template is_convertible_helper<From>::value;

    template <typename T, typename = void_t<>>
    struct is_class : generic::false_type{};

    template <typename T>
    struct is_class<T, void_t<void(T::*)()>> : generic::true_type{};

    template <typename T>
    inline constexpr bool is_class_v = is_class<T>::value;

}
#endif //IMPLEMENTING_STL_SFINAE_TRAITS_H