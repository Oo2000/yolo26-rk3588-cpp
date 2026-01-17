#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <opencv2/opencv.hpp>

#include "task/yolo26.h"
#include "utils/logging.h"
#include "draw/cv_draw.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include "dirent.h"
#include <unistd.h>

using namespace std;
using namespace std::chrono;

static inline int ReadFiles(const char *dirName, std::vector<std::string> &fileNames)
{
    DIR *pDir = opendir(dirName);
    if (pDir == nullptr)
        return -1;
    struct dirent *pFile = nullptr;
    while ((pFile = readdir(pDir)) != nullptr)
    {
        if (strcmp(pFile->d_name, ".") != 0 && strcmp(pFile->d_name, "..") != 0)
        {
            std::string sName(pFile->d_name);
            fileNames.push_back(sName);
        }
    }
}

bool ifFileExist(const char *model_path)
{
    string filename(model_path);
    ifstream f(filename.c_str());
    return f.good();
}

double __get_us(struct timeval t) { return (t.tv_sec * 1000000 + t.tv_usec); }

/*-------------------------------------------
                  Main Functions
-------------------------------------------*/
int main(int argc, char **argv)
{
    struct timeval start_time, stop_time;
    int ret = 0;
    int loopNums = 10; // 迭代测试次数
    bool bDrawFlag = false;

    // const char* model_name = "./model/yolov5s-640-640.rknn";
    const char *model_file = (char *)argv[1];

    Yolo26 yolo;
    yolo.LoadModel(model_file);

    std::string imgDir = "./data/";
    std::string saveDir = "./outputs/";
    std::vector<std::string> fileNames;
    ReadFiles(imgDir.c_str(), fileNames);

    for (int nIndex = 0; nIndex < fileNames.size(); nIndex++)
    {
        cv::Mat orig_img = cv::imread(imgDir + '/' + fileNames[nIndex], 1);
        if (!orig_img.data)
        {
            printf("cv::imread %s fail!\n", fileNames[nIndex].c_str());
            return -1;
        }
        for (int conNum = 0; conNum < loopNums; conNum++)
        {
            int obj_num = 0;
            std::vector<Detection> objects;
            yolo.Run(orig_img, objects);
            // Draw Objects
            if (bDrawFlag)
            {
                // Draw Objects
                DrawDetections(orig_img, objects);
                imwrite(saveDir + '/' + fileNames[nIndex], orig_img);
            }
        }
    }

    return 0;
}
