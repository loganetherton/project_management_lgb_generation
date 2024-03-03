cmake_minimum_required(VERSION 3.22)
project(pybind)

set(CMAKE_CXX_STANDARD 20)

# NOTE: For apple clang, the compiler options are libstdc++ (deprecated) and libc++. This is different
# than Unix systems, which use libstdc++ and libstdc++11 (new ABI, application binary interface)
# @link: https://docs.conan.io/en/latest/howtos/manage_gcc_abi.html#manage-gcc-abi

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    # Specifying TARGETS argument is necessary to use the "modern" cmake target_link_libraries call below,
    # target_link_libraries(learning CONAN_PKG::poco)
    # https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_generator.html#targets-approach
    conan_basic_setup(TARGETS)
    # Call this way to make conan packages globally available
    # https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_generator.html#global-variables-approach
#     conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

#get_cmake_organization(_variableNames VARIABLES)
#list(SORT _variableNames)
#foreach (_variableNames ${_variableNames})
#    message(STATUS "${_variableNames}=${${_variableNames}}")
#endforeach ()

# Add in interpreter, development headers for Python, include necessary dirs
find_package(Python COMPONENTS Interpreter Development)

get_cmake_organization(_variableNames VARIABLES)
list(SORT _variableNames)
foreach (_variableNames ${_variableNames})
    message(STATUS "${_variableNames}=${${_variableNames}}")
endforeach ()

find_package(pybind11 REQUIRED)
include_directories(${Python_INCLUDE_DIRS})

add_executable(pybind main.cpp src/Dashboard.h src/TeamData.h
        src/UserData.h src/ConfigReport.h src/OrganizationContentClassification.h src/MongoTypes.h src/Project.h src/types.h
        src/BaseJsonStruct.h src/jsonObjects.h src/subTask.h src/Task.h src/AssignedUser.h src/Comment.h src/TaskInfo.h src/ProgressInfo.h)

# Conan makes an environment variable called "CONAN_INCLUDE_DIRS" that includes dependencies.
# @link: https://docs.conan.io/en/latest/reference/generators/cmake.html
target_link_libraries(pybind ${Python_LIBRARIES})
# Global linking
#target_link_libraries(pybind ${CONAN_LIBS})
# Target linking
target_link_libraries(pybind CONAN_PKG::fmt)
target_link_libraries(pybind CONAN_PKG::boost)
target_link_libraries(pybind CONAN_PKG::nlohmann_json)
target_link_libraries(pybind CONAN_PKG::pybind11)

# PyBind11 way of creating libs, macro is accessible after calling find_package(pybind11 REQUIRED)
pybind11_add_module(pm_tickets main.cpp)

# This is set so that we don't have to manually copy the built library to where Python can find it
# @link https://stackoverflow.com/questions/9994045/copy-target-file-to-another-location-in-a-post-build-step-in-cmake
set_target_properties(pm_tickets PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY_DEBUG /home/logan/projects/cpp/pybind/src/py
        LIBRARY_OUTPUT_DIRECTORY_RELEASE /home/logan/projects/cpp/pybind/dashboard
)

# The error I was getting before with mixed usages of target_link_libraries referred to having the PUBLIC/PRIVATE/etc
# keyword in some of the usages of target_link_libraries, specifically in pybind11_add_module, using visibility,
# and mine not using it
# Link in pybind11, fmt, anything else we need
target_link_libraries(pm_tickets PUBLIC pybind11::headers)
target_link_libraries(pm_tickets PUBLIC CONAN_PKG::fmt)
target_link_libraries(pm_tickets PUBLIC CONAN_PKG::nlohmann_json)

# CMAKE_BUILD_TYPE=Debug
# Note: This was not originally working before. The reason is that string expansion can happen more than
# once. So, if CMAKE_BUILD_TYPE is "Debug," but there is a variable called "Debug" that is equal to something else
# then that will end up being compared. So, by adding an extra space, it prevents that expansion
# @link https://stackoverflow.com/questions/19982340/cmake-compare-to-empty-string-with-strequal-failed
#if (NOT "${CMAKE_BUILD_TYPE} " STREQUAL "Debug ")
#    message("NOT DEBUG ")
#else()
#    message("DEBUG ")
#    message("${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
#endif()

# This is non-PyBind11 way of creating Python shared module
#Python_add_library(pm_tickets main.cpp src/func.cpp src/func.h)
#set_target_properties(pm_tickets PROPERTIES
#        INTERPROCEDURAL_OPTIMIZATION ON
#        CXX_VISIBILITY_PRESET default
#        VISIBLITY_INLINES_HIDDEN ON)
