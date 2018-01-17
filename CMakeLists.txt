cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project (quxx)

#
# import ExternalProject module
#
include(ExternalProject)

#
# compiler options
#
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(SUPPORT_LARGE_FILES ON)

if(UNIX AND NOT APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")
elseif(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0 /D_WIN32_WINNT=0x0601")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.10")
endif()

#
# debug info
#
MESSAGE(STATUS "runtime:" ${NODE_RUNTIME})
MESSAGE(STATUS "runtime version:" ${NODE_RUNTIMEVERSION})
MESSAGE(STATUS "architecture:" ${NODE_ARCH})

include_directories(BEFORE ${CMAKE_JS_INC})

file(GLOB SOURCE_FILES "src/*.cc" "src/*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

add_dependencies(${PROJECT_NAME} quxx)
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

