cmake_minimum_required(VERSION 3.14)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(exe_name ${PROJECT_NAME})

if(WIN32 OR MSVC)
    include(FetchContent)
    FetchContent_Declare(
        PDcurses
        GIT_REPOSITORY https://github.com/dsavenko/PDCurses.git
        GIT_TAG        dfbac0fe5ef90a40a67d6b13cc7d9c69bf40a5f5
    )
    FetchContent_MakeAvailable(PDcurses)
endif()

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME} main.cpp "source/Engine/GameObject.cpp" "source/Engine/GameContext.cpp" "source/Textures/Tile.cpp" "source/Entities/Player.cpp" "source/Entities/Door.cpp" "source/Engine/Engine.cpp" "source/Entities/Enemy.cpp" "source/Engine/UploadLvls.cpp")

if(WIN32 OR MSVC)
    target_link_libraries(${exe_name} PDcurses)
else()
    target_link_libraries(${exe_name} curses)
endif()

# Добавляем путь к заголовочным файлам
target_include_directories(${PROJECT_NAME} PUBLIC "include")
