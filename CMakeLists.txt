cmake_minimum_required(VERSION 3.5)

project(app)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_QMAKE_EXECUTABLE ${PROJECT_NAME})

file(GLOB SOURCES "*.cpp")
#source_group(HEADERS FILES "*.h")

find_package(PkgConfig REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(DtkWidget REQUIRED)

pkg_check_modules(DtkCore REQUIRED dtkcore)
pkg_check_modules(DtkWidget REQUIRED dtkwidget)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${DtkCore_INCLUDE_DIRS}
    ${DtkWidget_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME}
    ${DtkCore_LIBRARIES}
    ${DtkWidget_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
)

# 构建处理配置文件 从源目录复制到构建目录
file(COPY ${CMAKE_SOURCE_DIR}/config.json DESTINATION ${CMAKE_BINARY_DIR})
