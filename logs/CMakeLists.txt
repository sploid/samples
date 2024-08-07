qt6_add_executable(one one.cc)
target_link_libraries(one PRIVATE Qt6::Core)

qt6_add_executable(two two.cc)
target_link_libraries(two PRIVATE Qt6::Core)

qt6_add_executable(three three.cc)
target_link_libraries(three PRIVATE Qt6::Core)

qt6_add_executable(four four.cc)
target_link_libraries(four PRIVATE Qt6::Core)

qt6_add_executable(five five.cc)
target_link_libraries(five PRIVATE Qt6::Core)
