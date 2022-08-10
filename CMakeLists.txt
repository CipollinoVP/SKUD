cmake_minimum_required(VERSION 3.3)

project(SKUD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(INCLUDES
        main_settings.h
        SecurityApp.h
        SinglePassApp.h
        OrderPassApp.h
        MessengerApp.h
        LoginApp.h
        DirectorApp.h
        MenuApp.h)

add_executable(SKUD main.cpp ${INCLUDES})

find_package(OpenCV REQUIRED)
find_package(PostgreSQL REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(SKUD PRIVATE ${PostgreSQL_LIBRARIES} ${GTK3_LIBRARIES} ${OpenCV_LIBS})

target_include_directories(SKUD PRIVATE ${PostgreSQL_INCLUDE_DIRS})
