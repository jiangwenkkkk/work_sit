add_executable(test_graph test_graph.cpp)

find_package(Boost REQUIRED COMPONENTS graph)

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(test_graph ${Boost_LIBRARIES})
