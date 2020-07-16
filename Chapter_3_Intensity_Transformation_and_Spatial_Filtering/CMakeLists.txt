cmake_minimum_required(VERSION "3.18.0-rc1")

set("OpenCV_DIR" "C:/opencv/build")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)



project(CHAPTER-3)

#add_subdirectory("${PROJECT_SOURCE_DIR}/3_2_Basic_Intensity_Transformation")

find_package(OpenCV REQUIRED)

include_directories("${OpenCV_INCLUDE_DIRS}")

file(GLOB SOURCES "*.cpp" "*.h")
 
add_executable("${PROJECT_NAME}" ${SOURCES})

target_link_libraries("${PROJECT_NAME}" PRIVATE "${OpenCV_LIBS}")
#target_link_libraries("${PROJECT_NAME}" PUBLIC "3-2_Basic_Intensity_Transformation")

install(TARGETS "${PROJECT_NAME}" DESTINATION "${PROJECT_SOURCE_DIR}/bin")
install(FILES "main_header.h" "Section_3_2.h" "Section_3_3.h" "Section_3_5.h" "Section_3_6.h" DESTINATION "${PROJECT_SOURCE_DIR}/include")

install(FILES "Section_3_2_src.cpp" "Section_3_2.h" DESTINATION "${PROJECT_SOURCE_DIR}/include/Section_3_2")
install(FILES "Section_3_3_src.cpp" "Section_3_3.h" DESTINATION "${PROJECT_SOURCE_DIR}/include/Section_3_3")
install(FILES "Section_3_5_src.cpp" "Section_3_5.h" DESTINATION "${PROJECT_SOURCE_DIR}/include/Section_3_5")
install(FILES "Section_3_6_src.cpp" "Section_3_6.h" DESTINATION "${PROJECT_SOURCE_DIR}/include/Section_3_6")