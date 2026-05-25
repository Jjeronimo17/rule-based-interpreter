cmake_minimum_required(VERSION 4.0)
project(ProyectoFinal)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProyectoFinal main.cpp
        Lexer.cpp
        Lexer.h
        Parser.cpp
        Parser.h
        Condicion.cpp
        Condicion.h
        Comparacion.cpp
        Comparacion.h
        Hecho.cpp
        Hecho.h
        And.cpp
        And.h
        NodoRule.cpp
        NodoRule.h
        Programa.cpp
        Programa.h
        Interprete.cpp
        Interprete.h
        Entrada.cpp
        Entrada.h
        Analisis.cpp
        Analisis.h)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")