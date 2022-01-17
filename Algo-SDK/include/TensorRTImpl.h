/*
 * @Description: 
 * @Version: 1.0
 * @Autor: zhenkun.yu
 * @Date: 2021-06-02 14:43:17
 * @LastEditors: zhenkun.yu
 * @LastEditTime: 2021-06-02 21:25:02
 */
#ifndef _TENSORRT_IMPL_H_
#define _TENSORRT_IMPL_H_

#ifdef WITH_TENSORRT

#include "IBaseImpl.h"

namespace smartmore
{
    class TensorRTImpl : public IBaseImpl
    {
    public:
        TensorRTImpl();
        ~TensorRTImpl();

    public:
        ResultCode Init(std::string &model_data,
                        const int labelCount,
                        const bool USE_GPU,
                        const int device_id) override;

        ResultCode Do(const cv::Mat &input, const std::vector<float> &thresholds, cv::Mat &mask) override;

    private:
        class Impl;
        std::shared_ptr<Impl> _impl;
    };

} // namespace smartmore

#endif

#endif