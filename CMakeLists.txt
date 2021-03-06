cmake_minimum_required(VERSION 3.5)
project(sqlite3_demo)

# Default to C99
# if(NOT CMAKE_C_STANDARD)
#   set(CMAKE_C_STANDARD 99)
# endif()

# Default to C++14
# if(NOT CMAKE_CXX_STANDARD)
#   set(CMAKE_CXX_STANDARD 14)
# endif()

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()

# find dependencies
# find_package(sqlite3 REQUIRED)
# find_package(rclcpp REQUIRED)

include_directories(
./include
# ${catkin_INCLUDE_DIRS}
)

add_executable(demo src/demo.cpp)
target_link_libraries(demo sqlite3)

# add_executable(db_tool src/db_tool.cpp)
# target_link_libraries(db_tool sqlite3)

add_library(db_lib
  src/db_tool.cpp
)
target_link_libraries(db_lib
    sqlite3
)

set(SOURCES
  # src/db_tool.cpp
  src/singleton_db.cpp
)

add_executable(singleton_db ${SOURCES})
target_link_libraries(singleton_db 
  sqlite3
  db_lib
)

## Install headers

# install(TARGETS
#   demo
#   DESTINATION
#   lib/${PROJECT_NAME})

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# ament_package()
