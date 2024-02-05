#ifndef PASTEIMGFUNCTIONS_H
#define PASTEIMGFUNCTIONS_H

#include <opencv2/core.hpp>

using namespace cv;

namespace csfgame {


void paste_img(const Mat& src, const Rect& coord, Mat& dst);

/**
 * @brief pasting a part of the image that may protrude vertically
 * beyond the dimensions of the dst
 *
 * @param src
 * @param coord
 * @param dst
 */
void paste_img_vert_partialy(const Mat& src, const Rect& coord, Mat& dst);

/**
 * @brief paste img to borad in vertical wrap mode
 *
 */
void paste_img_vert_wrap(const Mat& src, const Rect& coord, int vert_shift, Mat& dst);

void paste_img_horiz_wrap(const Mat& src, const Rect& coord, int horiz_shift, Mat& dst);

} //namespace csfgame
#endif //PASTEIMGFUNCTIONS_H
