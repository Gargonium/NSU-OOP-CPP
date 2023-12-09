cmake_minimum_required(VERSION 3.8)
project(VFP)

set(CMAKE_CXX_STANDARD 17)
set(exe_name ${PROJECT_NAME})

include(FetchContent)
FetchContent_Declare(
    PDcurses
    GIT_REPOSITORY https://github.com/dsavenko/PDCurses.git
    GIT_TAG        dfbac0fe5ef90a40a67d6b13cc7d9c69bf40a5f5
)
FetchContent_MakeAvailable(PDcurses)

add_executable(${PROJECT_NAME} main.cpp "source/Engine/GameObject.cpp" "source/Engine/GameContext.cpp" "source/Textures/Tile.cpp" "source/Entities/Player.cpp" "source/Entities/Door.cpp" "source/Engine/Engine.cpp" "source/Entities/Enemy.cpp" "source/Engine/UploadLvls.cpp")

target_link_libraries(${exe_name} PUBLIC PDcurses )

# ${CMAKE_SOURCE_DIR}/out/_deps/irrKlang-src/bin/winx64-visualStudio/irrKlang.dll

# ��������� ���� � ������������ ������
target_include_directories(${PROJECT_NAME} PUBLIC "include")


