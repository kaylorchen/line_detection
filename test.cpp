#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
  const cv::Mat K = (cv::Mat_<double>(3, 3)
      << 518.5206194361012, 0.0, 932.0926791943779, 0.0, 518.0241546073428, 507.22695301062527, 0.0, 0.0, 1.0);
  const cv::Mat D = (cv::Mat_<double>(4, 1)
      << -0.09556402717747697, 0.012374049436718767, -0.010465758469831311, 0.0033159128053917544);

  const string str = "../fisheye.jpg";
  const int ImgWidth = 1920;
  const int ImgHeight = 1080;

  cv::Mat map1, map2;
  cv::Size imageSize(ImgWidth, ImgHeight);
  const double alpha = 1;
  cv::Mat NewCameraMatrix = getOptimalNewCameraMatrix(K, D, imageSize, alpha, imageSize, 0);
  initUndistortRectifyMap(K, D, cv::Mat(), NewCameraMatrix, imageSize, CV_16SC2, map1, map2);


    cv::Mat RawImage = cv::imread(str);
    cv::imshow("RawImage", RawImage);

    cv::Mat UndistortImage;
    remap(RawImage, UndistortImage, map1, map2, cv::INTER_LINEAR);
    cv::imshow("UndistortImage", UndistortImage);

    string OutputPath = str + to_string(i) + "_un" + ".png";
    cv::imwrite(OutputPath, UndistortImage);
    cv::waitKey(0);


  return 0;
}


//  cv::Mat input_frame = cv::imread("../fisheye.jpg");
//
//  cv::Size size = {input_frame.cols, input_frame.rows};
//
//  cv::Mat map1;
//  cv::Mat map2;
//  //cv::fisheye::undistortImage(input_frame,output_frame,cameraMatrix,distortionCoeffs, E, cv::Size(input_frame.cols,input_frame.rows));
//
//  cv::fisheye::initUndistortRectifyMap(K, D, E, K, size, CV_16SC2, map1, map2);
//
//  cv::Mat undistort;
//
//  cv::remap(input_frame, undistort, map1, map2, cv::INTER_LINEAR,
//            CV_HAL_BORDER_CONSTANT);
//
//  cv::imshow("Input Image", input_frame);
//  cv::imshow("Output Image", undistort);
//  cv::waitKey(-1);