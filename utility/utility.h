#ifndef IMPLEMENTING_STL_UTILITY_H
#define IMPLEMENTING_STL_UTILITY_H
#include "../traits/qualifiers_traits.h"

namespace impl{

    template<typename... Args>
    using void_t = void;

    template <typename T>
    constexpr impl::traits::add_rvalue_ref_t<T> declval() noexcept;
}
#endif //IMPLEMENTING_STL_UTILITY_H
