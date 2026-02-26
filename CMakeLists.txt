cmake_minimum_required(VERSION 3.0...4.0 FATAL_ERROR)

project(genjets-course)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -pipe -O2 -g")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(ROOT QUIET)

if(${ROOT_FOUND})
   message(STATUS "ROOT package found")
   link_libraries(${ROOT_LIBRARIES})
elseif(EXISTS "$ENV{ROOT_PATH}/bin/root-config")
   message(STATUS "ROOT path found")
   set(ROOT_INCLUDE_DIRS "$ENV{ROOT_PATH}/include")
   set(ROOT_root_CMD "$ENV{ROOT_PATH}/bin/root-config")
   execute_process(COMMAND ${ROOT_root_CMD} --glibs OUTPUT_VARIABLE ROOT_LIB_FLAGS)
   string(STRIP ${ROOT_LIB_FLAGS} ROOT_LIB_FLAGS)
else()
   message(FATAL_ERROR "ROOT was not found: install it via package manager or set ROOT_PATH if you installed it manually")
endif()

if (EXISTS "$ENV{HEPMC3_PATH}/outputs/bin/HepMC3-config")
   message(STATUS "HEPMC3 path found")
   set(HEPMC3_INCLUDE_DIRS "$ENV{HEPMC3_PATH}/include")
   set(HEPMC3_CMD "$ENV{HEPMC3_PATH}/outputs/bin/HepMC3-config")
   execute_process(COMMAND ${HEPMC3_CMD} --libs OUTPUT_VARIABLE HEPMC3_LIB_FLAGS)
   string(STRIP ${HEPMC3_LIB_FLAGS} HEPMC3_LIB_FLAGS)
elseif (EXISTS "/bin/HepMC3-config")
   set(HEPMC3_INCLUDE_DIRS "/usr/include")
   message(STATUS "HEPMC3 package found")
   set(HEPMC3_CMD "/bin/HepMC3-config")
   execute_process(COMMAND ${HEPMC3_CMD} --libs OUTPUT_VARIABLE HEPMC3_LIB_FLAGS)
   string(STRIP ${HEPMC3_LIB_FLAGS} HEPMC3_LIB_FLAGS)
else()
   message(FATAL_ERROR "HEPMC3 not found: install it manually and set HEPMC3_PATH")
endif()

set(CMAKE_SHARED_LINKER_FLAGS "${ROOT_LIB_FLAGS} ${HEPMC3_LIB_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${ROOT_LIB_FLAGS} ${HEPMC3_LIB_FLAGS}")

include_directories(${CMAKE_SOURCE_DIR}/include ${ROOT_INCLUDE_DIRS} ${HEPMC3_INCLUDE_DIRS})

#add_executable(BasicPythia ${CMAKE_SOURCE_DIR}/src/BasicPythia.cpp)

if (CMAKE_VERSION LESS 4.0)
   string(STRIP ${CMAKE_SHARED_LINKER_FLAGS} CMAKE_EXE_LINKER_FLAGS)
   string(STRIP ${CMAKE_EXE_LINKER_FLAGS} CMAKE_EXE_LINKER_FLAGS)
   #   target_link_libraries(BasicPythia PRIVATE ${CMAKE_EXE_LINKER_FLAGS})
endif()
