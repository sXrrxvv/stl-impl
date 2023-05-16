#ifndef IMPLEMENTING_STL_TUPLE_H
#define IMPLEMENTING_STL_TUPLE_H

//TODO : get<N>,make_tuple and tie

namespace impl::generic {

    template <unsigned int Index, typename T,
            bool can_inherit_from = traits::is_class_v<T> && !std::is_final_v<T>> //is_final implemented via compiler support
    class tuple_elem;

    template <unsigned int Index, typename T>
    class tuple_elem<Index, T, false>{

    private:
        T val;

    public:

        tuple_elem(const T& val) : val(val) {};

        tuple_elem(T&& val) noexcept : val(move(val)) {};

        T& get_val() &{
            return val;
        }

        const T& get_val() const &{
            return val;
        }
    };

    template <unsigned int Index, typename T>
    class tuple_elem<Index, T, true> : private T{
    public:

        tuple_elem(const T& val){
            static_cast<T&>(*this) = val;
        };

        tuple_elem(T&& val) noexcept {
            static_cast<T&>(*this) = move(val);
        };

        T& get_val() &{
            return *this;
        }

        const T& get_val() const &{
            return *this;
        }
    };

    template <typename... Types>
    class tuple;

    template <typename FirstType, typename...  OtherTypes>
    class tuple<FirstType, OtherTypes...> : private tuple_elem<sizeof...(OtherTypes), FirstType>, tuple<OtherTypes...>{

        //make private after tests
    public:

        using tail = tuple<OtherTypes...>;
        using head = tuple_elem<sizeof...(OtherTypes), FirstType>;

        tail& get_tail(){
            return *this;
        }

        const tail& get_tail() const{
            return *this;
        }

        head& get_head(){
            return *this;
        }

        const head& get_head() const{
            return *this;
        }

    public:

        tuple() = default;

        tuple(const tuple& rhs) : head(rhs.get_head()), tail(rhs.get_tail()) {};

        tuple(tuple&& rhs) noexcept : head(move(rhs.get_head())), tail(move(rhs.get_tail())) {};

        template <typename FwdFirstType, typename... FwdOtherTypes,
                typename = enable_if_t<sizeof...(OtherTypes) == sizeof...(FwdOtherTypes), void>>
        tuple(FwdFirstType&& first, FwdOtherTypes&&... other) :
        head(forward<FwdFirstType>(first)), tail(forward<FwdOtherTypes>(other)...) {};

        tuple& operator = (tuple&& rhs) noexcept{
            this->get_head() = move(rhs.get_head());
            this->get_tail() = move(rhs.get_tail());
            return *this;
        }

        tuple& operator = (const tuple& rhs){
            tuple tmp{rhs};
            swap(*this, tmp);
            return *this;
        }

        friend void swap(tuple& first, tuple& second) {
            tuple tmp{move(first)};
            first = move(second);
            second = move(tmp);
        }
    };

    template <>
    class tuple<>{};



}



#endif //IMPLEMENTING_STL_TUPLE_H
