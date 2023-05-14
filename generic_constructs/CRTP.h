#ifndef IMPLEMENTING_STL_CRTP_H
#define IMPLEMENTING_STL_CRTP_H

//we can customize behaviour to the derived class via specialization

//TODO: add enable_share_from_this when shared_ptr is ready
namespace impl::generic {
    template<typename Derived>
    class object_counter {
    private:
        inline static unsigned int count = 0;

    protected:
        object_counter() {
            ++count;
        }

        object_counter(const object_counter &) {
            ++count;
        }

        object_counter(object_counter &&) noexcept = default;

        ~object_counter() {
            --count;
        }

    public:
        static unsigned int alive() { return count; }
    };
}

template <typename Derived>
class equality_comparable{
    friend bool operator == (const Derived& lhs, const Derived& rhs){
        return !(lhs != rhs);
    }
};
#endif //IMPLEMENTING_STL_CRTP_H
