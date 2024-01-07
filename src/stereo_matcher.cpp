#include "camera_driver.hpp"
#include "stereo_matcher.hpp"

int main( int argc, char const *argv[] )
{
  vision::CameraDriver camera;
  camera.open( 0 );
  cv::Mat frame_left;
  cv::Mat frame_right;
  camera.getStereoFrame( frame_left, frame_right );
  cv::imshow( "frame_left", frame_left );
  cv::imshow( "frame_right", frame_right );

  vision::StereoMatcher stereo_matcher;
  stereo_matcher.initializeSGBM();
  cv::Mat frame_disparity;
  stereo_matcher.getDisparity( frame_left, frame_right, frame_disparity );
  cv::imshow( "frame_disparity", frame_disparity );

  stereo_matcher.showDisparity( frame_disparity );


  return 0;
}