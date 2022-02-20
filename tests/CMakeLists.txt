# 테스트 라이브러리를 빌드 및 실행합니다.
find_package( GTest REQUIRED)
if ( NOT ${GTest_FOUND} )
    message( FATAL_ERROR "테스트 를 진행하기 위해서는 Google_test가 필요합니다." )
endif()

# 파일을 찾고 테스트 라이브러리를 링크 시킵니다. 
file( GLOB TEST_LISTS "*.cpp" )
foreach( ITEM ${TEST_LISTS} )
    get_filename_component( TEST_NAME ${ITEM} NAME_WE )
    set( TEST_NAME "${PROJECT_NAME}_${TEST_NAME}_test" ) #이름이 중복되지 않습니다.
    add_executable( ${TEST_NAME} ${ITEM} )
    # ! 해당 Target 이 lib 가 아닐 경우 링크할 수 없습니다.
    target_link_libraries( ${TEST_NAME} PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main )
    add_test( ${TEST_NAME} ${TEST_NAME} )
endforeach( ITEM ${TEST_LISTS} )
