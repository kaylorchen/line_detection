#include <iostream>
#include "opencv2/opencv.hpp"
using namespace cv;

int main() {
  cv::VideoCapture capture("/dev/video0");
  capture.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
  capture.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
  capture.set(cv::CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
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
    cv::imshow("image", frame);
    cv::waitKey(1);
  }
  return 0;
}
