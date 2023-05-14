#ifndef IMPLEMENTING_STL_TUPLE_H
#define IMPLEMENTING_STL_TUPLE_H

//TODO : get<N>, make_tuple and tie

namespace impl::generic {

    template <typename... Types>
    class tuple;


    //bad tuple design, because of recursive inheritance. Need to rewrite it in future
    template<typename FirstType, typename... OtherTypes>
    class tuple<FirstType, OtherTypes...> : private tuple<OtherTypes...> {

    public:
        FirstType val;

        tuple<OtherTypes...>& get_tail() {
            return static_cast<tuple<OtherTypes...>&>(*this);
        }

        const tuple<OtherTypes...>& get_tail() const {
            return static_cast<const tuple<OtherTypes...>&>(*this);
        }

    public:

        tuple() = default;

        //need to disable when we're constructing from existing tuple, because Fwd c-tor can be a better match than copy/move
        template <typename FwdFirstType, typename... FwdOtherTypes,
                typename = enable_if_t<sizeof...(FwdOtherTypes) == sizeof...(OtherTypes), void>>
        tuple(FwdFirstType&& first_val, FwdOtherTypes&&... other_types) : val{forward<FwdFirstType>(first_val)},
                tuple<OtherTypes...>{forward<FwdOtherTypes>(other_types)...} {};

        tuple(const tuple& rhs) : val(rhs.val), tuple<OtherTypes...>(rhs.get_tail()) {};

        tuple(tuple&& rhs) noexcept : val(move(rhs.val)), tuple<OtherTypes...>(move(rhs.get_tail())) {};

        tuple& operator = (const tuple& rhs){
            tuple tmp(rhs);
            swap(*this, tmp);
            return *this;
        }

        tuple& operator = (tuple&& rhs) noexcept{
            val = move(rhs.val);
            static_cast<tuple<OtherTypes...>&>(*this) = move(rhs.get_tail());
            return *this;
        }

        friend constexpr void swap(tuple& lhs, tuple& rhs){
            tuple tmp = move(lhs);
            lhs = move(rhs);
            rhs = move(tmp);
        }

//        friend constexpr bool operator ==(const tuple& lhs, const tuple& rhs){
//
//        }

    };

    template <>
    class tuple<>{};

    template <typename FirstType, typename... OtherTypes>
    constexpr void print_tuple(const tuple<FirstType, OtherTypes...>& t){

    }
}



#endif //IMPLEMENTING_STL_TUPLE_H
