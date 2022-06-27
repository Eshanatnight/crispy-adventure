#include <fmt/core.h>
#include <fmt/color.h>

#include "utils.h"

#include <string>
#include <vector>

#include <opencv2/face.hpp>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fmt::print(fg(fmt::color::hot_pink), "useage: {} <csv.ext> <output_folder>\n", argv[0]);
		exit(1);
	}

	std::string outFolder(".");
	if (argc == 3)
	{
		outFolder = std::move(std::string(argv[3]));
	}

	std::string fm_csv(argv[2]);

	std::vector<cv::Mat> images;
	std::vector<int> lables;

	try
	{
		read_csv(fm_csv, images, lables);
	}
	catch (const cv::Exception& e)
	{
		fmt::print(stderr, fg(fmt::color::red), "Error Opening File {}\nReason: {}\n\n", fm_csv, e.msg);
		exit(1);
	}

	if (images.size() <= 1)
	{
		std::string errorMessage = fmt::format("Insufficient Data\n");
		CV_Error(cv::Error::StsError, errorMessage);
	}

	int height = images[0].rows;

	cv::Mat testSample = images[images.size() - 1];
	int testLable = lables[lables.size() - 1];

	images.pop_back();
	lables.pop_back();


	cv::Ptr<cv::face::EigenFaceRecognizer> model = cv::face::EigenFaceRecognizer::create();
	model->train(images, lables);

	int predictedLable = model->predict(testSample);

	std::string result = fmt::format("Predicted Class = {}, Actual Class = {}", predictedLable, testLable);

}
