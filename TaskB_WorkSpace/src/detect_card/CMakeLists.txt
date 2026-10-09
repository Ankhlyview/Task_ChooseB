cmake_minimum_required(VERSION 3.8)
project(detect_card)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(color_choose src/ColorChoose.cpp)
add_executable(card_detect src/CardDetect.cpp)

target_include_directories(color_choose PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(color_choose PRIVATE ${OpenCV_LIBS})

target_include_directories(card_detect PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(card_detect PRIVATE ${OpenCV_LIBS})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS color_choose card_detect
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
