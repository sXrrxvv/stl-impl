#ifndef IMPLEMENTING_STL_UTILITY_H
#define IMPLEMENTING_STL_UTILITY_H
#include "../traits/qualifiers_traits.h"

namespace impl{

    template<typename... Args>
    using void_t = void;

    template <typename T>
    constexpr impl::traits::add_rvalue_ref_t<T> declval() noexcept;


    //TODO : create move and forward

    template<typename T, size_t... Ind, template<typename> class Container>
    Container<T> create_from_indexes(const Container<T>& from){
        Container<T> created{};
        (created.emplace_back(from[Ind]),... );
        return created;
    }
}
#endif //IMPLEMENTING_STL_UTILITY_H
