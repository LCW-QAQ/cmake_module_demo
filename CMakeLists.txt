cmake_minimum_required(VERSION 3.0.0)
project(cmkmod VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 引入后会自动设置了 CMAKE_INSTALL_BINDIR、CMAKE_INSTALL_LIBDIR、CMAKE_INSTALL_INCLUDEDIR 等变量，
# 然后通过 install 命令指定了可执行文件、库文件和头文件的安装路径。这样做使得项目更容易在不同的系统上进行移植和安装。
# 在linux上CMAKE_INSTALL_PREFIX=，windows上则为C:/Program Files (x86)/${PROJECT_NAME}或C:/Program Files/${PROJECT_NAME}
include(GNUInstallDirs)

# 引入用于生成CMake Config文件命令
include(CMakePackageConfigHelpers)

add_subdirectory(src)
add_subdirectory(test)
