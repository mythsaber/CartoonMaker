#include<opencv.hpp>
#include <atlimage.h>  //CImage
/*
��ʾopencvͼƬ��ʽMat��ͼ��ؼ�vIDC��
vMat��ͼ��Mat
vIDC��ͼ��ؼ�ID
*/
namespace tool
{
	void mat_to_cimage(const cv::Mat& mat, CImage& cImage);
}