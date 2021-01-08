cmake_minimum_required(VERSION 3.17)
project(universityTimetabling_master)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/class)
include_directories(src/engine)
include_directories(src/io)

add_executable(universityTimetabling_master
        src/class/agenda.cpp
        src/class/agenda.hpp
        src/class/curso.hpp
        src/class/disciplina.hpp
        src/class/discSol.cpp
        src/class/discSol.hpp
        src/class/professor.hpp
        src/class/profSol.cpp
        src/class/profSol.hpp
        src/class/sala.hpp
        src/class/salaSol.cpp
        src/class/salaSol.hpp
        src/class/turma.hpp
        src/class/turmaSol.cpp
        src/class/turmaSol.hpp
        src/engine/metaheuristica.cpp
        src/engine/metaheuristica.hpp
        src/engine/solucao.cpp
        src/engine/solucao.hpp
        src/io/data.cpp
        src/io/data.hpp
        src/main.cpp)
