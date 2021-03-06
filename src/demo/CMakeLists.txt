cmake_minimum_required(VERSION 3.0)
project(lucene++-demo)

file(GLOB_RECURSE
  demo_headers
  "${lucene++-demo_SOURCE_DIR}/../include/*.h"
)

add_definitions(-DLPP_HAVE_DLL)
find_package(Boost REQUIRED)

include_directories(
  ${Boost_INCLUDE_DIRS}
)
include_directories(
  "${lucene++_SOURCE_DIR}/include"
)

add_executable(indexfiles
  "${lucene++-demo_SOURCE_DIR}/indexfiles/main.cpp"
  ${demo_headers}
)
target_link_libraries(indexfiles
  lucene++ boost_system
)

add_executable(searchfiles
  "${lucene++-demo_SOURCE_DIR}/searchfiles/main.cpp"
  ${demo_headers}
)
target_link_libraries(searchfiles
  lucene++ boost_system
)

add_executable(deletefiles
  "${lucene++-demo_SOURCE_DIR}/deletefiles/main.cpp"
  ${demo_headers}
)
target_link_libraries(deletefiles
  lucene++ boost_system
)

add_executable(termquery
  "${lucene++-demo_SOURCE_DIR}/TermQueryBench/main.cpp"
  ${demo_headers}
)

target_link_libraries(termquery
  lucene++ boost_system
)

add_executable(indexreload
  "${lucene++-demo_SOURCE_DIR}/IndexReload/main.cpp"
  ${demo_headers}
)

target_link_libraries(indexreload
  lucene++ boost_system
)

add_executable(valetbench
  "${lucene++-demo_SOURCE_DIR}/valetBench/main.cpp"
  ${demo_headers}
)

target_link_libraries(valetbench
  lucene++ boost_system
)