cmake_minimum_required(VERSION 3.1)

project(Mercury)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_RELEASE_LIBS       ON)
set(Boost_USE_MULTITHREADED      ON)

set(Boost_ADDITIONAL_VERSIONS 1.70.0 1.70)

find_package(Qt5 COMPONENTS Core Widgets Sql REQUIRED)
find_package(Boost 1.70.0 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/Mercury)
include_directories(${PROJECT_SOURCE_DIR}/Mercury/GeneratedFiles)


file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/Mercury/*.h"
        "${PROJECT_SOURCE_DIR}/Mercury/*.hpp"
        "${PROJECT_SOURCE_DIR}/Mercury/*.cpp"
        "${PROJECT_SOURCE_DIR}/Mercury/*.c"
        )

add_subdirectory(tests)

add_executable(Mercury ${all_SRCS})

if(MSVC)
	SET_TARGET_PROPERTIES(Mercury PROPERTIES LINK_FLAGS -APPCONTAINER:NO)
endif()

target_link_libraries(Mercury Qt5::Widgets Qt5::Core Qt5::Sql ${BOOST_LIBRARIES})

if(WIN32)
	include(cmake/DeployQt.cmake)
	windeployqt(Mercury)
endif()