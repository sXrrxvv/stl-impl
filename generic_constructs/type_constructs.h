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


    //Interesting: T[N] is decayed to T* when it is function parameter, but no decay when it is template param,
    //so we must accept ref to array, funny
    //maybe stl version is variadic, so we can specialize for containers with size member via sfinae specialization
    // like decltype(declval<Container>().size) or with enable_if_t<has_size_member_v<Container>, void>
    template <typename T, std::size_t N>
    constexpr std::size_t size(T(&)[N]) {
        return N;
    }

}
#endif //IMPLEMENTING_STL_TYPE_CONSTRUCTS_H
