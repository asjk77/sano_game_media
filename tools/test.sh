# 테스트를 진행합니다. 주의 오직 프로젝트의 root 디렉토리에서 실행해야 합니다.
 
function handle_error() {
    echo ${1}
    exit -1
}

if [ ! -d ".git" ]; then
    handle_error "오직 프로젝트 루트 디렉토리에서 실행 해야 합니다."
fi

cd build && ctest 
