cmake_minimum_required(VERSION 3.16)

project(assignment4)

# gdb mode
# SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
# gdb mode

SET(MAIN_PATH ${PROJECT_SOURCE_DIR})


SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/")
SET(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib/")
SET(DIR_SRC "${PROJECT_SOURCE_DIR}/src/")

configure_file(${DIR_SRC}/param_deliver.h.in ${PROJECT_SOURCE_DIR}/include/param_deliver.h)
include_directories("${PROJECT_SOURCE_DIR}/include/")

message(${DIR_SRC})

add_subdirectory(src)


set(flag 1)
if(${flag})
    set(START_IDX 1)
    set(END_IDX 5)
    set(STEP_IDX 1)
    foreach(i RANGE ${START_IDX} ${END_IDX} ${STEP_IDX})
        # message(answer${i})
        aux_source_directory(${DIR_SRC}/answer${i} ANSWER_SRC${i})
        message(${DIR_SRC}answer${i})
    endforeach()

    foreach(i RANGE ${START_IDX} 2 ${STEP_IDX})
        add_executable(answer${i} ${ANSWER_SRC${i}})
    endforeach()

    foreach(i RANGE 3 ${END_IDX} ${STEP_IDX})
        add_executable(answer${i} ${ANSWER_SRC${i}})
        target_link_libraries(answer${i} MyList)
    endforeach()
endif()

add_executable(demo ${DIR_SRC}/demo.c)
target_link_libraries(demo MyList)