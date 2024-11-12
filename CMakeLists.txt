# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(tinyshader VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加编译标志
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(EIGEN3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/eigen")

set(OBJECTS_LOADER_DIR "${CMAKE_SOURCE_DIR}/include/tiny_obj_loader")


message(STATUS "Eigen3 include dir: ${EIGEN3_INCLUDE_DIR}")

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${OBJECTS_LOADER_DIR})

# 递归查找所有 .cpp 源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 创建目标文件（可执行文件）
add_executable(${PROJECT_NAME} ${SOURCES})

# 链接数学库
target_link_libraries(${PROJECT_NAME} m)


target_link_libraries(tinyshader 
    kernel32
    user32
    gdi32
    winspool
    shell32
    ole32
    oleaut32
    uuid
    comdlg32
    advapi32
)

# 自定义的清理操作
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_BINARY_DIR}/*.o
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_BINARY_DIR}/*.tga
)

# 设置输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)



