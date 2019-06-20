#include<opencv.hpp>
#include <atlimage.h>  //CImage
/*
显示opencv图片格式Mat到图像控件vIDC上
vMat：图像Mat
vIDC：图像控件ID
*/
namespace tool
{
	void mat_to_cimage(const cv::Mat& mat, CImage& cImage);
}