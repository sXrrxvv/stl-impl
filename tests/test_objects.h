#ifndef IMPLEMENTING_STL_TEST_OBJECTS_H
#define IMPLEMENTING_STL_TEST_OBJECTS_H
#include "../traits/sfinae_traits.h"

namespace impl::test{
    struct noDefCtor {
        noDefCtor() = delete;
    };

    struct noDefCtorWithMemberFirst : noDefCtor {
        int first;
    };

    struct enable_if_test {
        template<typename Container>
        impl::traits::enable_if_t<impl::traits::has_size_type_v<Container>, void>
                constexpr static test(){
            std::cout << "overload for types with ::size_type\n";
        }

        template<typename Container>
        impl::traits::enable_if_t<!impl::traits::has_size_type_v<Container>, void>
                constexpr static test(){
            std::cout << "overload for types without ::size_type\n";
        }
    };

    //TODO: read more about sfinae error, where instantiating applies and where it would be an error
//    template <typename Container, typename = void>
//    struct substitution_failure_without_size_type{};
//
//    template <typename Container>
//    struct substitution_failure_without_size_type<Container,
//            typename impl::traits::enable_if_t<impl::traits::has_size_type_v<Container>, void>> {};
//
//    template <typename Container>
//    struct substitution_failure_without_size_type<Container,
//            typename impl::traits::enable_if_t<!impl::traits::has_size_type_v<Container>, void>::type>{};

}
#endif //IMPLEMENTING_STL_TEST_OBJECTS_H
