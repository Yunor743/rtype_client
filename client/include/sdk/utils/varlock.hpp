/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_UTILS_VARLOCK_HPP_
#define _SDK_UTILS_VARLOCK_HPP_

#include <iostream>

namespace sdkutils {
    template<typename T>
    class VarLock {
        bool islock = false;
        T data;
    public:
        [[nodiscard]] T& value()
        {
            return data;
        }
        VarLock & unlock()
        {
            islock = false;
            return *this;
        }
        VarLock & lock()
        {
            islock = true;
            return *this;
        }

        VarLock &operator=(const VarLock &other) {
            if (!islock) {
                data = other.data;
                islock = true;
            }
            return *this;
        }

        VarLock &operator=(const T &other)
        {
            if (!islock) {
                data = other;
                islock = true;
            }
            return *this;
        }

        explicit operator bool() const
        {
            return !islock;
        }

        T *operator->()
        {
            T *ret = nullptr;
            if (!islock) {
                islock = true;
                ret = &data;
            }
            if (ret == nullptr)
                std::cerr << "Varlock : operator-> return nullptr" << std::endl;
            return ret;
        }
    };

}

#endif