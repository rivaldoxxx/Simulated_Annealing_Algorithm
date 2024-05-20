cmake_minimum_required(VERSION 3.21)
project(PEA)

set(CMAKE_CXX_STANDARD 14)


#include_directories(src)

add_executable(PEA_PROJ2
        Graf.cpp
        Graf.h
        Menu.cpp
        Menu.h
        main.cpp
        SymulowaneWyzarzanie.cpp
        SymulowaneWyzarzanie.h
        Sciezka.h
        Sciezka.cpp
        )
# Dodaj katalog z TinyXML-2 do listy katalogów include
#include_directories(C:/Users/fizyk/CLionProjects/PEA/src/tinyxml2-master)
#
## Dodaj źródła TinyXML-2 do projektu
#add_library(tinyxml2 STATIC C:/Users/fizyk/CLionProjects/PEA/src/tinyxml2-master/tinyxml2.cpp)
#
## Linkuj bibliotekę tinyxml2 do twojego projektu
#target_link_libraries(E2 tinyxml2-master)

