add_executable(inside inside_loop.c)
add_executable(outside outside_loop.c)
add_executable(without without_locks.c)

target_link_libraries(inside pthread)
target_link_libraries(outside pthread)
target_link_libraries(without pthread)