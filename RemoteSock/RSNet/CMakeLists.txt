# CMakeList.txt : CMake project for RemoteSock, include source and define
# project specific logic here.
#

find_package(Boost 1.89 REQUIRED)

add_library(RSNet INTERFACE)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RemoteSock PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
