cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 14)

project(stl2thumbnail)

add_subdirectory(libstl)

set(CMAKE_INCLUDE_CURRENT_DIR true)

find_package(PNG REQUIRED)

include_directories(${PNG_INCLUDE_DIR} libstl)

add_executable (
    ${PROJECT_NAME}
    "main.cpp"
    "picture.cpp"
    "picture.h"
    "aabb.cpp"
    "aabb.h"
    "vec3.h"
    "vec4.h"
    "triangle.h"
    "backends/backend.h"
    "backends/raster/backend.cpp"
    "backends/raster/backend.h"
    "backends/raster/zbuffer.cpp"
    "backends/raster/zbuffer.h"

    # 3rd party
    "args.hxx"
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/dist/linux/stl.thumbnailer
                ${CMAKE_CURRENT_BINARY_DIR}/stl.thumbnailer
)

target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARY} stl)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "bin")
install(FILES "dist/linux/stl.thumbnailer" DESTINATION "share/thumbnailers")
