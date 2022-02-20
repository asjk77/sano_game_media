#!/bin/bash

# 오직 프로젝트 루트 디렉토리에서 실행해야 합니다.
# 사용법 sh ./build.sh [-t 테스트를 빌드] [-e 예제를 빌드] [-d 문서를 빌드]

function handle_usage() {
    echo "Usage: $0 [-t 테스트를 빌드] [-e 예제를 빌드] [-d 문서를 빌드]"
    exit -1;
}

function handle_error() {
    echo ${1}
    exit -1
}

if [ ! -d ".git" ]; then
    handle_error "오직 프로젝트 루트 디렉토리에서 실행 해야 합니다."
fi

BUILD_OPTIONS=()

while getopts "ted" opt;
do
    case ${opt} in
        t)
            BUILD_OPTIONS+=("-Dbuild_tests=ON")
            ;;
        e)
            BUILD_OPTIONS+=("-Dbuild_examples=ON")
            ;;
        d)
            BUILD_OPTIONS+=("-Dbuild_docs=ON")
            ;;
        *)
            handle_usage
    esac
done

[ -d "build" ] || mkdir build
cd build

cmake .. ${BUILD_OPTIONS[@]}
make
