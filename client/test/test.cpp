/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <array>

BOOST_AUTO_TEST_CASE(test) {
    BOOST_CHECK_EQUAL("hello world", "hello world");
    BOOST_CHECK_NE("hello world", "hallo worl");
}

//
//BOOST_AUTO_TEST_CASE(test_helloword) {
//    BOOST_CHECK_EQUAL(ret_helloworld(), "hello world");
//    BOOST_CHECK_NE(ret_helloworld(), "hallo worl");
//}
//
//BOOST_AUTO_TEST_CASE(test_equal) {
//    BOOST_CHECK_EQUAL(1, 1);
//    BOOST_CHECK_EQUAL("hello", "hello");
//    BOOST_CHECK_EQUAL(1.04f, 1.04f);
//    BOOST_CHECK_EQUAL(23.1, 23.1);
//
//    BOOST_WARN_EQUAL(1.04f, 1.04f);
//    BOOST_REQUIRE_EQUAL(23.1, 23.1);
//}
//
//BOOST_AUTO_TEST_CASE(test_equal_container) {
//    std::vector<double> vector_a = {0.0, 0.1, 0.2, 0.3};
//    std::list<double> list_a = {0.0, 0.1, 0.2, 0.3, 0.4};
//    std::array<double, 3> array_a = {{0.0, 0.3, 0.6}};
//
//    BOOST_CHECK_EQUAL_COLLECTIONS(vector_a.begin(), vector_a.end(), vector_a.begin(), vector_a.end());
//    BOOST_CHECK_EQUAL_COLLECTIONS(list_a.begin(), list_a.end(), list_a.begin(), list_a.end());
//    BOOST_CHECK_EQUAL_COLLECTIONS(array_a.begin(), array_a.end(), array_a.begin(), array_a.end());
//}
//
//BOOST_AUTO_TEST_CASE(test_close) {
//    BOOST_CHECK_CLOSE_FRACTION(1.0001, 1.0, 1E-3);
//    BOOST_CHECK_CLOSE_FRACTION(3.32f, 3.33f, 1E-2f);
//
//    // 0.01 -> 0.01%
//    BOOST_CHECK_CLOSE(1.0001, 1.0000, 0.01);
//    BOOST_CHECK_CLOSE(3.32f, 3.33f, 0.31);
//}
//
//BOOST_AUTO_TEST_CASE(test_negated_equal) {
//    BOOST_CHECK_NE(1, 0);
//    BOOST_CHECK_NE("hello", "hallo");
//    BOOST_CHECK_NE(1.04f, 1.03f);
//    BOOST_CHECK_NE(23.1, 23.3);
//
//    BOOST_WARN_NE(1.04f, 1.03f);
//    BOOST_REQUIRE_NE(23.1, 23.3);
//}