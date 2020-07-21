cmake_minimum_required(VERSION "3.18.0-rc1")

set("OpenCV_DIR" "C:/opencv/build")
set("Eigen_SOURCE_DIR" "C:/eigen-3.3.7/eigen-3.3.7")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project("Chapter-4")

find_package(OpenCV REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)


include_directories("${OpenCV_INCLUDE_DIRS}")
include_directories("Eigen3_INCLUDE_DIR")

file(GLOB SOURCES "*.cpp" "*.h")

add_executable("${PROJECT_NAME}" ${SOURCES})

target_link_libraries("${PROJECT_NAME}" PRIVATE "${OpenCV_LIBS}")
target_link_libraries("${PROJECT_NAME}" PRIVATE Eigen3::Eigen)

install(TARGETS "${PROJECT_NAME}" DESTINATION "${PROJECT_SOURCE_DIR}/bin")
install(FILES "main_header.h" "Section_4_9_H_.h" "Section_4_10_H_.h" DESTINATION "${PROJECT_SOURCE_DIR}/include")