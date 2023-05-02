#ifndef IMPLEMENTING_STL_TYPE_CONSTRUCTS_H
#define IMPLEMENTING_STL_TYPE_CONSTRUCTS_H

namespace impl::generic{

    template <typename Type, Type val>
    struct integral_constant{
        using value_type = Type;

        inline static constexpr value_type value{val};
    };

    struct true_type : integral_constant<bool, true>{};

    struct false_type : integral_constant<bool, false>{};

    template <typename Type, Type... val>
    struct value_sequence {};

    template <int... val>
    using integer_sequence = value_sequence<int, val...>;

    template <size_t... val>
    using index_sequence = integer_sequence<val...>;

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
#endif //IMPLEMENTING_STL_TYPE_CONSTRUCTS_H
