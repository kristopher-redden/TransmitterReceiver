cmake_minimum_required(VERSION 3.8)
project(TransmitterReceiver)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp PhysicalLayer.cpp PhysicalLayer.h ApplicationLayer.cpp ApplicationLayer.h)
add_executable(TransmitterReceiver ${SOURCE_FILES})