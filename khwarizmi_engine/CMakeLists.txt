# ====================================================
# Initial Khwarizmi Engine Prototype - CMakeLists.txt
# ====================================================

cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# ----------------------------------------------------
# Project name and version
# Define the subproject: same version as top-level
# ----------------------------------------------------
project(khwarizmi_engine_app VERSION ${LibKE_VERSION} LANGUAGES CXX)

# Where to put compiled binaries and libs
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# ----------------------------------------------------
# Consistent library name with version
# ----------------------------------------------------
# Use PROJECT_NAME and PROJECT_VERSION — recommended!
set(LibKE "${PROJECT_NAME}_${PROJECT_VERSION}")
message(STATUS "LibKE = ${LibKE}")

# ----------------------------------------------------
# Include variant static library built previously
# ----------------------------------------------------
# You MUST tell CMake where to find the LibKE_Variant target.
# Let's assume you built variant with its own CMakeLists.txt.
# You can do this cleanly with `add_subdirectory` or `find_package`.
# ✅ If variant is in a subfolder:
# add_subdirectory(../variant_lib build_variant)

# Or if you built variant separately, you need to use:
# find_package(LibKE_Variant REQUIRED)   <-- only works if you made a proper install/package.
# For now let's assume you built variant in ../variant_lib/build

# Simple: just link its static lib manually for now:
# e.g., you have ../variant_lib/build/libLibKE_Variant.a

# Alternatively, you can do:
# add_library(LibKE_Variant STATIC IMPORTED)
# set_target_properties(LibKE_Variant PROPERTIES IMPORTED_LOCATION "<full path to lib>")

# For the demo, we'll assume you added variant as a subdirectory:
#add_subdirectory(../variant_lib variant_build)

# Now you have LibKE_Variant target available!

# ----------------------------------------------------
# Define your own library
# ----------------------------------------------------
add_library(${LibKE}
    scene/scene.hpp
    # Add any .cpp files here too!
)

# Public include directories for your LibKE library
target_include_directories(${LibKE}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

# Properties for LibKE
set_target_properties(${LibKE} PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    LINKER_LANGUAGE CXX
)

# ----------------------------------------------------
# Define your executable
# ----------------------------------------------------
add_executable(${PROJECT_NAME} khwarizmi_engine.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    LINKER_LANGUAGE CXX
)

# Public include dirs for executable (optional)
target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

# ----------------------------------------------------
# Link your executable to your library and variant
# ----------------------------------------------------
target_link_libraries(${PROJECT_NAME}
    PUBLIC ${LibKE}
    PUBLIC LibKE_Variant  # Use the ACTUAL target name created by the variant's CMakeLists!
)

# ----------------------------------------------------
# ✅ Notes:
# ----------------------------------------------------
# - Make sure the variant lib target is defined in scope.
#   Using add_subdirectory(../variant_lib variant_build) is the simplest.
#
# - If you installed variant somewhere, use find_package.
#
# - Keep naming consistent: no undefined variables like LibKE_VERSION.
#
# - If you have .cpp files for scene, add them to add_library.