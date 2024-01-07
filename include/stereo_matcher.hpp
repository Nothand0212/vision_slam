#include <iostream>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>

namespace vision
{
class StereoMatcher
{
private:
  cv::Mat frame_left;
  cv::Mat frame_right;
  cv::Mat frame_disparity;
  cv::Mat frame_showed;

  cv::Ptr<cv::StereoSGBM> matcher;

public:
  StereoMatcher( /* args */ );
  ~StereoMatcher();
  // void initializeGC();
  void initializeSGBM();
  void getDisparity( const cv::Mat &frame_left, const cv::Mat &frame_right, cv::Mat &frame_disparity );
  void showDisparity( const cv::Mat &frame_disparity );
};

StereoMatcher::StereoMatcher( /* args */ )
{
}

StereoMatcher::~StereoMatcher()
{
}

void StereoMatcher::initializeSGBM()
{
  matcher = cv::StereoSGBM::create();
  matcher->setPreFilterCap( 63 );

  int sad_window_size = 11;
  int cn              = 1;

  matcher->setSpeckleWindowSize( sad_window_size > 0 ? sad_window_size : 3 );
  matcher->setP1( 4 * cn * matcher->getSpeckleWindowSize() * matcher->getSpeckleWindowSize() );
  matcher->setP2( 32 * cn * matcher->getSpeckleWindowSize() * matcher->getSpeckleWindowSize() );

  matcher->setMinDisparity( 0 );
  matcher->setNumDisparities( 32 );
  matcher->setUniquenessRatio( 10 );
  matcher->setSpeckleWindowSize( 100 );
  matcher->setSpeckleRange( 32 );
  matcher->setDisp12MaxDiff( 1 );
}

void StereoMatcher::getDisparity( const cv::Mat &frame_left, const cv::Mat &frame_right, cv::Mat &frame_disparity )
{
  matcher->compute( frame_left, frame_right, frame_disparity );
}

void StereoMatcher::showDisparity( const cv::Mat &frame_disparity )
{
  double min_value, max_value;

  cv::minMaxLoc( frame_disparity, &min_value, &max_value );
  cv::Mat frame_disparity_normalized;
  frame_disparity.convertTo( frame_disparity_normalized, CV_8UC1, 255 / ( max_value - min_value ) );

  cv::imshow( "Disparity", frame_disparity_normalized );
  cv::waitKey( 0 );
}

}  // namespace vision
