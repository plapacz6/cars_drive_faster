#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "T_GameImages.h"



using namespace std;
using namespace cv;
namespace csfgame {

#include "assets/bush.h"
#include "assets/car1.h"
#include "assets/car2.h"
#include "assets/hole.h"
#include "assets/lane.h"
#include "assets/line_dotted.h"
#include "assets/roadside.h"

T_GameImages::T_GameImages() {  
    imagesArrays.push_back(make_tuple(&img_bush, bush_png, bush_png_len));
    imagesArrays.push_back(make_tuple(&img_car1, car1_png, car1_png_len));
    imagesArrays.push_back(make_tuple(&img_car2, car2_png, car2_png_len));
    imagesArrays.push_back(make_tuple(&img_hole, hole_png, hole_png_len));
    imagesArrays.push_back(make_tuple(&img_lane, lane_png, lane_png_len));
    imagesArrays.push_back(make_tuple(&img_lane_dotted, line_dotted_png, line_dotted_png_len));
    imagesArrays.push_back(make_tuple(&img_lane_dotted, roadside_png, roadside_png_len));
    load_images();
}

//T_GameImages::~T_GameImages() override { }

//setters and getters:
//void T_GameImages::set_(TTT) { }
//TTT T_GameImages::get_() const { }

void T_GameImages::load_images() {

    try {
        // img_roadside = imread("roadside.jpg");
        // img_lane = imread("lane.jpg");
        // img_car1 = imread("car1.jpg");
        // img_car2 = imread("car2.jpg");
        // img_hole = imread("hole.jpg");
        // img_bush = imread("bush.png");
        // img_lane_dotted = imread("line_dotted.jpg");
        for(auto [imgMat, dataBufor, dataLength] : imagesArrays) 
        {            
            cv::Mat data = cv::Mat(1, dataLength, CV_8UC1, (void*)dataBufor);
            *imgMat = cv::imdecode(data, cv::IMREAD_COLOR);    
            if(imgMat->empty()) {
                throw;
            }
        }
        // if(img_roadside.empty()
        //         || img_lane.empty()
        //         || img_car1.empty()
        //         || img_car2.empty()
        //         || img_hole.empty()
        //         || img_bush.empty()
        //   ) {
        //     throw;
        // }
    }
    catch(...) {
        cerr << "road_t - exception" << endl;
        exit(EXIT_FAILURE);
    }
}

T_GameImages game_images;

} //namespace csfgame
