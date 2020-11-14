/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <string>
#include <boost/test/unit_test.hpp>
#include "sdk/utils/varlock.hpp"

using namespace sdkutils;

BOOST_AUTO_TEST_CASE(varlock) {
    VarLock<std::string> str_lock;
    str_lock = "test";
    str_lock.unlock();
    BOOST_CHECK_EQUAL(str_lock->length(), 4);
}