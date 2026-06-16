cmake_minimum_required(VERSION 3.30)

project(TAREA2ALGORITMOS C)

set(CMAKE_C_STANDARD 11)

add_executable(TAREA2ALGORITMOS

        src/main.c

        src/experiments.c

        src/avl_tree/avl.c

        src/splay_tree/splay.c

)

target_include_directories(

        TAREA2ALGORITMOS

        PRIVATE

        src

        src/avl_tree

        src/splay_tree

)

target_link_libraries(

        TAREA2ALGORITMOS

        m

)