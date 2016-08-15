/*
 * myvector.h
 * Copyright (C) 2016 blueyi <blueyi@blueyi-lubuntu>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <memory>

template <typename T> class myvector {
public:
    myvector();
    myvector(const myvector &rhs);
    myvector(const T *arr);
    myvector& operator=(const myvector &rhs);
    T& operator[](std::size_t n);
    const T& operator[](std::size_t n) const;
    ~myvector();

private:
    T *p_data;
    std::size_t max_index;
    void check(std::size_t i, const std::string &msg) const;
};

template <typename T> myvector<T>::myvector()
{
    p_data = nullptr;
}

#endif /* !MYVECTOR_H */
