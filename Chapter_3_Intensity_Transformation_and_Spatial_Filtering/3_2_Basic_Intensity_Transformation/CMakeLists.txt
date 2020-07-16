#This folder will include the implementation for section 3.2
#Willn't be used due to limitation to path name length
set("OpenCV_DIR" "C:/opencv/build")

find_package(OpenCV REQUIRED)

include_directories("${OpenCV_INCLUDE_DIRS}")

add_library("3-2_Basic_Intensity_Transformation" STATIC "image_negative.cpp" "Section_3_2.h")


target_link_libraries("3-2_Basic_Intensity_Transformation" PRIVATE "${OpenCV_LIBS}")
target_include_directories("3-2_Basic_Intensity_Transformation" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")


target_compile_definitions("3-2_Basic_Intensity_Transformation" PUBLIC Section_3_2="Implementation of some algorithms in Section 3.2")