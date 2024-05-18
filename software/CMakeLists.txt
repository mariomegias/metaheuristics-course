cmake_minimum_required(VERSION 3.16)

project(APC_problem DESCRIPTION "Solution of APC problem with different algorithms" LANGUAGES CXX)

set(SRC_DIR ./FUENTES/src)
set(INC_DIR ./FUENTES/inc)
set(SOURCE_FILES
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/arff_file.cpp
        ${SRC_DIR}/classifier_1NN.cpp
        ${SRC_DIR}/greedy_relief.cpp
        ${SRC_DIR}/local_search.cpp
        ${SRC_DIR}/metaheuristics.cpp
        ${SRC_DIR}/apc.cpp
        ${SRC_DIR}/ag.cpp
        ${SRC_DIR}/agg.cpp
        ${SRC_DIR}/age.cpp
        ${SRC_DIR}/blx.cpp
        ${SRC_DIR}/ca.cpp
        ${SRC_DIR}/am.cpp
        ${SRC_DIR}/am_all.cpp
        ${SRC_DIR}/am_rand.cpp
        ${SRC_DIR}/am_best.cpp
        ${SRC_DIR}/tournament.cpp
        ${SRC_DIR}/es.cpp
        ${SRC_DIR}/bmb.cpp
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O2")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/BIN
)