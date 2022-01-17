/*
 * @Description: 
 * @Version: 1.0
 * @Autor: zhenkun.yu
 * @Date: 2021-06-02 14:54:34
 * @LastEditors: zhenkun.yu
 * @LastEditTime: 2021-06-02 21:25:16
 */
#ifndef _BASE_IMPL_H_
#define _BASE_IMPL_H_

#include <opencv2/opencv.hpp>
#include <vector>
#include "Common.h"

namespace smartmore
{
    class IBaseImpl
    {
    public:
        IBaseImpl() = default;
        virtual ~IBaseImpl() = default;

    public:
        virtual ResultCode Init(std::string &model_data, const int labelCount, const bool USE_GPU, const int device_id) = 0;

        virtual ResultCode Do(const cv::Mat &input, const std::vector<float> &thresholds, cv::Mat &mask) = 0;
    };

} // namespace smartmore

#endif