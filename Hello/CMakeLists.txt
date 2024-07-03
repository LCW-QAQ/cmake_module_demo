aux_source_directory(. SRC_FILES)

add_library(Hello ${SRC_FILES})
add_library(${PROJECT_NAME}::Hello ALIAS Hello)
set_target_properties(Hello
	PROPERTIES
	VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
  # 修改库名称
	OUTPUT_NAME ${PROJECT_NAME}Hello
	DEFINE_SYMBOL Hello_EXPORTS
)

target_include_directories(Hello
PUBLIC
    # 在构建时引入的头文件目录
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    # 安装时引入的头文件目录
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

CMKMOD_INSTALL(Hello)
CMKMOD_GENERATE_PACKAGE(Hello)