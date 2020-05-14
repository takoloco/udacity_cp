cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)
project(COVID_tracker)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

set(CPP_HTTPLIB_DIR "../cpp-httplib")

include_directories(${CPP_HTTPLIB_DIR})

file(GLOB project_SRCS src/*.cpp)

add_executable(covid-tracker ${project_SRCS})
target_link_libraries(covid-tracker OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(covid-tracker ${CMAKE_DL_LIBS})