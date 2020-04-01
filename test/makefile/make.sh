#!/bin/bash
if [ -f profile ]; then
    echo "使用个人自定义环境变量"
    source profile
else
    echo "ok"
    source profile_example
fi

LOCAL_INSTALL_PATH=`pwd`
SYS_INSTALL_PATH=/app/roam


remake_sys() {
    rm -rf ./build
    mkdir -p ./build
    mkdir -p ./bin

    cd ./build
    cmake -DCMAKE_INSTALL_PREFIX=${SYS_INSTALL_PATH} ..
    cd ..
}

remake_local() {
    rm -rf ./build
    mkdir -p ./build
    mkdir -p ./bin

    cd ./build
    cmake -DCMAKE_INSTALL_PREFIX=${LOCAL_INSTALL_PATH} ..
    cd ..
}

make_func() {
    mkdir -p ./build

    cd ./build
    make -j $1
    cd ..
}


make_install() {
    mkdir -p ./build

    cd ./build
    make install -j
    cd ..
}

print_usage() {
    echo "用法:
0: 编译
1：编译安装
local: 生成cmake编译文件, 安装到当前目录
sys: 生成cmake编译文件，安装到系统目录"
}

build() {
    for no in $@
    do
        case $no in
            -1)
                echo "编译"
                make_func
            ;;
            0)
                echo "编译"
                make_func 1
            ;;
            1)
                echo "编译安装"
                make_install
            ;;
            local)
                echo "重新构建cmake编译文件"
                remake_local
            ;;
            sys)
                echo "重新构建cmake编译文件"
                remake_sys
            ;;
            *)
                print_usage
            ;;
        esac
    done
}

build "$@"
