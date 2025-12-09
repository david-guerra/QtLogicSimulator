cmake_minimum_required(VERSION 3.16)

project(MyLogicSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON) # <--- The magic switch
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# This generates the compile_commands.json for Neovim/Clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Qt 6 (Widgets module includes Graphics View)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Add your source files
add_executable(MyLogicSim
    main.cpp
    mainWindow.cpp
    gate.h
    mainWindow.h
    pin.h
    pin.cpp
    PinContainer.h
    wire.h
    wire.cpp
  )

# Link Qt libraries
target_link_libraries(MyLogicSim PRIVATE Qt6::Widgets)

# Fix for macOS bundles (optional, but good for M4)
set_target_properties(MyLogicSim PROPERTIES MACOSX_BUNDLE ON)
