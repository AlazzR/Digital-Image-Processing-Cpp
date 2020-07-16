# Install script for directory: C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/CHAPTER-3")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/bin/CHAPTER-3.exe")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/bin" TYPE EXECUTABLE FILES "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/build/Debug/CHAPTER-3.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/bin/CHAPTER-3.exe")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/bin" TYPE EXECUTABLE FILES "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/build/Release/CHAPTER-3.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/bin/CHAPTER-3.exe")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/bin" TYPE EXECUTABLE FILES "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/build/MinSizeRel/CHAPTER-3.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/bin/CHAPTER-3.exe")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/bin" TYPE EXECUTABLE FILES "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/build/RelWithDebInfo/CHAPTER-3.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/main_header.h;C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_2.h;C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_3.h;C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_5.h;C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_6.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include" TYPE FILE FILES
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/main_header.h"
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/Section_3_2.h"
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/Section_3_3.h"
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/Section_3_5.h"
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/Section_3_6.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_2/Section_3_2_src.cpp;C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_2/Section_3_2.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_2" TYPE FILE FILES
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/Section_3_2_src.cpp"
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/Section_3_2.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_3/Section_3_3_src.cpp;C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_3/Section_3_3.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_3" TYPE FILE FILES
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/Section_3_3_src.cpp"
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/Section_3_3.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_5/Section_3_5_src.cpp;C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_5/Section_3_5.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_5" TYPE FILE FILES
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/Section_3_5_src.cpp"
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/Section_3_5.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_6/Section_3_6_src.cpp;C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_6/Section_3_6.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/include/Section_3_6" TYPE FILE FILES
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/Section_3_6_src.cpp"
    "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/Section_3_6.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/USER/Desktop/C++_Codes/OpenCV_Projects/Chapter_3_Intensity_Transformation_and_Spatial_Filtering/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
