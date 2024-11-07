cmake_minimum_required(VERSION 3.22)

project(fluids3 LANGUAGES C CXX CUDA)

find_package(CUDAToolkit REQUIRED)

# GLAD
if(NOT IS_DIRECTORY "${CMAKE_CURRENT_BINRAY_DIR}/common/glad")
    file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_LIST_DIR}/common/glad.tgz" DESTINATION "common")
endif()
if(WIN32)
    set(GLAD_SOURCES
        common/glad/include/glad/gl.h
        common/glad/include/glad/wgl.h
        common/glad/src/gl.c
        common/glad/src/wgl.c
    )
elseif(UNIX AND NOT APPLE)
    set(GLAD_SOURCES
        common/glad/include/glad/gl.h
        common/glad/include/glad/glx.h
        common/glad/src/gl.c
        common/glad/src/glx.c
    )
else()
    message(FATAL "-- Apple platform series not supported")
endif()

add_library(
    glad
    ${GLAD_SOURCES}
)
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/common/glad/include")

# pugi_xml
if(NOT IS_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/common/pugixml-1.14")
    file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_LIST_DIR}/common/pugixml-1.14.tgz" DESTINATION "common")
endif()
add_subdirectory("${CMAKE_CURRENT_BINARY_DIR}/common/pugixml-1.14")

# Fluidv3
set(FLUID_SOURCES
    fluids/fluid_defs.h
    fluids/fluid_system.cpp
    fluids/fluid_system.h
    fluids/fluid_system_host.cu
    fluids/fluid_system_host.cuh
    fluids/fluid_system_kern.cu
    fluids/fluid_system_kern.cuh

    main.cpp

    common/app_perf.cpp
    common/app_util.cpp
    common/xml_settings.cpp
)

if(WIN32)
    add_executable(${PROJECT_NAME}
        WIN32
        ${FLUID_SOURCES}
    )
else()
    add_executable(${PROJECT_NAME}
        ${FLUID_SOURCES}
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE 
    "./"
    "fluids"
    "common"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE "LOG_NUM_BANKS=5" "BUILD_CUDA=1" "UNICODE")

target_link_libraries(${PROJECT_NAME} PRIVATE
    pugixml::pugixml
    CUDA::cudart
    glad
    opengl32
)

