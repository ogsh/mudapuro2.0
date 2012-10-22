#ifndef __COMMON__
#define __COMMON__

#include <opencv2/opencv.hpp>

#ifdef _DEBUG
    //Debugモードの場合
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Debug\\opencv_core220d.lib")            // opencv_core
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Debug\\opencv_imgproc220d.lib")        // opencv_imgproc
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Debug\\opencv_highgui220d.lib")        // opencv_highgui
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Debug\\opencv_objdetect220d.lib")    // opencv_objdetect
    //以下、必要に応じて追加
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Debug\\opencv_ml220d.lib")            // opencv_ml
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Debug\\opencv_features2d220d.lib")    // opencv_features2d
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Debug\\opencv_video220d.lib")        // opencv_video
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Debug\\opencv_calib3d220d.lib")        // opencv_calib3d
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Debug\\opencv_flann220d.lib")        // opencv_flann
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Debug\\opencv_contrib220d.lib")        // opencv_contrib
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Debug\\opencv_legacy220d.lib")        // opencv_legacy
    //#pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\opencv_gpu220d.lib")            // opencv_gpu

#else
    //Releaseモードの場合
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Release\\opencv_core220.lib")            // opencv_core
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Release\\opencv_imgproc220.lib")        // opencv_imgproc
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Release\\opencv_highgui220.lib")        // opencv_highgui
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Release\\opencv_objdetect220.lib")    // opencv_objdetect
    //以下、必要に応じて追加
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Release\\opencv_ml220.lib")            // opencv_ml
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Release\\opencv_features2d220.lib")    // opencv_features2d
    #pragma comment(lib,"C:\\OpenCV2.2\\vc10\\lib\\Release\\opencv_video220.lib")        // opencv_video
    //#pragma comment(lib,"C:\\OpenCV2.2vc10\\\\lib\\Release\\opencv_calib3d220.lib")        // opencv_calib3d
    //#pragma comment(lib,"C:\\OpenCV2.2vc10\\\\lib\\Release\\opencv_flann220.lib")        // opencv_flann
    //#pragma comment(lib,"C:\\OpenCV2.2vc10\\\\lib\\Release\\opencv_contrib220.lib")        // opencv_contrib
    //#pragma comment(lib,"C:\\OpenCV2.2vc10\\\\lib\\Release\\opencv_legacy220.lib")        // opencv_legacy
    //#pragma comment(lib,"C:\\OpenCV2.2vc10\\\\lib\\Release\\opencv_gpu220.lib")            // opencv_gpu
#endif
#pragma comment(lib,"C:/OpenNI/Lib/openNI.lib")
#endif