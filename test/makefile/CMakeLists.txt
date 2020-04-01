cmake_minimum_required(VERSION 3.10)
project(find_use)
set(CMAKE_CXX_STANDARD 11)

include_directories(
        ${PROJECT_SOURCE_DIR}

        $ENV{HLA_PATH}/include
        $ENV{CLOUD_PATH}/include
)
link_directories(
        $ENV{HLA_PATH}/lib
        $ENV{CLOUD_PATH}/lib
)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_subdirectory(make_file)