cmake_minimum_required(VERSION 3.20)
project(WordleSFML)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(external)

add_subdirectory(WordleSFML)
add_subdirectory(Fonts)
add_subdirectory(server)

target_link_libraries(WordleSFML
  sfml-graphics
  sfml-window
  sfml-system
)
enable_testing()

