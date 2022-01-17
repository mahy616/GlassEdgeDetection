#ifndef __HUIKEALGO_H__
#define __HUIKEALGO_H__

#include <memory>
#include <array>
#include <vector>
#include <opencv2/opencv.hpp>

#ifdef SM_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace smartmore
{

    struct EdgeConfig
    {
        std::vector<int> x_range;
        std::vector<int> y_range;
        int threshold;
        std::string mode;
        int erode;
        int roi;
    };

    struct InputConfig // this is for the input file
    {
        std::string mode;   // 支持first，last，proceed，分别代表第1张，最后1张，中间，需要外部传入
        std::string mirror; //支持left，right，分别代表玻璃在图像左边、右边，需要外部传入
        const int X_LENGTH;
        const int Y_LENGTH;
        const EdgeConfig *x_edge_config, *y_edge_config;
        InputConfig(std::string &mode, std::string &mirror, const EdgeConfig *x_edge_config, const EdgeConfig *y_edge_config, int x_length, int y_length) : mode{mode}, mirror{mirror}, x_edge_config{x_edge_config}, y_edge_config{y_edge_config}, X_LENGTH{x_length}, Y_LENGTH{y_length}
        {
            //
        }
    };

    class DLL_API HuikeAlgo
    {
    public:
        HuikeAlgo();
        ~HuikeAlgo();
        void RunAlgo(cv::Mat &mask, int corner, cv::Mat &, InputConfig &, bool &, bool);
        bool VisualizeDetectOk(const cv::Mat &origin_img, const cv::Mat &mask,cv::Mat &rendered_image);

    private:
        class Impl;
        std::shared_ptr<Impl> _impl;
    };

} // namespace smartmore

#endif