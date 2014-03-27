cmake_minimum_required (VERSION 2.6) 
project (img_sim)
SET(CMAKE_CXX_FLAGS "-std=c++0x -O2 -g" )

include_directories(./)

file(GLOB SRC_FILE "src/*.cpp")
file(GLOB INCLUDE_FILE "include/*.cpp")

add_executable(img_sim ${INCLUDE_FILE} ${SRC_FILE} main.cpp)


find_package(X11)
find_package(Threads)
find_package(Boost)
find_package(Boost REQUIRED COMPONENTS program_options filesystem system)
if (X11_FOUND)
include_directories(${X11_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries (img_sim ${X11_LIBRARIES})
endif (X11_FOUND)

target_link_libraries(img_sim ${Boost_LIBRARIES} )
target_link_libraries(img_sim ${CMAKE_THREAD_LIBS_INIT})


