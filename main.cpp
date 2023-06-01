#include <iostream>

//TODO: rewrite headers in one order for precompiled headers

#include "generic_constructs/type_constructs.h"
#include "traits/qualifiers_traits.h"
#include "traits/non_sfinae_check_traits.h"
#include "traits/sfinae_traits.h"
#include "tests/test_objects.h"
#include "utility/utility.h"
#include "generic_constructs/CRTP.h"
#include "tests/test_objects.h"
#include "generic_constructs/function.h"
#include "generic_constructs/tuple.h"
#include "memory/unique_ptr.h"

//TODO: Variant, u_map, deque, pull allocator, shared/weak ptrs.

using namespace impl;

//struct A{
//    int val;
//
//    A() = default;
//
//    A(const int& val) {
//        this->val = val;
//    }
//
//    A(const A& rhs){
//        val = rhs.val;
//    }
//
//    A(A&& rhs){
//        val = rhs.val;
//        rhs.val = 0;
//    }
//
//    A& operator = (const A& rhs)= default;
//
//    A& operator = (A&& rhs) noexcept{
//        val = rhs.val;
//        rhs.val = 0;
//        return *this;
//    }
//
//    A(int&& val) noexcept{
//        this->val = val;
//        val = 0;
//    }
//};


int main() {

//    memory::unique_ptr<int> u_ptr = new int(5);
//
//    std::cout << *u_ptr;

//    generic::tuple <A, double> t{A(10), 2.0};
//    auto t2 = move(t);
//    std::cout << t2.get_head().get_val().val << '\n';
//    std::cout << t.get_head().get_val().val << '\n';
//    generic::get<0>(t2).val = 50;
//    std::cout << generic::get<0>(t2).val;
//
//    generic::tuple<int, double> t1{5, 3.0};
//    generic::tuple<int, double> t2 = move(t1);
//    t1 = t2;
//    std::cout << t2.val;

    //    TODO : need to investigate google unit for experience, or, at least change all to static_assert for practical use, or just include in test_objects.h
    //
//    generic::tuple<std::string, std::string, std::string> t = {"abc", "bcd", "cde"};
//    std::cout << sizeof(t);
//
//    std::string str{"abc"};
//    std::tuple<std::string> t1;
//    std::tuple<char> t2{'1'};
//    t1 = t2;

//    std::cout << sizeof(std::string) << '\n';
//    std::cout << sizeof(std::tuple<std::string, std::string, std::string>);
//    generic::function<void(double, int)> func{&foo};
//
//    func(1,2+3);
//
//    auto l1 = [](double x, int y){std::cout << x+y << '\n';};
//
//    func = l1;
//
//    func(1, 5);
//
//    int x = 10;
//    auto l2 = [&a = x](double b, int y){std::cout << a + b + y << '\n';};
//
//    func = l2;
//    func(10, 10);
//
//    auto l3 = [](int a, int b){};
//
//    func = l3;
//    func(10, 10);


        //size_test
//      int ar[10];
//      std::cout << generic::size(ar);
//    Qualifiers generic tests
//    _____________________________________________________________________________________________________________________
//
//    add ref test
//        int x;
//        impl::generic::add_lvalue_ref_t<int> ref{x};
//        impl::generic::add_rvalue_ref_t<int> r_ref{5};
//        std::cout << impl::generic::is_same_v<int&, impl::generic::add_lvalue_ref_t<int>> << '\n';
//        std::cout << impl::generic::is_same_v<int&&, impl::generic::add_rvalue_ref_t<int>> << '\n';
//        std::cout << impl::generic::is_same_v<int&, impl::generic::add_rvalue_ref_t<int>> << '\n';
//
//    is_same test
//        std::cout << impl::generic::is_same_v<int,int&> << '\n';
//        std::cout << impl::generic::is_same_v<int,int> << '\n';
//        std::cout << impl::generic::is_same_v<int,impl::generic::remove_ref_t<int&&>> << '\n';
//
//        remove_ref_tests
//        std::cout << impl::generic::is_same_v<int, impl::generic::remove_ref_t<int&>> << '\n';
//        std::cout << impl::generic::is_same_v<int, impl::generic::remove_ref_t<int&&>> << '\n';
//
//        add/remove_c/v test
//        std::cout << std::is_same_v<impl::generic::remove_const_t<const int>, int> << '\n';
//        std::cout << std::is_same_v<impl::generic::add_const_t<int>, const int> << '\n';
//        std::cout << is_same_v<const int, remove_ref_t<const int&&>> << '\n';
//
//        std::cout << is_same_v<int&, remove_const_t<const int&>> << '\n';
//        !!!
//        here we have int& lhs and const int& rhs. const applied to type, not to ref, and our func discard ref qualifier
//
//
//         std::cout << is_same_v<int* const, add_const_t<int*>> << '\n';
//        std::cout << is_same_v<const int&, add_lvalue_ref_t<add_const_t<int>>> << '\n';
//
//        std::cout << is_same_v<const int&, remove_volatile_t<const volatile int&>> << '\n';
//        !!!
//        this test fails cause we should differ volatile int& and int& volatile, second is forbidden btw similar to ref test shit btw
//
//        std::cout << is_same_v<const int, remove_volatile_t<const volatile int>> << '\n';
//        std::cout << is_same_v<const volatile int, add_volatile_t<const int>> << '\n';
//
//    to_pointer_test
//    std::cout << is_same_v<int*, to_pointer_t<int[10]>> << '\n';
//    std::cout << is_same_v<int*, to_pointer_t<int[]>> << '\n';
//    std::cout << is_same_v<int, to_pointer_t<int>> << '\n';
//
//    decay test
//     std::cout << is_same_v<int, decay_t<const volatile int&>> << '\n';
//     std::cout << is_same_v<int*, decay_t<int[10]>> << '\n';
//
//    is_ref test
//     std::cout << is_lvalue_ref_t<int&> << '\n';
//     std::cout << is_rvalue_ref_v<int&&> << '\n';
//     std::cout << is_rvalue_ref_v<int&> << '\n';
//     std::cout << is_ref_v<int&> << '\n';
//     std::cout << is_ref_v<int> << '\n';
//______________________________________________________________________________________________________________________
//
//    array size test
//    std::cout << is_known_size_array_v<int[2]> << '\n';
//    std::cout << is_known_size_array_v<int[]> << '\n';
//
//......................................................................................................................
//
//    has_first test
//
//    std::cout << has_first_v<std::pair<int,int>> << '\n';
//    std::cout << has_first_v<noDefCtorWithMemberFirst> << '\n';
//    std::cout << has_first_v<std::vector<int>> << '\n';
//
//
//    has_size_type test
//    std::cout << has_size_type<std::vector<int>>::value << '\n';
//    std::cout << has_size_type_v<int> << '\n';
//
//!!! depend on impl
//    std::cout << has_size_type_v<std::vector<int>&> << '\n';
//
//    is_default_constructable test
//    std::cout << is_default_constructable_v<int> << '\n';
//    std::cout << is_default_constructable_v<int&> << '\n';
//    std::cout << is_default_constructable_v<impl::test::noDefCtor> << '\n';
//
//
//is_convertible test
//    std::cout << is_convertible_v<int, char> << '\n';
//    std::cout << is_convertible_v<int, long> << '\n';
//    std::cout << is_convertible_v<int, noDefCtor> << '\n';
//    std::cout << is_convertible_v<const int&, int> << '\n';
//    std::cout << is_convertible_v<noDefCtor, noDefCtorWithMemberFirst> << '\n';
//

//conditiontal test
    //std::cout << is_same_v<int, conditional_t<is_lvalue_ref_t<int&>, int, int&&>> << '\n';
    //std::cout << is_same_v<int&&, conditional_t<is_lvalue_ref_t<int&&>, int, int&&>> << '\n';
//
//create_from_index test
//    std::vector v{1,2,3,4,5};
//    for(const auto& elem : create_from_indexes<int, 1,2,3,4,0>(v)){
//        std::cout << elem << '\n';
//    }
//
//enable_if test
//    impl::test::enable_if_test::test<std::vector<int>>();
//    impl::test::enable_if_test::test<int>();
//    impl::test::substitution_failure_without_size_type<std::vector<int>> works;
//    impl::test::substitution_failure_without_size_type<int> failure;
//
//

//object_count test
//    someData<int> someData1;
//    std::cout << someData<int>::alive() << '\n';
//    someData<int> someData2;
//    someData<char> someData3;
//    std::cout << someData<int>::alive() << '\n';
//    std::cout << someData<double>::alive() << '\n';
//    auto someData4 = std::move(someData1);
//    std::cout << someData<int>::alive() << '\n';
//    someData4.~someData();
//    std::cout << someData<int>::alive() << '\n';
//

//equality_comparable CRTP test
    //impl::test::equality_comparable_test t1, t2;
    //std::cout << (t1 == t2) << '\n;

//move tests
    //test::log log1, log2;
    //log1 = log2;
    //log1 = move(log2);
    //test::log log3{move(log1)};
    //test::log log4{log3};
//
    //std::cout << traits::is_same_v<decltype(move(log4)), test::log&&> << '\n';
    //std::cout << traits::is_same_v<decltype(move(test::log{})), test::log&&> << '\n';
    //std::cout << traits::is_same_v<decltype(move(move(log4))), test::log&&> << '\n';

    return 0;
}