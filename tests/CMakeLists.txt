cmake_minimum_required(VERSION 3.1)

enable_testing()
project(tests)

find_package(GTEST REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIRECTORY}/Mercury)

file(GLOB tsts
        "${PROJECT_SOURCE_DIR}/*.cpp"
        )

add_executable(tests ${tsts})

if(MSVC)
	SET_TARGET_PROPERTIES(tests PROPERTIES LINK_FLAGS -NODEFAULTLIB:library)
	SET_TARGET_PROPERTIES(tests PROPERTIES COMPILE_FLAGS -MTd)
endif()

target_link_libraries(tests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Qt5::Core)

