# ================================================
# CMakeLists.txt
# ================================================

cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# Define the project name and version.
# These become PROJECT_NAME and PROJECT_VERSION.
project(LibKE_Variant VERSION 0.0.1 LANGUAGES CXX)

message(STATUS "Project name is ${PROJECT_NAME}")      # → LibKE_Variant
message(STATUS "Project version is ${PROJECT_VERSION}")  # → 0.0.1

# --------------------------------------------
# Define your target name consistently:
# Use the PROJECT_NAME directly as the library name.
# --------------------------------------------

# For demonstration: if you want a versioned target name:
#set(LibKE_Variant ${PROJECT_NAME}_${PROJECT_VERSION})
# But for simplicity, we'll stick with PROJECT_NAME.
set(LibKE_Variant ${PROJECT_NAME})
message(STATUS "Library target name is ${LibKE_Variant}")

# --------------------------------------------
# Define the header-only include directory
# --------------------------------------------

# In your case, all .hpp files are directly in this folder:
set(VARIANT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# --------------------------------------------
# Collect headers
# --------------------------------------------

file(GLOB VARIANT_HEADERS "${VARIANT_INCLUDE_DIR}/*.hpp")

# --------------------------------------------
# Create the static library target
# --------------------------------------------

add_library(${LibKE_Variant} STATIC ${VARIANT_HEADERS})

# --------------------------------------------
# Target properties: recommended modern CMake way
# --------------------------------------------

# --------------------------------------------
# Public include directories
# --------------------------------------------

# Key: include the PARENT of 'variant_lib' so that:
# #include "variant_lib/variant.hpp" works
target_include_directories(${LibKE_Variant} PUBLIC
 ${CMAKE_SOURCE_DIR}  # <- top-level root # <-- THIS IS THE ROOT, so 'variant_lib/variant.hpp' works.
 ${VARIANT_INCLUDE_DIR}
 ${CMAKE_CURRENT_SOURCE_DIR}
)

# (Optional) Status message
message(STATUS "${LibKE_Variant} public include: ${CMAKE_SOURCE_DIR}")


set_target_properties(${LibKE_Variant} PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    LINKER_LANGUAGE CXX
)


# --------------------------------------------
# Optional: print what you got
# --------------------------------------------

message(STATUS "✅ ${LibKE_Variant} will include headers from: ${VARIANT_INCLUDE_DIR}")