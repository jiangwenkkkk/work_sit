

add_executable(net net_t.cpp)
target_link_libraries(net gtest.a libgtest_main.a)

add_executable(test_execl test_execl.cpp)
target_link_libraries(test_execl gtest.a libgtest_main.a)

add_executable(test_host_ip test_host_ip.cpp)
add_executable(main2 main2.cpp)
add_executable(main10 main10.cpp)
add_executable(main11 main11.cpp)


add_executable(make_sh make_sh.cpp)
add_executable(another_make_sh another_make_sh.cpp)
add_executable(another_new_file_1 another_new_file_1.cpp)
add_executable(signal_test signal_test.cpp)
add_executable(test_root_uid test_root_uid.cpp)

add_executable(test_fork_dead test_fork_dead.cpp)
add_executable(test_time_out test_time_out.cpp)

add_subdirectory(jameswork)

add_executable(test_include test_include.cpp)

add_subdirectory(makefile)