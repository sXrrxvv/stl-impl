#ifndef IMPLEMENTING_STL_NON_SFINAE_CHECK_TRAITS_H
#define IMPLEMENTING_STL_NON_SFINAE_CHECK_TRAITS_H
#include "../generic_constructs/type_constructs.h"

namespace impl::traits{
    template <typename T1, typename T2>
    struct is_same : generic::false_type{};

    template <typename T>
    struct is_same<T,T> : generic::true_type{};

    template <typename T1, typename T2>
    inline constexpr bool is_same_v = is_same<T1,T2>::value;

    template <typename T, typename = std::size_t>
    struct is_known_size_array;

    template <typename T>
    struct is_known_size_array<T[]> : generic::false_type {};

    template <typename T, std::size_t N>
    struct is_known_size_array<T[N]> : generic::true_type{};

    template <typename T>
    inline constexpr bool is_known_size_array_v = is_known_size_array<T>::value;

//    template <typename Type, typename... Other>
//    struct all_types_different{
//        using Head = Type;
//        inline static bool val = !is_same_v<Head, typename all_types_different<Other...>::Head> && all_types_different<Other...>::val;
//    };
//
//    template <typename Type>
//    struct all_types_different<Type>{
//        using Head = Type;
//        inline static bool val = true;
//    };

}

#endif //IMPLEMENTING_STL_NON_SFINAE_CHECK_TRAITS_H
