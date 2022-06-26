#include <fmt/core.h>
#include <opencv2/face.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <fstream>
#include <sstream>


// Normalizes the given face image to a standard size.
static cv::Mat norm_0_255(cv::InputArray _src)
{
	cv::Mat src = _src.getMat();
	
	cv::Mat dst;
	switch (src.channels())
	{
	case 1:
		cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC1);
		break;
	case 3:
		cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC3);
		break;
	default:
		src.copyTo(dst);
		break;
	}
	
	return dst;
}

// read csv 
static void read_csv(const std::string& file, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator = ';')
{
	std::ifstream file_stream(file, std::ifstream::in);
	if (!file_stream.is_open())
	{
		std::string error_message = fmt::format("Unable to open file \"{}\"\n", file);
		CV_Error(cv::Error::StsBadArg, error_message);
		return;
	}
	
	std::string line, path, classlabel;
	while (std::getline(file_stream, line))
	{
		std::stringstream liness(line);
		std::getline(liness, path, separator);
		std::getline(liness, classlabel);

		if (!path.empty() && !classlabel.empty())
		{
			images.push_back(cv::imread(path, 0));
			labels.push_back(std::stoi(classlabel));
		}
	}
}

int main()
{
	fmt::print("Hello, World!\n");
}
