cmake_minimum_required(VERSION 3.10)
project(find_use)
set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/mysql/include)
link_directories(/usr/local/mysql/lib
        )



add_executable(find_use find_use.cpp)
add_executable(test_mysql test_mysql.cpp)
add_executable(change_num_to_prince change_num_to_prince.cpp)
target_link_libraries(test_mysql libmysqlclient.a )

add_executable(mysql_demo MySqlDemo.cpp MySqlQuery.cpp MySqlQuery.h)
target_link_libraries(mysql_demo libmysqlclient.a)

add_executable(get_all get_all.cpp)



add_executable(test_all
        test_all.cpp
        find_data.cpp
        find_data.h)

target_link_libraries(test_all libgtest.a libgtest_main.a)


add_executable(query_show
        query_show.cpp
        MySqlQuery.h
        MySqlQuery.cpp
        find_data.cpp
        find_data.h
        )
target_link_libraries(query_show libmysqlclient.a)

add_executable(check_num check_num.cpp MySqlQuery.cpp MySqlQuery.h)
target_link_libraries(check_num libmysqlclient.a)

add_executable(regex_check_num regex_check_num.cpp MySqlQuery.cpp MySqlQuery.h)
target_link_libraries(regex_check_num libmysqlclient.a)


add_executable(mut_check_num mut_check_num.cpp MySqlQuery.cpp MySqlQuery.h)
target_link_libraries(mut_check_num libmysqlclient.a)

find_package(Boost COMPONENTS thread system REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(mut_check_num ${Boost_LIBRARIES})



add_executable(single_db single_db.cpp MySqlQuery.cpp MySqlQuery.h)
target_link_libraries(single_db libmysqlclient.a)




#add_subdirectory(inspect)
add_subdirectory(test)
#add_subdirectory(graph)
add_subdirectory(sh)