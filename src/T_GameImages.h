#ifndef T_GAMEIMAGES_H
#define T_GAMEIMAGES_H

#include <T_Rect.h>

namespace csfgame {

//class game_images_t {
class T_GameImages {
public:
    explicit T_GameImages();
    T_GameImages(const  T_GameImages&) = delete;
    virtual ~T_GameImages() = default;
    T_GameImages& operator=(const T_GameImages&) = delete;

    //setters and getters:
    //void set_(TTT);
    //TTT get_() const;

    cv::Mat img_roadside;
    cv::Mat img_lane;
    cv::Mat img_car1;
    cv::Mat img_car2;
    cv::Mat img_hole;
    cv::Mat img_bush;
    cv::Mat img_lane_dotted;

    std::vector<std::tuple<cv::Mat*, unsigned char*, unsigned int>> imagesArrays;

    void load_images();

protected:
private:
};

extern T_GameImages game_images;
} //namespace csfgame
#endif //T_GAMEIMAGES_H

