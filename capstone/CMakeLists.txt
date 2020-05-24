cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(COVID_tracker)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
find_package(Python 2.7 REQUIRED)
find_package(PythonLibs REQUIRED)
find_package (Python2 COMPONENTS Interpreter Development NumPy)

set(CPP_HTTPLIB_DIR "../cpp-httplib")
set(MATPLOTLIB_CPP_DIR "../matplotlib-cpp")
set(PYTHON_DIR "/usr/include/python2.7")

include_directories(${CPP_HTTPLIB_DIR} ${MATPLOTLIB_CPP_DIR} ${PYTHON_DIR})

file(GLOB project_SRCS src/*.cpp)

add_executable(covid-tracker ${project_SRCS})
target_link_libraries(covid-tracker OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(covid-tracker ${CMAKE_DL_LIBS})
target_link_libraries(covid-tracker Python2::Python Python2::NumPy)
