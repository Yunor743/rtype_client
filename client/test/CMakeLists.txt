set(Boost_USE_STATIC_LIBS OFF)

add_executable(Client_Units_Tests)

target_sources (Client_Units_Tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/varlock_test.cpp
        )

target_link_libraries(Client_Units_Tests
        r-type_client_app
        r-type_client_sdk
        )

# target_link_libraries(Client_Units_Tests ${CONAN_LIBS_BOOST})
conan_target_link_libraries(Client_Units_Tests)