# 프로젝트가 사용하는 외부 라이브러리 들 입니다.
set( external_modules )
set( external_modules_inc )

# 외부 모듈은 추가는 여기서 진행하십시오
# add_subdirectory(SDL2)
# list(APPEND external_modules SDL2 SDL2main )

find_package(SDL2 REQUIRED PATH ${PROJECT_SOURCE_DIR}/cmake )
list(APPEND external_modules ${SDL2_LIBRARY})
list(APPEND external_modules_inc ${SDL2_INCLUDE_DIR})



# image 라이브러리는 mac m1 에 빌드가 안되는 이슈가 존재함
# 그러므로 이것만 FindPackage로 빌드 되어있는 라이브러리를 링크시키겠음
find_package(SDL2_image REQUIRED PATH ${PROJECT_SOURCE_DIR}/cmake )
list(APPEND external_modules ${SDL2_IMAGE_LIBRARIES})
list(APPEND external_modules_inc ${SDL2_IMAGE_INCLUDE_DIRS})

# SDL_ttf 라이브러리
find_package(SDL2_ttf REQUIRED PATH ${PROJECT_SOURCE_DIR}/cmake )
list(APPEND external_modules ${SDL2_TTF_LIBRARIES})
list(APPEND external_modules_inc ${SDL2_TTF_INCLUDE_DIRS})

# SDL_mixer 라이브러리
find_package(SDL2_mixer REQUIRED PATH ${PROJECT_SOURCE_DIR}/cmake )
list(APPEND external_modules ${SDL2_MIXER_LIBRARIES})
list(APPEND external_modules_inc ${SDL2_MIXER_INCLUDE_DIRS})

# boost
find_package(Boost REQUIRED)
list(APPEND external_modules ${Boost_LIBRARY_DIRS})
list(APPEND external_modules_inc ${Boost_INCLUDE_DIRS})

set( module_private_dep_list ${module_private_dep_list} ${external_modules} PARENT_SCOPE)
set( module_private_dep_list_inc ${module_private_dep_list_inc} ${external_modules_inc} PARENT_SCOPE)

