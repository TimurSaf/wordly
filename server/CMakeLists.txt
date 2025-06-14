add_executable(http_server main.cpp http_server.cpp file_name.cpp check_word.cpp get_word.cpp http_server.hpp)

add_executable(file_name_test file_name.cpp file_name_test.cpp http_server.hpp)
add_executable(get_word_test get_word.cpp get_word_test.cpp check_word.cpp file_name.cpp http_server.hpp)
add_executable(check_word_test check_word_test.cpp check_word.cpp file_name.cpp http_server.hpp)


target_link_libraries(file_name_test doctest)
target_link_libraries(get_word_test doctest)
target_link_libraries(check_word_test doctest)


enable_testing()

add_test(NAME file_name_test COMMAND file_name_test --force-colors -d)
add_test(NAME get_word_test COMMAND get_word_test --force-colors -d)
add_test(NAME check_word_test COMMAND check_word_test --force-colors -d)



configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dict_4.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dict_5.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dict_6.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pool_dict_4.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pool_dict_5.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pool_dict_6.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)