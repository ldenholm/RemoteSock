find_package(Boost 1.89 REQUIRED)

add_library(Queue)


target_sources(Queue
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/RSNetQueue.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/RSNetQueue.h
  )

target_link_libraries(Queue PUBLIC Boost::headers)