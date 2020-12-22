cmake_minimum_required(VERSION 3.12)

project(
    base_codec VERSION 0.0.0
    DESCRIPTION "Library with base16/32/64 encoding/decoding routines"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(STATIC_LIBRARY_TARGET base_codec_static)
set(SHARED_LIBRARY_TARGET base_codec_shared)

set(
    LIBRARY_PUBLIC_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/base_codec/base16.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/base_codec/base32.hpp
)
set(LIBRARY_PRIVATE_HEADERS)
set(
    LIBRARY_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/base16.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/base32.cpp
)

add_library(
    ${STATIC_LIBRARY_TARGET} STATIC ${LIBRARY_PUBLIC_HEADERS}
    ${LIBRARY_PRIVATE_HEADERS}
    ${LIBRARY_SOURCES}
)
target_include_directories(${STATIC_LIBRARY_TARGET} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
add_library(${PROJECT_NAME}::${STATIC_LIBRARY_TARGET} ALIAS ${STATIC_LIBRARY_TARGET})

add_library(
    ${SHARED_LIBRARY_TARGET} SHARED ${LIBRARY_PUBLIC_HEADERS}
    ${LIBRARY_PRIVATE_HEADERS}
    ${LIBRARY_SOURCES}
)
target_include_directories(${SHARED_LIBRARY_TARGET} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
add_library(${PROJECT_NAME}::${SHARED_LIBRARY_TARGET} ALIAS ${SHARED_LIBRARY_TARGET})

option(BASE_CODEC_ENABLE_TESTS "Built the base_codec library tests" OFF)

if(BASE_CODEC_ENABLE_TESTS)
    find_package(Catch2 REQUIRED)
    enable_testing()

    set(TEST_MAIN base_codec_test_main)
    set(TEST_EXECUTOR base_codec_test_executor)

    add_library(${TEST_MAIN} STATIC ${CMAKE_CURRENT_LIST_DIR}/tests/test_main.cpp)
    target_link_libraries(${TEST_MAIN} PUBLIC Catch2::Catch2)

    add_executable(${TEST_EXECUTOR} ${CMAKE_CURRENT_LIST_DIR}/tests/base_codec_test.cpp)
    target_link_libraries(${TEST_EXECUTOR} PRIVATE
        ${TEST_MAIN}
        ${PROJECT_NAME}::${STATIC_LIBRARY_TARGET}
    )

    include(CTest)
    include(Catch)
    catch_discover_tests(${TEST_EXECUTOR})
endif()

message(WARNING "The author of this library is currently looking for a job - contact at rosengeorgiev93 at gmail dot com")
