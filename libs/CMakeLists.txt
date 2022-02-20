# 프로젝트의 서브모듈 입니다.
set( sub_modules )

# 외부 모듈은 추가는 여기서 진행하십시오
add_subdirectory( ../../sano_game_global build/libs/sano_game_global )

list(APPEND sub_modules sano_game_global)

set( module_public_dep_list ${module_private_dep_list} ${sub_modules} PARENT_SCOPE)
