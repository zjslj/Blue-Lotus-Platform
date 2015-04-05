#ifndef BLP_BASE_SCOPED_PTR_H
#define BLP_BASE_SCOPED_PTR_H
#include "Config.h"
#include <assert.h>
#include <cstddef>


namespace blp{

/**
 * 本文件实现了以下两个智能指针类
 */
template <class T> class CScopedPtr;
template <class T> class CScopedArray;

template <class T>
class CScopedPtr
{
public:
    typedef T element_type;

    explicit CScopedPtr(T* p = NULL)
        : _ptr(p)
    {
    }

    ~CScopedPtr()
    {
        enum { type_must_be_complete = sizeof(T) };

        delete _ptr;
        _ptr = reinterpret_cast<T*>(-1);
    }

    bool operator !() const
    {
        return NULL == _ptr;
    }

    void reset(T* p = NULL)
    {
        if (p != _ptr)
        {
            enum { type_must_be_complete = sizeof(T) };

            delete _ptr;
            _ptr = p;
        }
    }

    T& operator *() const
    {
        assert(_ptr != NULL);
        return *_ptr;
    }

    T* operator ->() const
    {
        assert(_ptr != NULL);
        return _ptr;
    }

    T* get() const
    {
        return _ptr;
    }

    bool operator ==(T* p) const
    {
        return _ptr == p;
    }

    bool operator !=(T* p) const
    {
        return _ptr != p;
    }

    void swap(CScopedPtr& p2)
    {
        T* tmp = _ptr;
        _ptr = p2._ptr;
        p2._ptr = tmp;
    }

    T* release()
    {
        T* retVal = _ptr;
        _ptr = NULL;

        return retVal;
    }

private:
    CScopedPtr(const CScopedPtr&);
    CScopedPtr& operator =(const CScopedPtr&);
    template <class T2> bool operator ==(CScopedPtr<T2> const& p2) const;
    template <class T2> bool operator !=(CScopedPtr<T2> const& p2) const;

private:
    T* _ptr;
};

/***
 * 面向对象数组或数组变量的智能指针
 */
template <class T>
class CScopedArray
{
public:
    typedef T element_type;

    explicit CScopedArray(T* p = NULL)
        : _array(p)
    {
    }

    ~CScopedArray()
    {
        enum { type_must_be_complete = sizeof(T) };

        delete[] _array;
        _array = reinterpret_cast<T*>(-1);
    }

    bool operator !() const
    {
        return NULL == _array;
    }

    void reset(T* p = NULL)
    {
        if (p != _array)
        {
            enum { type_must_be_complete = sizeof(T) };

            delete[] _array;
            _array = p;
        }
    }

    T& operator [](std::ptrdiff_t i) const
    {
        assert(i >= 0);
        assert(_array != NULL);

        return _array[i];
    }

    T* get() const
    {
        return _array;
    }

    bool operator==(T* p) const { return _array == p; }
    bool operator!=(T* p) const { return _array != p; }

    void swap(CScopedArray& p2)
    {
        T* tmp = _array;
        _array = p2._array;
        p2._array = tmp;
    }

    T* release()
    {
        T* retVal = _array;
        _array = NULL;

        return retVal;
    }

private:
    CScopedArray(const CScopedArray&);
    CScopedArray& operator=(const CScopedArray&);
    template <class T2> bool operator ==(CScopedArray<T2> const& p2) const;
    template <class T2> bool operator !=(CScopedArray<T2> const& p2) const;

private:
    T* _array;
};

}
#endif
