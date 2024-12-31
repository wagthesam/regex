cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    regex
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

file(GLOB_RECURSE SOURCES "source/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX "main\\.cpp$")  
file(GLOB_RECURSE HEADERS "source/*.hpp")  

add_library(
    regex_lib OBJECT
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(
    regex_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(regex_lib PUBLIC cxx_std_17)

find_package(fmt REQUIRED)
target_link_libraries(regex_lib PRIVATE fmt::fmt)

# ---- Declare executable ----

add_executable(regex_exe source/main.cpp)
add_executable(regex::exe ALIAS regex_exe)

set_property(TARGET regex_exe PROPERTY OUTPUT_NAME regex)

target_compile_features(regex_exe PRIVATE cxx_std_17)

target_link_libraries(regex_exe PRIVATE regex_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT regex_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of regex"
  )
endif()

include(cmake/dev-mode.cmake)
