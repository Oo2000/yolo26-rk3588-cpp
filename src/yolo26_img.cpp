#undef LOG_TAG
#define LOG_TAG "yolo26_img"

#include <opencv2/opencv.hpp>

#include "task/yolo26.h"
#include "utils/logging.h"
#include "draw/cv_draw.h"


int main(int argc, char **argv)
{
    Yolo26 yolo;
    // model file path
    const char *model_file = argv[1];
    // input img path
    const char *img_file = argv[2];
    // load image
    cv::Mat img = cv::imread(img_file);

    // 打印图片的尺寸
    NN_LOG_INFO("Image size: %d x %d", img.cols, img.rows);

    // load model file
    yolo.LoadModel(model_file);

    std::vector<Detection> objects;
    yolo.Run(img, objects);
    DrawDetections(img, objects);
    
    cv::imwrite("result.jpg", img);

    return 0;
}