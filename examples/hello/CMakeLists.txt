project(examples-hello)

add_executable(hello main.cpp)
target_link_libraries(hello PRIVATE mgfx)
