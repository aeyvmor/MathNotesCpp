cmake_minimum_required(VERSION 3.16)
project(MathNotesCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

# Automatically handle moc, uic, and rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Automatically find all source files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable
add_executable(MathNotesCpp
    ${SOURCES}
    resources.qrc
)

# Link against the Qt libraries
target_link_libraries(MathNotesCpp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)