cmake_minimum_required(VERSION 3.10)
project(CircularQueueExample LANGUAGES CXX)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исполняемый файл из исходного кода
add_executable(CircularQueueExample main.cpp)

# Если файлы с реализацией располагаются в отдельных каталогах,
# можно использовать target_include_directories
target_include_directories(CircularQueueExample PRIVATE ${PROJECT_SOURCE_DIR})
