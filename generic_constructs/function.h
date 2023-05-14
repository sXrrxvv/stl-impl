#ifndef IMPLEMENTING_STL_FUNCTION_H
#define IMPLEMENTING_STL_FUNCTION_H

#include "../utility/utility.h"
#include "../traits/sfinae_traits.h"
#include "../traits/non_sfinae_check_traits.h"

//TODO : bind

namespace impl::generic {

    //for future bind func
    template <size_t N>
    struct placeholder{};

    constexpr placeholder<1> _1;
    constexpr placeholder<2> _2;
    constexpr placeholder<3> _3;


    template <typename ReturnType, typename... Args>
    class function_base{

    public:

        virtual ~function_base() = default;

        virtual ReturnType invoke(Args... args) const = 0;

        virtual function_base* clone() const = 0;

    };


    template <typename Functor, typename ReturnType, typename... Args>
    class function_erasure : public function_base<ReturnType, Args...>{

    private:
        Functor functor;

        ReturnType invoke(Args... args) const override{
            return functor(impl::forward<Args>(args)...);
        }

        function_erasure* clone() const override{
            return new function_erasure(functor);
        }

    public:

        template <typename Functor_>
        function_erasure (Functor_&& functor_) : functor{forward<Functor_>(functor_)} {};

    };

    template <typename... Args>
    class function;

    template<typename ReturnType, typename... ArgsType>
    class function<ReturnType(ArgsType...)> {

    private:

         function_base<ReturnType, ArgsType...>* func;

    public:

        function() : func{nullptr} {};

        template <typename Functor,
                typename = enable_if_t<!traits::is_same_v<traits::decay_t<Functor>, function>, void>>
        function(Functor&& functor) : func{new function_erasure<traits::decay_t<Functor>, ReturnType, ArgsType...>
                {impl::forward<Functor>(functor)}} {};

        function(const function& rhs) : func{nullptr} {
            if(rhs.func != nullptr) {
                func = rhs.func->clone();
            }
        };

        function(function&& rhs) noexcept : func{rhs.func} {
            rhs.func = nullptr;
        }

        template<typename Functor>
        function& operator = (Functor&& functor){
            delete func;
            function f_new{impl::forward<Functor>(functor)};
            swap(*this, f_new);
            return *this;
        }

        function& operator = (function&& rhs) noexcept{
            delete func;
            func = rhs.func;
            rhs.func = nullptr;
            return *this;
        }

        ReturnType operator()(ArgsType... args) const{
            func->invoke(impl::forward<ArgsType>(args)...);
        }

        friend void swap(function& f1, function& f2){
            impl::swap(f1, f2);
        }
    };
    
}

#endif //IMPLEMENTING_STL_FUNCTION_H
