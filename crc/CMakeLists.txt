# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.


project(CrcLib)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(. CRC_SRC)
message("CRC_SRC: ${CRC_SRC}")

add_library(crc STATIC ${CRC_SRC} CRC16CCITT.cpp CRC16CCITT.h CRC64WE.cpp CRC64WE.h)
