#include <opencv2/opencv.hpp>

class CameraCalibrator
{
private:
  std::vector<std::vector<cv::Point2f>> image_points;
  std::vector<std::vector<cv::Point3f>> object_points;
  cv::Size                              image_size;
  cv::Mat                               cameraMatrix, distCoeffs;
  std::vector<cv::Mat>                  rvecs, tvecs;

public:
  CameraCalibrator( cv::Size board_size, cv::Size image_size ) : image_size( image_size )
  {
    // 初始化棋盘格的3D点
    std::vector<cv::Point3f> objectCorners;
    for ( int i = 0; i < boardSize.height; i++ )
    {
      for ( int j = 0; j < boardSize.width; j++ )
      {
        objectCorners.push_back( cv::Point3f( j, i, 0.0f ) );
      }
    }
    objectPoints.push_back( objectCorners );
  }

  bool addImage( cv::Mat image )
  {
    std::vector<cv::Point2f> imageCorners;
    bool                     found = cv::findChessboardCorners( image, cv::Size( object_points[ 0 ].size() ), imageCorners );
    if ( found )
    {
      image_points.push_back( imageCorners );
    }
    return found;
  }

  void calibrate()
  {
    cv::calibrateCamera( object_points, image_points, image_size, cameraMatrix, distCoeffs, rvecs, tvecs );
  }

  cv::Mat getCameraMatrix()
  {
    return cameraMatrix;
  }

  cv::Mat getDistCoeffs()
  {
    return distCoeffs;
  }
};