cmake_minimum_required(VERSION 3.16)

project(RentalManagementSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt MOC, RCC, UIC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Policy for AUTOMOC
if(POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)#penambahan

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Widgets 
    Sql
)

# Source files
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/DatabaseManager.cpp
)

# Header files (for AUTOMOC)
set(HEADERS
    include/MainWindow.h
    include/DatabaseManager.h
)

# Create executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

# Link Qt6 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy assets folder to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMENT "Copying assets folder to build directory..."
)

# For Windows: copy Qt DLLs to output directory
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt6::Core>
        $<TARGET_FILE:Qt6::Widgets>
        $<TARGET_FILE:Qt6::Sql>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMENT "Copying Qt DLLs..."
    )
endif()

# Install target
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Install assets
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets
    DESTINATION bin
)

# Print configuration summary
message(STATUS "========================================")
message(STATUS "  Project: ${PROJECT_NAME}")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "----------------------------------------")
message(STATUS "  Qt6 Core: ${Qt6Core_VERSION}")
message(STATUS "  Qt6 Widgets: ${Qt6Widgets_VERSION}")
message(STATUS "  Qt6 Sql: ${Qt6Sql_VERSION}")
message(STATUS "----------------------------------------")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Output Directory: ${CMAKE_BINARY_DIR}/bin")
message(STATUS "  AUTOMOC: ${CMAKE_AUTOMOC}")
message(STATUS "========================================")