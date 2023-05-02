#ifndef IMPLEMENTING_STL_TEST_OBJECTS_H
#define IMPLEMENTING_STL_TEST_OBJECTS_H
#include "../traits/sfinae_traits.h"
#include "../generic_constructs/type_constructs.h"
#include "../generic_constructs/CRTP.h"
#include "../generic_constructs/tag_dispatcher.h"

namespace impl::test{

    struct noDefCtor {
        noDefCtor() = delete;
    };

    struct noDefCtorWithMemberFirst : noDefCtor {
        int first;
    };

    struct enable_if_test {
        template<typename Container>
        generic::enable_if_t<traits::has_size_type_v<Container>, void>
                constexpr static test(){
            std::cout << "overload for types with ::size_type\n";
        }

        template<typename Container>
        generic::enable_if_t<!traits::has_size_type_v<Container>, void>
                constexpr static test(){
            std::cout << "overload for types without ::size_type\n";
        }
    };

    class log{
    public:
        log(){
            std::cout << "default ctor" <<'\n';
        }

        log(const log&){
            std::cout << "copy ctor" <<'\n';
        }

        log(log&&) noexcept{
            std::cout << "move ctor\n";
        }

        log& operator = (const log&){
            std::cout << "copy assignment\n";
            return *this;
        }

        log& operator = (log&&){
            std::cout << "move assignment\n";
            return *this;
        }
    };

    template <typename T>
    class CRTP_test : public generic::objectCounter<CRTP_test<T>>{};

    class equality_comparable_test : public equality_comparable<equality_comparable_test>{
        friend bool operator !=(const equality_comparable_test& lhs, const equality_comparable_test& rhs){
            return true;
        }
    };

    //TODO: read more about sfinae error, where instantiating applies and where it would be an error
    template <typename Container, typename = void>
    struct substitution_failure_without_size_type{};

    template <typename Container>
    struct substitution_failure_without_size_type<Container,
            typename generic::enable_if_t<traits::has_size_type_v<Container>, void>> {};

    template <typename Container>
    struct substitution_failure_without_size_type<Container,
            typename generic::enable_if_t<!traits::has_size_type_v<Container>, void>::type>{};

    template <typename Iter, typename tag = tag_dispatcher_t
            <typename std::iterator_traits<Iter>::iterator_category,
                    std::input_iterator_tag,
                    std::forward_iterator_tag,
                    std::bidirectional_iterator_tag,
                    std::random_access_iterator_tag>>
    struct tag_dispatcher_test;

    template <typename Iter>
    struct tag_dispatcher_test<Iter, std::input_iterator_tag>{
        static void f() {std::cout << 1;}
    };

    template <typename Iter>
    struct tag_dispatcher_test<Iter, std::forward_iterator_tag>{
        static void f() {std::cout << 2;}
    };

    template <typename Iter>
    struct tag_dispatcher_test<Iter, std::bidirectional_iterator_tag>{
        static void f() {std::cout << 3;}
    };

    template <typename Iter>
    struct tag_dispatcher_test<Iter, std::random_access_iterator_tag>{
        static void f() {std::cout << 4;}
    };

}
#endif //IMPLEMENTING_STL_TEST_OBJECTS_H
