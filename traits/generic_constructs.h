#ifndef IMPLEMENTING_STL_GENERIC_CONSTRUCTS_H
#define IMPLEMENTING_STL_GENERIC_CONSTRUCTS_H

//should be in traits??
namespace impl::traits{

    template <typename Type, Type val>
    struct integral_constant{
        using value_type = Type;

        inline static constexpr value_type value{val};
    };

    struct true_type : integral_constant<bool, true>{};

    struct false_type : integral_constant<bool, false>{};

    template <bool Predicate, typename TrueType, typename FalseType>
    struct conditional{};

    template <typename TrueType, typename FalseType>
    struct conditional<true, TrueType, FalseType>{
        using type = TrueType;
    };

    template <typename TrueType, typename FalseType>
    struct conditional<false, TrueType, FalseType>{
        using type = FalseType;
    };

    template <bool Predicate, typename TrueType, typename FalseType>
    using conditional_t = typename conditional<Predicate, TrueType, FalseType>::type;

    template <bool Predicate, typename Type>
    struct enable_if{};

    template<typename Type>
    struct enable_if<true, Type>{
        using type = Type;
    };

    template<bool Predicate, typename Type>
    using enable_if_t = typename enable_if<Predicate, Type>::type;

}
#endif //IMPLEMENTING_STL_GENERIC_CONSTRUCTS_H
