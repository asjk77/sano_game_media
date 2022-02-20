file( GLOB EXAMPLE_LISTS "*.cpp" )
foreach( ITEM ${EXAMPLE_LISTS} )
    get_filename_component( EXAMPLE_NAME ${ITEM} NAME_WE )
    set( EXAMPLE_NAME "${PROJECT_NAME}_${EXAMPLE_NAME}_example" ) #이름이 중복되지 않습니다.
    add_executable( ${EXAMPLE_NAME} ${ITEM} )
    # ! 해당 Target 이 lib 가 아닐 경우 링크할 수 없습니다.
    target_link_libraries( ${EXAMPLE_NAME} PRIVATE ${PROJECT_NAME} )
endforeach( ITEM ${EXAMPLE_LISTS} )
