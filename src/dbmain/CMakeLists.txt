# src/dbmain/CMakeLists.txt

add_tdb_object_library(dbmain
    Database.cpp)

add_executable(taco
    Main.cpp)
