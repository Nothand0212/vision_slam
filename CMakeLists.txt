cmake_minimum_required(VERSION 3.15)

project(vision_tools)

find_package(OpenCV REQUIRED QUIET)

include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
)

link_libraries(
    ${OpenCV_LIBS}
)

link_directories(
    ${OpenCV_LIBRARY_DIRS}
)


add_executable(camera_driver src/camera_driver.cpp)
target_link_libraries(camera_driver ${OpenCV_LIBS})

# add_executable(stereo_matcher src/stereo_matcher.cpp)
# target_link_libraries(stereo_matcher ${OpenCV_LIBS})

add_executable(camera_calibrator src/camera_calibrator.cpp)
target_link_libraries(camera_calibrator ${OpenCV_LIBS})