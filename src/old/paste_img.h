#ifndef PASTE_IMG_H
#define PASTE_IMG_H

#include <opencv2/core.hpp>

void paste_img(const cv::Mat& src, const cv::Rect& coord, cv::Mat& dst);
void paste_img_vert_partialy(const cv::Mat& src, const cv::Rect& coord, cv::Mat& dst);
void paste_img_vert_wrap(const cv::Mat& src, const cv::Rect& coord, int vert_shift, cv::Mat& dst);
void paste_img_horiz_wrap(const cv::Mat& src, const cv::Rect& coord, int horiz_shift, cv::Mat& dst);

#endif // PASTE_IMG_H