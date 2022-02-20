# 프로젝트의 부가적인 라이브러리 들 입니다.
set( extra_modules )

# 외부 모듈은 추가는 여기서 진행하십시오
# add_subdirectory(<someModule>)
# list(APPEND extra_modules <someModule>)


set( module_private_dep_list ${module_private_dep_list} ${extra_modules} PARENT_SCOPE)
