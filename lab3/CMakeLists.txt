cmake_minimum_required(VERSION 3.14)
project(creatingDollar-lab3)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME} main.cpp "src/Engine/Engine.cpp" "src/Engine/Draw.cpp" "src/Engine/Input.cpp" "src/Entities/Player.cpp" "src/Engine/Update.cpp"  "src/Engine/Globals.cpp" "src/Textures/Floor.cpp" "src/Textures/Box.cpp")

# Добавляем путь к заголовочным файлам
target_include_directories(${PROJECT_NAME} PUBLIC "include")
