cmake_minimum_required(VERSION 3.20)



project(dummy LANGUAGES CXX VERSION 0.0.0)

message(STATUS "${CMAKE_PROJECT_NAME} Version: ${CMAKE_PROJECT_VERSION}")

math(EXPR bits "8*${CMAKE_SIZEOF_VOID_P}")
message(STATUS "Target is ${bits} bits")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(dummy SHARED)
target_sources(dummy PRIVATE dummy.cpp dummy.hpp)
target_include_directories(dummy PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>$<INSTALL_INTERFACE:include>)
set_target_properties(dummy PROPERTIES VERSION ${CMAKE_PROJECT_VERSION} SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

file(GLOB_RECURSE eti_files FOLLOW_SYMLINKS eti/*.cpp)
target_sources(dummy PRIVATE ${eti_files})
foreach(scalar float)
    file(GLOB_RECURSE f FOLLOW_SYMLINKS eti/${scalar}/*.cpp)
    set_source_files_properties(${f} PROPERTIES COMPILE_DEFINITIONS "DUMMY_ETI_SCALAR=${scalar}")
endforeach()

add_executable(dummy_exe main.cpp)
target_link_libraries(dummy_exe PRIVATE dummy)

include(GNUInstallDirs)
install(TARGETS dummy dummy_exe
    EXPORT dummyTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES dummy.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT dummyTargets
    FILE dummyConfig.cmake
    NAMESPACE dummy::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dummy)
