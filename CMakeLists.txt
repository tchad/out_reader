cmake_minimum_required(VERSION 3.1.0)

project(reader)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(reader
    src/gui/out_load_dialog.ui 
    src/gui/include/out_load_dialog.h
    src/gui/out_load_dialog.cpp
    src/gui/main_window.ui 
    src/gui/include/main_window.h
    src/gui/main_window.cpp
    src/gui/include/gui_main.h
    src/gui/gui_main.cpp
    src/parser/dataset_abstract.cpp
    src/parser/dataset_null.cpp
    src/parser/dataset_v5_3.cpp
    src/parser/storage.cpp
    src/parser/reader.cpp
    src/parser/parser.cpp
    src/parser/parser_engine_v5_3.cpp
    src/main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb")
target_link_libraries(reader Qt5::Widgets)
target_include_directories(reader PUBLIC src )

