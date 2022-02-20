# 프로젝트 빌드 스크립트 입니다.
cmake_minimum_required( VERSION 3.2.0 )

# 프로젝트 구성 파라메터 입니다.
set( module_name "sano_game_media" ) # 모듈 이름을 지정합니다.
set( module_pch_file_name "sano_game_media_pch.hpp" ) # pch 파일은 기본적으로 <project_dir>/src/ 안에 정의되어야 합니다.
set( module_type "SHARED" ) # 정적 라이브러일 경우 STATC을 입력하십시오.
option( build_tests "테스트를 빌드합니다." OFF ) # 테스트를 빌드하기 위해서는 ON으로 설정하십시오.
option( build_examples "예제를 빌드합니다." OFF ) # 예제를 빌드하기 위해서는 ON으로 설정합니다.
option( build_docs "문서를 빌드합니다." OFF ) # 문서를 빌드하기 위해서는 OFF 로 설정합니다.
option( show_log "변수 로그를 출력합니다." OFF ) # 변수로그를 출력하길 위해서는 ON으로 설정하십시오.
set( CMAKE_BUILD_TYPE Debug ) # 빌드 타입을 Debug로 설정합니다.

# 프로젝트 내부 파라메터입니다. 

project( ${module_name} )
set( module_include_dir "${PROJECT_SOURCE_DIR}/include" )
set( module_src_dir "${PROJECT_SOURCE_DIR}/src" )
set( module_examples_dir "${PROJECT_SOURCE_DIR}/examples")
file(GLOB_RECURSE module_source_list "${module_src_dir}/*.cpp" )

# 프로젝트를 구성합니다.
list( APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ) # cmake 위치를 추가합니다.

# 프로젝트 내부의 의존 라이브러리들을 로드 및 링크합니다.
set( module_private_dep_list ) # private 의존 라이브러리 입니다.
set( module_private_dep_list_inc ) # private 의존 라이브러리 입니다.

add_subdirectory(external)
add_subdirectory(libs)
add_subdirectory(extras)

message("---------------------")
message(STATUS ${module_private_dep_list})
message(STATUS ${module_private_dep_list_inc})
message("---------------------")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # compile_command.json을 사용합니다.

add_library( ${PROJECT_NAME} ${module_type} ${module_source_list} ) #
target_include_directories( ${PROJECT_NAME} PUBLIC ${module_include_dir} ) # include_dir을 추가합니다.
target_include_directories( ${PROJECT_NAME} PRIVATE ${module_private_dep_list_inc} ) # module_private_dep_list_inc include 
target_link_libraries( ${PROJECT_NAME} PUBLIC ${module_public_dep_list} ) # public_dep_list를 추가합니다.
target_link_libraries( ${PROJECT_NAME} PRIVATE ${module_private_dep_list} ) # private_dep_list를 추가합니다.
target_precompile_headers( ${PROJECT_NAME} PRIVATE "${module_src_dir}/${module_pch_file_name}" ) # PCH 위치를 지정합니다.
target_include_directories( ${PROJECT_NAME} PRIVATE ${module_src_dir} ) # PCH을 소스코드에서 쉽게 추가하기 위하여 include_directory를 추가합니다. 
target_compile_features( ${PROJECT_NAME} PUBLIC cxx_std_17 ) # 프로젝트는 CPP_17 을 지원한합니다.

add_compile_options( -Wsuggest-override )

if(${build_tests}) # 테스트를 빌드합니다.
    include(CTest)
    add_subdirectory(tests)
endif()

if(${build_examples}) # 예제를 빌드합니다.
    add_subdirectory(examples)
endif()

if(${build_docs}) # 문서를 빌드합니다.
    add_subdirectory(docs)
endif()

if (${show_log})
    message("module_name: ${module_name}")
    message("module_pch_file_name: ${module_pch_file_name}")
    message("module_type: ${module_type}")
    message("module_build_type: ${module_build_type}")
    message("module_include_dir: ${module_include_dir}")
    message("module_src_dir: ${module_src_dir}")
    message("module_source_list: ${module_source_list}")
    message("module_public_dep_list: ${module_public_dep_list}")
    message("module_private_dep_list: ${module_private_dep_list}")
endif()


