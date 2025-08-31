cmake_minimum_required(VERSION 3.16)

# Set the project name (this also determines the executable name)
project(CountdownTimer)

# Find the required Qt6 packages
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Automatically handle Qt's special compilation steps (moc, uic, rcc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set the C++ standard (Qt6 requires C++17 or newer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add our source file to create an executable named "CountdownTimer"
add_executable(CountdownTimer main.cpp)

# Link the executable against the Qt6 Widgets library
target_link_libraries(CountdownTimer PRIVATE Qt6::Widgets)

