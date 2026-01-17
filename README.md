这是一个可以在RK3588上运行的yolo26-demo项目，项目自带有量化后的官方模型可以进行测试使用。

转换及python推理代码见：https://github.com/li2390893/yolo26-rk3588-python.git

详细讲解视频，B站搜索：橘子搞AI视觉
【【已开源】YOLO26在RK3588上部署详解】 https://www.bilibili.com/video/BV1gNr4BFEZP

20260117说明
更新原始模型推理后处理内容，更新librknnrt.so版本。
此处发现如果使用2.2.0版本的so包会导致堆栈错误，现在将包更新至2.3.2。
上传原始结构的n、s模型的量化、非量化rknn模型提供测试使用。
但是原始结构的n、s模型的量化模型都无法正常推理出结果，此问题待解决。

编译
```
cmake -S . -B build
cmake --build build
```

运行
```
./build/yolo26_img ./weights/yolo26s.int.rknn ./images/bus.jpg
```
yolo26_imgs和yolo26_video请自行探索