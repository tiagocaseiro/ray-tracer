cmake_minimum_required(VERSION 3.31)

project(ray-tracer LANGUAGES CXX)

add_executable(ray-tracer 
  main.cpp  
  ray.cpp  
  canvas.cpp  
  figures.cpp  
  camera.cpp
)
 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_compile_features(ray-tracer PUBLIC cxx_std_20)

target_include_directories(ray-tracer PUBLIC glm)
