cmake_minimum_required (VERSION 3.1.0)
project (rings)

# Set Configuration specific DEFINES
IF ( CMAKE_BUILD_TYPE STREQUAL "Debug" ) 
  add_definitions ( "-DUSE_PERFORMANCE_DATA")
  add_definitions ( "-DDEBUG " )
  add_definitions ( "-D_DEBUG " )
  add_definitions ( "-std=c++20")
  add_definitions ( "-rdynamic ")
  add_definitions ( "-g ")

  add_definitions ( "-Wno-deprecated ")
  add_definitions ( "-Wno-unknown-pragmas ")

ELSE()
  add_definitions ( "-Wall ")
  add_definitions ( "-DNDEBUG " )
  add_definitions ( "-DUSE_PERFORMANCE_DATA")
  add_definitions ( "-O3 ")
  add_definitions ( "-std=c++20")
  add_definitions ( "-march=native ")
  add_definitions ( "-mtune=native ")
  add_definitions ( "-Wno-deprecated ")
  add_definitions ( "-Wno-unknown-pragmas ")
  add_definitions ( "-rdynamic ")
  add_definitions ( "-g ")
ENDIF()


include_directories (/usr/include)
include_directories (/usr/local/include)

link_directories (/usr/lib)
link_directories (/usr/local/lib)

add_executable (hello 
  hello/hello.cpp)

add_executable (ex01 
  ex01/ex01.cpp)

add_executable (ex02 
  ex02/src/fractions.cpp
  ex02/src/decimal.cpp
  ex02/src/ex02.cpp)

add_executable (ex03 
  ex02/src/fractions.cpp
  ex02/src/decimal.cpp
  ex02/src/ex03.cpp)

add_executable (analysis
  analysis/src/main.cpp
  analysis/src/calc_mean.cpp
  analysis/src/calc_sum.cpp
  )

add_executable (double
  double/main.cpp
)
target_link_libraries(double pthread)

add_executable (edu
edu/main.cpp
)
target_link_libraries(edu pthread)

add_executable (ring00
ring00/main.cpp
)
target_link_libraries(ring00 pthread)
