# CMakeList.txt : CMake project for DGravity, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

# Enable Hot Reload if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>")
endif()

set(NAME "DGravity")

project (${NAME})

add_executable (${NAME} "main.cpp")
target_include_directories(${NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/DGravity")

# deps

set (DEPS "${PROJECT_SOURCE_DIR}/deps")

set (SDL2_INCLUDE "${DEPS}/SDL2/include")
set (SDL2_LIB "${DEPS}/SDL2/lib")

set (IMGUI_INCLUDE "${DEPS}/imgui/include")
set (IMGUI_LIB "${DEPS}/imgui/lib")

add_custom_command(
        TARGET ${NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SDL2_LIB}/SDL2.dll
                ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll)

target_include_directories (
    ${NAME} PUBLIC ${SDL2_INCLUDE}
    ${NAME} PUBLIC ${IMGUI_INCLUDE}
)

target_link_libraries (${NAME} 
    ${SDL2_LIB}/SDL2.lib ${SDL2_LIB}/SDL2main.lib ${SDL2_LIB}/SDL2gfx.lib ${SDL2_LIB}/SDL2_ttf.lib
    ${IMGUI_LIB}/imgui.lib ${IMGUI_LIB}/imgui_sdl.lib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
