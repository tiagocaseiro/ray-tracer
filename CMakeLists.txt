cmake_minimum_required(VERSION 3.31)

project(ray-tracer LANGUAGES CXX)

include_directories(src)

add_executable(ray-tracer 
  src/main.cpp  
  src/tuple.cpp 
  src/mat.cpp 
  src/ray.cpp 
  src/common.cpp 
  src/canvas.cpp 
  src/lighting.cpp
  src/world.cpp
)

target_compile_options(ray-tracer PRIVATE /Wall /WX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_compile_features(ray-tracer PUBLIC cxx_std_20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  ray-tracer-tests
  tests/tuple_test.cpp
  tests/color_test.cpp
  tests/canvas_test.cpp
  tests/mat_test.cpp
  tests/ray_test.cpp
  tests/lighting_test.cpp
  tests/world_test.cpp
  src/tuple.cpp 
  src/mat.cpp 
  src/ray.cpp
  src/common.cpp 
  src/canvas.cpp 
  src/lighting.cpp
  src/world.cpp
)

target_link_libraries(
  ray-tracer-tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ray-tracer-tests)
