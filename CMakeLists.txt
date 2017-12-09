cmake_minimum_required(VERSION 2.8)
project(openpose_test)

#config for c++11
include (CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
if (1)
  if (CMAKE_COMPLIER_IS_GUNCXX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=gun++11")
  else()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
  endif()
endif()

find_package(Boost REQUIRED system filesystem)
include_directories(${Boost_INCLUDE_DIR})
link_directories( ${Boost_LIBRARY_DIRS} )

add_executable(${PROJECT_NAME}_rmboost rmboost.cpp)
target_link_libraries(${PROJECT_NAME}_rmboost ${Boost_LIBRARIES})
