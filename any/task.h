#pragma once
#include <memory>

class Any {
public:
    Any()
        : _inner(nullptr)
        {}

    Any(const Any& src) 
        : _inner(src._inner->clone()) 
        {}
    
    Any(Any&& src) 
        : _inner(std::move(src)._inner->clone()) {
            src._inner = nullptr;
        }

    template <typename T> 
    Any(T src) 
        : _inner(new inner<T>(std::forward<T>(src))) 
        {}

    template <typename T> 
    Any& operator=(T src) {
        _inner = std::make_unique<inner<T>>(std::forward<T>(src));
        return *this;
    }

    Any& operator=(const Any& src) {
        Any oTmp(src);
        std::swap(oTmp._inner, this->_inner);
        return *this;
    }

    Any& operator=(Any&& src) {
        Any oTmp(src);
        std::swap(oTmp._inner, this->_inner);
        src._inner = nullptr;
        return *this;
    }

    const std::type_info& Type() const { 
        return _inner->Type(); 
    }
    bool Empty() {
        return _inner == nullptr;
    }
    size_t Size() const { 
        return _inner->Size(); 
    }
    
    void Reset() {
        _inner = nullptr;
    }
    void Swap(Any& other) {
        std::swap(this->_inner, other._inner);
    } 

    template <typename T> 
    T& Value() {
        return *dynamic_cast<inner<T>&>(*_inner);
    }

    template <typename T> 
    const T& Value() const {
        return *dynamic_cast<inner<T>&>(*_inner);
    }

    struct inner_base {
    public:
        using Pointer = std::unique_ptr<inner_base>;

        virtual inner_base* clone() const = 0;
        virtual const std::type_info& Type() const = 0;
        virtual size_t Size() const = 0;

        virtual ~inner_base() = default;
    };

    template <typename T> 
    struct inner : inner_base {
    private:
        T _value;
    
    public:
        inner(T newval) 
            : _value(std::move(newval)) 
            {}

        virtual inner_base* clone() const override { 
            return new inner(_value); 
        }
        virtual const std::type_info& Type() const override { 
            return typeid(T); 
        }
        T& operator*() { 
            return _value; 
        }
        const T& operator*() const { 
            return _value; 
        }
        virtual size_t Size() const { 
            return sizeof(T); 
        }
    };
private:
    inner_base::Pointer _inner;
};
