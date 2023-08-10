#include <iostream>
#include "opencv2/opencv.hpp"

const cv::Mat K = (cv::Mat_<double>(3, 3)
    << 518.5206194361012, 0.0, 932.0926791943779, 0.0, 518.0241546073428, 507.22695301062527, 0.0, 0.0, 1.0);
const cv::Mat D = (cv::Mat_<double>(4, 1)
    << -0.09556402717747697, 0.012374049436718767, -0.010465758469831311, 0.0033159128053917544);
const cv::Mat E = cv::Mat::eye(3, 3, cv::DataType<double>::type);
const int k_img_width = 1920;
const int k_img_height = 1080;
const int k_balance = 0;

int main() {
  cv::Mat map1, map2;
  cv::Size image_size(k_img_width,k_img_height);
  cv::Mat new_K;
  cv::fisheye::estimateNewCameraMatrixForUndistortRectify(K, D, image_size,E, new_K, k_balance);
//  cv::fisheye::initUndistortRectifyMap(K, D, E, new_K, image_size, CV_16SC2, map1, map2);
  std::cout << "size: " << image_size<< std::endl;
  std::cout << "K" << K << std::endl;
  std::cout << "new_K" << new_K << std::endl;
  cv::VideoCapture capture("/dev/video0");
  capture.set(cv::CAP_PROP_FRAME_WIDTH, k_img_width);
  capture.set(cv::CAP_PROP_FRAME_HEIGHT, k_img_height);
  capture.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
  // capture.set(cv::CAP_PROP_FPS, 30);//帧数

  //capture.set(cv::CAP_PROP_BRIGHTNESS, 1);//亮度 50
  //capture.set(cv::CAP_PROP_CONTRAST, 40);//对比度 50
  //capture.set(cv::CAP_PROP_SATURATION, 50);//饱和度 50
  //capture.set(cv::CAP_PROP_HUE, 50);//色调 0
  //capture.set(cv::CAP_PROP_EXPOSURE, 50);//曝光 -12
  //打印摄像头参数
  printf("width = %.2f\n", capture.get(cv::CAP_PROP_FRAME_WIDTH));
  printf("height = %.2f\n", capture.get(cv::CAP_PROP_FRAME_HEIGHT));
  printf("fbs = %.2f\n", capture.get(cv::CAP_PROP_FPS));
  printf("brightness = %.2f\n", capture.get(cv::CAP_PROP_BRIGHTNESS));
  printf("contrast = %.2f\n", capture.get(cv::CAP_PROP_CONTRAST));
  printf("saturation = %.2f\n", capture.get(cv::CAP_PROP_SATURATION));
  printf("hue = %.2f\n", capture.get(cv::CAP_PROP_HUE));
  printf("exposure = %.2f\n", capture.get(cv::CAP_PROP_EXPOSURE));

  while (true){
    cv::Mat frame;
    capture >> frame;
    cv::Mat UndistortedImage;
//    remap(frame, UndistortedImage, map1, map2, cv::INTER_LINEAR, CV_HAL_BORDER_CONSTANT);
    cv::fisheye::undistortImage(frame, UndistortedImage, K, D, new_K, frame.size());
    cv::imshow("original", frame);
    cv::imshow("image", UndistortedImage);
    cv::waitKey(1);
  }
  return 0;
}
