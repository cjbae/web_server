cmake_minimum_required(VERSION 2.8)
project(test_test)

add_compile_options(-std=c++17 -O0)

link_directories(${LIBRARY_BOOST_DIR})

file(GLOB_RECURSE headers "*.h")
file(GLOB_RECURSE sources "*.cpp")

add_executable(server8 ${sources} ${headers})

target_link_libraries(server8 pthread boost_system boost_filesystem boost_chrono boost_thread)

