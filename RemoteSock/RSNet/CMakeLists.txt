# CMakeList.txt : CMake project for RemoteSock, include source and define
# project specific logic here.
#

find_package(Boost 1.89 REQUIRED)

add_subdirectory(Queue)

add_library(RSNet "GameServer.cpp" "RSNet.h" "Connection.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RemoteSock PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(RSNet PUBLIC Boost::headers PRIVATE Queue)

target_include_directories(RSNet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET RSNet PROPERTY CXX_STANDARD 20)