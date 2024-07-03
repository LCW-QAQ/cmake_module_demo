aux_source_directory(. SRC_FILES)

add_library(Core ${SRC_FILES})
add_library(${PROJECT_NAME}::Core ALIAS Core)
set_target_properties(Core
	PROPERTIES
	VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
  # 修改库名称
	OUTPUT_NAME ${PROJECT_NAME}Core
	DEFINE_SYMBOL Core_EXPORTS
)

# 使用这种方式会导致安装${PROJECT_NAME}Targets.cmake对象文件时错误
# target_include_directories(${PROJECT_NAME} PUBLIC
#   ${PROJECT_SOURCE_DIR}/include
# )

target_include_directories(Core
PUBLIC
    # 在构建时引入的头文件目录
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    # 安装时引入的头文件目录
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

CMKMOD_INSTALL(Core)
CMKMOD_GENERATE_PACKAGE(Core)

# 拷贝license
# install(
#     FILES ${PROJECT_SOURCE_DIR}/LICENSE.md
#     DESTINATION ${CMAKE_INSTALL_DOCDIR}
# )

## CMake config file
# set(CMAKE_CONFIG_DEPS "find_dependency(Threads)\n")
# if(WITH_LIBCURL)
#     string(APPEND CMAKE_CONFIG_DEPS "find_dependency(CURL)\n")
# endif()
# if(WITH_LIBCURL OR WITH_OPENSSL)
#     string(APPEND CMAKE_CONFIG_DEPS "find_dependency(OpenSSL 1.1.0)\n")
# endif()

# export(
#     EXPORT ${PROJECT_NAME}Export
#     NAMESPACE ${PROJECT_NAME}::
#     FILE ${PROJECT_NAME}Targets.cmake
# )

# 上面target_include_directories命令如果不使用生成器表达式，就会导致下面的问题。
# 产生错误：Target "cmkmod" INTERFACE_INCLUDE_DIRECTORIES property contains path。
# 原因是：target_include_directories命令和第二个install命令产生了冲突。
# target_include_directories命令其实就是给库设置了属性 INTERFCE_INCLUDE_DERECTORIES。
# 即库在构建和安装时配置信息中都会包含target_include_directories命令中的路径。
# 而在下面的install中，${PROJECT_NAME}Targets.cmake为该库导出的对象文件，该对象文件会包含Message的配置相关信息。
# 再指定该对象文件的安装DESITNATION会和target_include_directories中的设置冲突。
# 安装该导出文件又必须指定DESTINATION，此时注释下面的install可以避免错误，但是这样就无法安装目标cmake文件了。
# 完美的解决方案是在target_include_directories命令处，使用生成器表达式，分别指定构建时、安装时的头文件路径。
# install(
#     EXPORT ${PROJECT_NAME}Export
#     NAMESPACE ${PROJECT_NAME}::
#     FILE ${PROJECT_NAME}Targets.cmake
#     DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
# )

# install(
#     FILES
#         ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
#         ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
#     DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
# )

# export(PACKAGE ${PROJECT_NAME})