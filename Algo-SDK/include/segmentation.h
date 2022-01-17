/*
 * @Descripttion:
 * @version:
 * @Author: max.ma
 * @Date: 2020-11-06 11:49:09
 * @LastEditors: zhenkun.yu
 * @LastEditTime: 2021-05-20 10:29:16
 */

#ifndef __MEIWEISEGMODULE_H_H__
#define __MEIWEISEGMODULE_H_H__

#include "ISegmentationModule.h"

namespace smartmore
{
    class DLL_API HuiKeSegModule : public ISegmentationModule
    {
    public:
        HuiKeSegModule();
        ~HuiKeSegModule();

        /**
            sdk版本号
            @return sdk版本号字符串
        */
        std::string Version() override;
        /**
            sdk初始化
            @param  input_model_path ：模型路径
            @param  USE_GPU             ：是否使用gpu
            @param  device_id         ：设备id
            @return 返回码 ：0：成功； 其他值：失败
        */
        ResultCode Init(
            const std::string &input_model_path,
            const bool USE_GPU,
            const int device_id) override;

        /**
            sdk处理
            @param  req ：sdk输入参数结构体的引用
            @param  rsp    ：sdk输出结果结构体的引用
            @return 返回码 ：0：成功； 其他值：失败
        */
        ResultCode Run(const SegmentationRequest &req, SegmentationResponse &rsp) override;

    private:
        class Impl;
        std::shared_ptr<Impl> impl_;
    };

} // namespace smartmore

#endif
