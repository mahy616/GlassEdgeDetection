#ifndef __CONFIGSETTING__
#define __CONFIGSETTING__
#include "find_contour.h"

const int X_LENGTH = 2048;
const int Y_LENGTH = 6500;
namespace smartmore
{
    std::vector<int> GenerateRange(int begin, int end, int step)
    {
        std::vector<int> vec_range;
        for (int i = begin; i < end; i += step)
        {
            vec_range.push_back(i);
        }
        return vec_range;
    }
} // namespace smartmore
//变量名称的first, proceed,  last 表示图片的顺序
//变量名称的left right表示玻璃在左边和右边

/*======================= 玻璃在左边  =================================*/

//第一张找上边缘线（玻璃在左边） 中间图也用这个
const smartmore::EdgeConfig x_edge1_first_left_config{
    smartmore::GenerateRange(0, 500, 10),
    {0, Y_LENGTH},
    -10,
    "first",
    0,
    100};

//第一张找右边缘线（玻璃在左边）
const smartmore::EdgeConfig y_edge1_first_left_config{
    {0, X_LENGTH},
    smartmore::GenerateRange(Y_LENGTH - 3000, Y_LENGTH, 10),
    -10,
    "last",
    0,
    100};

//中间图找右边缘线（中间图）（玻璃在左边）
const smartmore::EdgeConfig y_edge_proceed_left_config{
    {0, X_LENGTH},
    smartmore::GenerateRange(0, Y_LENGTH, 10),
    10,
    "last",
    0,
    100};

//最后一张找下边缘线（玻璃在左边）
const smartmore::EdgeConfig x_edge2_last_left_config{
    smartmore::GenerateRange(0, 500, 10),
    {0, Y_LENGTH},
    10,
    "first",
    0,
    100};

//最后一张图找右边缘线（最后一张图）（玻璃在左边）
const smartmore::EdgeConfig y_edge2_last_left_config{
    {0, X_LENGTH},
    smartmore::GenerateRange(0, 3000, 10),
    10,
    "last",
    0,
    100};

/*======================= 玻璃在右边  =================================*/

// 第一张图找上边缘线（玻璃在右边）中间图也用这个
const smartmore::EdgeConfig x_edge1_first_right_config{
    smartmore::GenerateRange(X_LENGTH - 500, X_LENGTH, 10),
    {0, Y_LENGTH},
    10,
    "first",
    0,
    100};

//第一张图片找左边缘线（玻璃在右边）
const smartmore::EdgeConfig y_edge1_first_right_config{
    {0, X_LENGTH},
    smartmore::GenerateRange(Y_LENGTH - 3000, Y_LENGTH, 10),
    10,
    "last",
    0,
    100};

// 中间一张图片找左边缘线（玻璃在右边）
const smartmore::EdgeConfig y_edge_proceed_right_config{
    {0, X_LENGTH},
    smartmore::GenerateRange(0, Y_LENGTH, 10),
    10,
    "last",
    0,
    100};

//最后一张图片找左边缘线（玻璃在右边）
const smartmore::EdgeConfig y_edge2_last_right_config{
    {0, X_LENGTH},
    smartmore::GenerateRange(0, 3000, 10),
    10,
    "last",
    0,
    100};

// 最后一张图找下边缘线（玻璃在右边）
const smartmore::EdgeConfig x_edge2_last_right_config{
    smartmore::GenerateRange(0, X_LENGTH, 10),
    {0, Y_LENGTH},
    -10,
    "first",
    0,
    100};

#endif