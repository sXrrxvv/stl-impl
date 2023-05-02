#ifndef IMPLEMENTING_STL_FUNCTION_H
#define IMPLEMENTING_STL_FUNCTION_H

#include "../utility/utility.h"
#include "../traits/sfinae_traits.h"

namespace impl::generic {

    template <typename ReturnType, typename... Args>
    class function_base{

    public:

        virtual ~function_base() = default;

        virtual ReturnType invoke(Args... args) const = 0;

    };


    template <typename Functor, typename ReturnType, typename... Args>
    class function_erasure : public function_base<ReturnType, Args...>{

    private:
        Functor functor;

        ReturnType invoke(Args... args) const override{
            return functor(impl::forward<Args>(args)...);
        }

        ~function_erasure() override = default;

    public:

        template <typename Functor_>
        function_erasure (Functor_&& functor_) : functor{functor_} {};

    };

    template <typename... Args>
    class function;

    template<typename ReturnType, typename... ArgsType>
    class function<ReturnType(ArgsType...)> {

    private:

         function_base<ReturnType, ArgsType...>* func;

    public:

        function() : func{nullptr} {};

        template <typename Functor>
        function(Functor&& functor) : func{new function_erasure<traits::decay_t<Functor>, ReturnType, ArgsType...>{functor}} {};

        template<typename Functor>
        function& operator = (Functor&& functor){
            delete func;
            function f_new{impl::forward<Functor>(functor)};
            swap(*this, f_new);
            return *this;
        }

        ReturnType operator()(ArgsType... args) const{
            func->invoke(impl::forward<ArgsType>(args)...);
        }

        friend void swap(function& f1, function& f2){
            auto tmp = f1.func;
            f1.func = f2.func;
            f2.func = tmp;
        }
    };
    
}

#endif
