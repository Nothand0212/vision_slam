#include "camera_driver.hpp"

int main( int argc, char **argv )
{
  vision::CameraDriver camera;
  camera.loadConfig( "../config/camera.json" );

  camera.initialize();

  cv::Mat frame;
  cv::Mat frame_left;
  cv::Mat frame_right;
  int     frame_count = 0;
  while ( true )
  {
    camera.getStereoFrameUndistorted( frame_left, frame_right );
    cv::imshow( "frame_left", frame_left );
    cv::imshow( "frame_right", frame_right );

    // 保存图像
    int key = cv::waitKey( 10 );
    if ( key == 32 )
    {
      cv::imwrite( "/home/lin/Projects/vision_ws/data/left/" + std::to_string( frame_count ) + ".png", frame_left );
      cv::imwrite( "/home/lin/Projects/vision_ws/data/right/" + std::to_string( frame_count ) + ".png", frame_right );
      frame_count++;
    }
  }

  camera.close();
  return 0;
}