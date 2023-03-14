#include <iostream>
#include <vector>

#include "traits/generic_constructs.h"
#include "traits/qualifiers_traits.h"
#include "traits/non_sfinae_check_traits.h"
#include "traits/sfinae_traits.h"
#include "tests/test_objects.h"
#include "utility/utility.h"


using namespace impl::traits;

template <typename... Args>
void f(Args... args);


int main() {
 //Qualifiers traits tests
 //_____________________________________________________________________________________________________________________

        //add ref test
    //    int x;
    //    impl::traits::add_lvalue_ref_t<int> ref{x};
    //    impl::traits::add_rvalue_ref_t<int> r_ref{5};
    //    std::cout << impl::traits::is_same_v<int&, impl::traits::add_lvalue_ref_t<int>> << '\n';
    //    std::cout << impl::traits::is_same_v<int&&, impl::traits::add_rvalue_ref_t<int>> << '\n';
    //    std::cout << impl::traits::is_same_v<int&, impl::traits::add_rvalue_ref_t<int>> << '\n';

          //is_same test
    //    std::cout << impl::traits::is_same_v<int,int&> << '\n';
    //    std::cout << impl::traits::is_same_v<int,int> << '\n';
    //    std::cout << impl::traits::is_same_v<int,impl::traits::remove_ref_t<int&&>> << '\n';

    //    remove_ref_tests
    //    std::cout << impl::traits::is_same_v<int, impl::traits::remove_ref_t<int&>> << '\n';
    //    std::cout << impl::traits::is_same_v<int, impl::traits::remove_ref_t<int&&>> << '\n';

    //    add/remove_c/v test
    //    std::cout << std::is_same_v<impl::traits::remove_const_t<const int>, int> << '\n';
    //    std::cout << std::is_same_v<impl::traits::add_const_t<int>, const int> << '\n';
    //    std::cout << is_same_v<const int, remove_ref_t<const int&&>> << '\n';

    //    std::cout << is_same_v<int&, remove_const_t<const int&>> << '\n';
    //    !!!
    //    here we have int& lhs and const int& rhs. const applied to type, not to ref, and our func discard ref qualifier


    //    std::cout << is_same_v<int* const, add_const_t<int*>> << '\n';
    //    std::cout << is_same_v<const int&, add_lvalue_ref_t<add_const_t<int>>> << '\n';

    //    std::cout << is_same_v<const int&, remove_volatile_t<const volatile int&>> << '\n';
    //    !!!
    //    this test fails cause we should differ volatile int& and int& volatile, second is forbidden btw similar to ref test shit btw

    //    std::cout << is_same_v<const int, remove_volatile_t<const volatile int>> << '\n';
    //    std::cout << is_same_v<const volatile int, add_volatile_t<const int>> << '\n';

    //to_pointer_test
//    std::cout << is_same_v<int*, to_pointer_t<int[10]>> << '\n';
//    std::cout << is_same_v<int*, to_pointer_t<int[]>> << '\n';
//    std::cout << is_same_v<int, to_pointer_t<int>> << '\n';

        //decay test
//     std::cout << is_same_v<int, decay_t<const volatile int&>> << '\n';
//     std::cout << is_same_v<int*, decay_t<int[10]>> << '\n';

    //is_ref test
//     std::cout << is_lvalue_ref_t<int&> << '\n';
//     std::cout << is_rvalue_ref_v<int&&> << '\n';
//     std::cout << is_rvalue_ref_v<int&> << '\n';
//     std::cout << is_ref_v<int&> << '\n';
//     std::cout << is_ref_v<int> << '\n';
//______________________________________________________________________________________________________________________

//    array size test
//    std::cout << is_known_size_array_v<int[2]> << '\n';
//    std::cout << is_known_size_array_v<int[]> << '\n';

//......................................................................................................................

//    has_first test

//    std::cout << has_first_v<std::pair<int,int>> << '\n';
//    std::cout << has_first_v<noDefCtorWithMemberFirst> << '\n';
//    std::cout << has_first_v<std::vector<int>> << '\n';


    //has_size_type test
//    std::cout << has_size_type<std::vector<int>>::value << '\n';
//    std::cout << has_size_type_v<int> << '\n';

//!!! depend on impl
//    std::cout << has_size_type_v<std::vector<int>&> << '\n';

    //is_default_constructable test
//    std::cout << is_default_constructable_v<int> << '\n';
//    std::cout << is_default_constructable_v<int&> << '\n';
//    std::cout << is_default_constructable_v<impl::test::noDefCtor> << '\n';


//      is_convertible test
//    std::cout << is_convertible_v<int, char> << '\n';
//    std::cout << is_convertible_v<int, long> << '\n';
//    std::cout << is_convertible_v<int, noDefCtor> << '\n';
//    std::cout << is_convertible_v<const int&, int> << '\n';
//    std::cout << is_convertible_v<noDefCtor, noDefCtorWithMemberFirst> << '\n';

//    conditiontal test
//std::cout << is_same_v<int, conditional_t<is_lvalue_ref_t<int&>, int, int&&>> << '\n';
//std::cout << is_same_v<int&&, conditional_t<is_lvalue_ref_t<int&&>, int, int&&>> << '\n';

//create_from_index test
//    std::vector v{1,2,3,4,5};
//    for(const auto& elem : create_from_indexes<int, 1,2,3,4,0>(v)){
//        std::cout << elem << '\n';
//    }

//enable_if test
//    impl::test::enable_if_test::test<std::vector<int>>();
//    impl::test::enable_if_test::test<int>();
//    impl::test::substitution_failure_without_size_type<std::vector<int>> works;
//    impl::test::substitution_failure_without_size_type<int> failure;



 return 0;
}
