project(Calculator CXX)

cmake_minimum_required(VERSION 3.17)

file(GLOB SRC_CORE_FILES ${PROJECT_SOURCE_DIR}/sourse/core/*.cpp ${PROJECT_SOURCE_DIR}/sourse/core/*.h)
file(GLOB MAIN_CPP ${PROJECT_SOURCE_DIR}/sourse/*.cpp)

file(GLOB SRC_TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_CORE_FILES} ${MAIN_CPP})
set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINKER_LANGUAGE CXX)
add_library(ObjectLibCalculator OBJECT ${SRC_CORE_FILES})

add_executable("${CMAKE_PROJECT_NAME}_test" ${SRC_TEST_FILES} $<TARGET_OBJECTS:ObjectLibCalculator>)
#add_executable("${CMAKE_PROJECT_NAME}_test" ${SRC_TEST_FILES})
set_target_properties("${CMAKE_PROJECT_NAME}_test" PROPERTIES LINKER_LANGUAGE CXX)


