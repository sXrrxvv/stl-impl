#ifndef IMPLEMENTING_STL_TAG_DISPATCHER_H
#define IMPLEMENTING_STL_TAG_DISPATCHER_H

#include <iterator>
#include <iostream>

namespace impl{

    template <typename... Tags>
    struct tag_dispatcher_helper{
        static void match(...);
    };

    template <>
    struct tag_dispatcher_helper<>{
        static void match();
    };

    template <typename Tag1, typename... Tags>
    struct tag_dispatcher_helper<Tag1, Tags...> : tag_dispatcher_helper<Tags...>{
        static Tag1 match(Tag1);

        using tag_dispatcher_helper<Tags...>::match;
    };

    template <typename T, typename... Types>
    struct tag_dispatcher{
        using tag = decltype(tag_dispatcher_helper<T, Types...>::match(declval<T>()));
    };

    template <typename T, typename... Tags>
    using tag_dispatcher_t = typename tag_dispatcher<T, Tags...>::tag;

}
#endif //IMPLEMENTING_STL_TAG_DISPATCHER_H
