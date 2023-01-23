cmake_minimum_required(VERSION 3.10)
project(api LANGUAGES CXX C)

# Specify C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check for C++11 support
if(NOT CMAKE_CXX_STANDARD)
    message(FATAL_ERROR "C++11 support not found.")
endif()

#Specify C standard
set(CMAKE_C_STANDARD 11)

add_library(api
  SHARED
  ./api.cpp
  exports.def
)