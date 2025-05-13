cmake_minimum_required(VERSION 3.31)

project(ray-tracer LANGUAGES CXX)

include_directories(src)

add_executable(ray-tracer 
  src/main.cpp  
)

target_compile_options(ray-tracer PRIVATE /Wall /WX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_compile_features(ray-tracer PUBLIC cxx_std_20)
