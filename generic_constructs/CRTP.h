#ifndef IMPLEMENTING_STL_CRTP_H
#define IMPLEMENTING_STL_CRTP_H

//we can customize behaviour to the derived class via specialization

namespace impl::generic {
    template<typename Derived>
    class objectCounter {
    private:
        inline static unsigned int count = 0;

    protected:
        objectCounter() {
            ++count;
        }

        objectCounter(const objectCounter &) {
            ++count;
        }

        objectCounter(objectCounter &&) noexcept = default;

        ~objectCounter() {
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
