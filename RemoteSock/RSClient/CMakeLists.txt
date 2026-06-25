

find_package(Boost 1.89 REQUIRED)

add_executable (RSClient "RSClient.cpp" "RSClient.h")

target_link_libraries(RSClient PRIVATE Boost::headers)