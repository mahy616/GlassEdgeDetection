/*******************************************************************************
 *  FILENAME:      ISegmentationModule.h
 *
 *  AUTHORS:       max.ma    START DATE: Friday November 6th 2020
 *
 *  LAST MODIFIED: Friday, November 20th 2020, 10:45:02 am
 *
 *  CONTACT:       max.ma@smartmore.com
*******************************************************************************/

#ifndef __ISEG_MODULE_H__
#define __ISEG_MODULE_H__

#include <opencv2/opencv.hpp>
#include "Common.h"

namespace smartmore
{
    //!
    //! \struct SegmentationRequest
    //!
    struct SegmentationRequest
    {
        cv::Mat image;
        std::vector<int> thresholds; //!< The threshold .
    };

    //!
    //! \struct SegmentationResponse
    //!
    struct SegmentationResponse
    {
        cv::Mat mask;                     //! The output mask
        std::map<int, std::string> names; //! Types of mask
        QCCode code;                      //! status code
    };

    //!
    //! \class ISegmentationModule
    //!
    //! \brief Base SegmentationModule class for user-implemented layers.
    //!
    class DLL_API ISegmentationModule
    {
    public:
        ISegmentationModule() = default;
        virtual ~ISegmentationModule() = default;

    public:
        //!
        //! \brief Get version information of the model.
        //!
        //! \return The version information.
        //!
        //! Version information should include the MD5 of model and the build time of this SDK.(e.g. "Version: 1.0.0\nModel MD5: 87d2c0a12551f0fc807b9a2aec207543\nSDK CreateTime: Nov  5 2020 17:00:00")
        //!
        virtual std::string Version() = 0;

        //!
        //! \brief Init SegmentationModule with given model path.
        //!
        //! \param input_model_path The path of input model.
        //! \param use_gpu Whethre use gpu in subsequent inference.
        //! \param device_id ID of gpu used.
        //!
        //! \return The status of Initialization. OK for success, else non-zero.
        //!
        //! In particular, this function is called prior to any call to Run().
        //!
        virtual ResultCode Init(const std::string &input_model_path,
                                const bool USE_GPU,
                                const int device_id) = 0;

        //!
        //! \brief Do inference.
        //!
        //! \param req The origin request.
        //! \param rsp The respnse generates from Run.
        //!
        //! \return The status of Visualization. OK for success, else non-zero.
        //!
        virtual ResultCode Run(const SegmentationRequest &req, SegmentationResponse &rsp) = 0;

        //!
        //! \brief Visualize result.
        //!
        //! \param req The origin request.
        //! \param rsp The respnse generates from Run.
        //! \param image Output image.
        //!
        //! \return The status of Visualization. OK for success, else non-zero.
        //!
        virtual ResultCode Visualize(const SegmentationRequest &req,
                                     cv::Mat & extra_side,
                                     std::string& side,
                                     const SegmentationResponse &rsp,const cv::Mat & mask_head_or_tail,cv::Mat & remove_detection,
                                     cv::Mat &image);
    };

} // namespace smartmore

#endif