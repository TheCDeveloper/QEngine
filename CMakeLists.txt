cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)




# --- Project properties ---
project(QEngine)

include_directories(include)
link_directories(libraries)

add_compile_options(-Wall -Wextra -pedantic)


set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "-g")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -flto -funroll-loops -fno-exceptions")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-s")


# --- Dependencies ---
find_package(SDL3 REQUIRED CONFIG)
find_package(OpenGL REQUIRED)




# --- QEngine Core ---
file(GLOB QENGINE_CORE_SOURCE src/Core/*.cpp src/Renderer/*.cpp)
add_library(QEngineCore SHARED ${QENGINE_CORE_SOURCE})
target_link_libraries(QEngineCore PRIVATE SDL3::SDL3)


# --- OpenGLRenderer ---
file(GLOB OPENGLRENDERER_SOURCE src/Renderer/OpenGL/*.cpp)
add_library(
    OpenGLRenderer SHARED
    ${OPENGLRENDERER_SOURCE} 
    src/Renderer/OpenGL/glad/gl.c
)
target_link_libraries(OpenGLRenderer PRIVATE QEngineCore SDL3::SDL3 OpenGL::GL)


# --- RendererCore ---
file(
    GLOB
    RENDERER_CORE_SOURCE
    src/Renderer/Core/*.cpp
    src/Renderer/Core/GLAPI/*.cpp
)
add_library(
    RendererCore SHARED
    ${RENDERER_CORE_SOURCE} 
    src/Renderer/OpenGL/glad/gl.c
)
target_link_libraries(RendererCore PRIVATE QEngineCore SDL3::SDL3 OpenGL::GL)

