cmake_minimum_required(VERSION 3.1)

project(tests)

set(CMAKE_CXX_STANDARD 17)

find_package(GTEST REQUIRED)

enable_testing()

include_directories(${GTEST_INCLUDE_DIR})

file(GLOB tsts
        "${PROJECT_SOURCE_DIR}/*.cpp"
        )

add_executable(tests ${tsts})

if(MSVC)
	SET_TARGET_PROPERTIES(tests PROPERTIES LINK_FLAGS -NODEFAULTLIB:library)
	SET_TARGET_PROPERTIES(tests PROPERTIES COMPILE_FLAGS -MTd)
endif()

target_link_libraries(tests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

