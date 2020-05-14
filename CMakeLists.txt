cmake_minimum_required(VERSION 3.17)
project(redcap-api-cpp-example)
include(FindCURL)
add_executable(redcap-api-cpp-example main.cpp)
target_compile_options(redcap-api-cpp-example
                       PRIVATE ${REDCAP_API_CPP_EXAMPLE_WARNINGS})
target_link_libraries(redcap-api-cpp-example PRIVATE CURL::libcurl)
