# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(regexTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(regex_test source/regex_test.cpp)
target_link_libraries(
    regex_test PRIVATE
    regex_lib
    Catch2::Catch2WithMain
)
target_compile_features(regex_test PRIVATE cxx_std_17)

catch_discover_tests(regex_test)

# ---- End-of-file commands ----

add_folders(Test)
