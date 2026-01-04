cmake_minimum_required(VERSION 3.21)
project(sfml_stars LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src)
find_package(SFML REQUIRED COMPONENTS Graphics Window System)

add_executable(${PROJECT_NAME}
        main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_PATH})

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)

if(APPLE)
    target_link_libraries(${PROJECT_NAME}
            PRIVATE
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
    )
endif()