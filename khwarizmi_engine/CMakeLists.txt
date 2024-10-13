# Inital khwarizmi_engine Prototype - CMakeLists.txt
cmake_minimum_required(VERSION 3.5 FATAL_ERROR) #specifies minimum version required

project(khwarizmi_engine CXX)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR})

# Library Name: Turing_Simulator
set(LibKE ${PROJECT_NAME}_${LibKE_VERSION})

# Now we add all the files along with its includes
add_library(${LibKE}
           scene/scene.hpp
            )

# Make sure the compiler can find include files for our LibKE library
target_include_directories (${LibKE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Targets can have properties that affect how they are built.
set_target_properties(${LibKE} PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS ON
        POSITION_INDEPENDENT_CODE ON
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        LINKER_LANGUAGE CXX)

add_executable(${PROJECT_NAME} khwarizmi_engine.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS ON
        POSITION_INDEPENDENT_CODE ON
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        LINKER_LANGUAGE CXX
        )
        #COMPILE_FLAGS "-ldraw -lglew32 -lgdi32 -lopengl32  -lGL -lglut")

target_include_directories (${PROJECT_NAME} PUBLIC
                            )

# Link the executable to LibKE
target_link_libraries (${PROJECT_NAME} LINK_PUBLIC ${LibKE}
                        )