set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    # Boost static link fix
    add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
    add_compile_options(
            $<$<CONFIG:>:/MD> #---------|
            $<$<CONFIG:Debug>:/MD> #----|-- Statically link the runtime libraries (boost fix)
            $<$<CONFIG:Release>:/MD> #--|
    )
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()

link_directories(${CMAKE_BINARY_DIR}/bin)

add_executable(r-type_client ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_library(r-type_client_sdk STATIC)
add_library(r-type_client_app STATIC)

target_include_directories(r-type_client PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
target_include_directories(r-type_client_sdk PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(r-type_client_app PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(r-type_client_sdk PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/interfaces/Iview.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/interfaces/Ifragment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/interfaces/Icolors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/interfaces/Istring.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/interfaces/Iwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/managers/event.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/managers/inputs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/widgets/image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/widgets/loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/widgets/text.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/widgets/text_entry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/widgets/button_text.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/widgets/button_image.cpp
)

target_sources(r-type_client_app PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/res/colors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/res/strings/common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/res/strings/fr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/res/strings/en.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/views/home/home.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/views/loading/loading.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/views/home/fragments/topbar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/views/home/fragments/bottombar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/views/home/fragments/game.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/views/home/widgets/console.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/network/client.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/network/tcpsockmngr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/network/udpsockmngr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/network/protocol.cpp
)

conan_target_link_libraries(r-type_client_sdk)
conan_target_link_libraries(r-type_client_app)

target_link_libraries(r-type_client_app
        r-type_client_sdk
)

target_link_libraries(r-type_client
        r-type_client_app
)

# Linking assets client folder
if (WIN32)
    add_custom_command(TARGET r-type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
else()
    ADD_CUSTOM_TARGET(assets ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
endif()

# Warning handling
set(MSVC_FLAGS /w)
set(GCC_FLAGS -Wall -Wextra -pedantic -Werror)

if(MSVC)
    target_compile_options(r-type_client PRIVATE ${MSVC_FLAGS})
else()
    target_compile_options(r-type_client PRIVATE ${GCC_FLAGS})
endif()
target_compile_definitions(r-type_client_app PUBLIC BOOST_BIND_GLOBAL_PLACEHOLDERS=1)

# Unit Tests
add_subdirectory(test)
