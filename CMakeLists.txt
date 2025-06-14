cmake_minimum_required(VERSION 3.20)
project(WordleSFML)

set(CMAKE_CXX_STANDARD 14)

# Добавляем поддиректорию external (где скачивается SFML)
add_subdirectory(external)

# Добавляем поддиректорию с кодом (где определена цель WordleSFML)
add_subdirectory(WordleSFML)
add_subdirectory(Fonts)
add_subdirectory(server)

# Связываем необходимые библиотеки SFML с целью WordleSFML
target_link_libraries(WordleSFML
  sfml-graphics
  sfml-window
  sfml-system
)
enable_testing()

