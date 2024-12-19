#include <opencv2/opencv.hpp>
#include <iostream>

// Function prototypes
void applyGaussianBlur(const std::string& inputPath, const std::string& outputPath);
void applyIdentityKernel(const std::string& inputPath, const std::string& outputPath);
void applyMedianBlur(const std::string& inputPath, const std::string& outputPath);
void applySharpening(const std::string& inputPath, const std::string& outputPath);
void applyBilateralFilter(const std::string& inputPath, const std::string& outputPath);
void enhanceContrast(const std::string& inputPath, const std::string& outputPath);
void addSaltAndPepperNoise(const std::string& inputPath, const std::string& outputPath, double noise_ratio);
void applyCannyEdgeDetection(const std::string& inputPath, const std::string& outputPath, double lowThreshold, double highThreshold);
void convertToHSV(const std::string& inputPath, const std::string& outputPath);

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " filter_type input_image output_image" << std::endl;
        std::cout << "filter_type options: gaussian, identity, median, sharpen, bilateral" << std::endl;
        return -1;
    }

    std::string filterType = argv[1];
    std::string inputPath = argv[2];
    std::string outputPath = argv[3];

    if (filterType == "gaussian") {
        applyGaussianBlur(inputPath, outputPath);
    } else if (filterType == "identity") {
        applyIdentityKernel(inputPath, outputPath);
    } else if (filterType == "median") {
        applyMedianBlur(inputPath, outputPath);
    } else if (filterType == "sharpen") {
        applySharpening(inputPath, outputPath);
    } else if (filterType == "bilateral") {
        applyBilateralFilter(inputPath, outputPath);
    } else {
        std::cout << "Invalid filter type provided." << std::endl;
        return -1;
    }

    return 0;
}


void applyGaussianBlur(const std::string& inputPath, const std::string& outputPath) {
    cv::Mat src = cv::imread(inputPath);
    if (src.empty()) {
        std::cerr << "Error opening image!" << std::endl;
        return;
    }

    cv::Mat dst;
    cv::GaussianBlur(src, dst, cv::Size(9, 9), 0, 0);
    cv::imwrite(outputPath, dst);
    cv::imshow("Original Image", src);
    cv::imshow("Gaussian Blurred Image", dst);
    cv::waitKey(0);
}

void applyIdentityKernel(const std::string& inputPath, the std::string& outputPath) {
    cv::Mat src = cv::imread(inputPath);
    if (src.empty()) {
        std::cerr << "Error opening image!" << std::endl;
        return;
    }

    cv::Mat kernel = (cv::Mat_<float>(3,3) <<
                      0, 0, 0,
                      0, 1, 0,
                      0, 0, 0);
    cv::Mat dst;
    cv::filter2D(src, dst, -1, kernel);
    cv::imwrite(outputPath, dst);
    cv::imshow("Original Image", src);
    cv::imshow("Image after Applying Identity Kernel", dst);
    cv::waitKey(0);
}

void applyMedianBlur(const std::string& inputPath, const std::string& outputPath) {
    cv::Mat src = cv::imread(inputPath);
    if (src.empty()) {
        std::cerr << "Error opening image!" << std::endl;
        return;
    }

    cv::Mat dst;
    cv::medianBlur(src, dst, 5); // You can change the kernel size
    cv::imwrite(outputPath, dst);
    cv::imshow("Original Image", src);
    cv::imshow("Median Blurred Image", dst);
    cv::waitKey(0);
}

void applySharpening(const std::string& inputPath, the std::string& outputPath) {
    cv::Mat src = cv::imread(inputPath);
    if (src.empty()) {
        std::cerr << "Error opening image!" << std::endl;
        return;
    }

    cv::Mat kernel = (cv::Mat_<float>(3,3) <<
                      -1, -1, -1,
                      -1,  9, -1,
                      -1, -1, -1);
    cv::Mat dst;
    cv::filter2D(src, dst, -1, kernel);
    cv::imwrite(outputPath, dst);
    cv::imshow("Original Image", src);
    cv::imshow("Sharpened Image", dst);
    cv::waitKey(0);
}

void applyBilateralFilter(const std::string& inputPath, const std::string& outputPath) {
    cv::Mat src = cv::imread(inputPath);
    if (src.empty()) {
        std::cerr << "Error opening image!" << std::endl;
        return;
    }

    cv::Mat dst;
    cv::bilateralFilter(src, dst, 9, 75, 75); // Diameter and two sigma values
    cv::imwrite(outputPath, dst);
    cv::imshow("Original Image", src);
    cv::imshow("Bilateral Filtered Image", dst);
    cv::waitKey(0);
}

void enhanceContrast(const std::string& inputPath, const std::string& outputPath) {
    cv::Mat src = cv::imread(inputPath, cv::IMREAD_GRAYSCALE); // Load the image in grayscale
    if (src.empty()) {
        std::cerr << "Error opening image!" << std::endl;
        return;
    }

    cv::Mat dst;
    cv::equalizeHist(src, dst);
    cv::imwrite(outputPath, dst);
}

void addSaltAndPepperNoise(const std::string& inputPath, const std::string& outputPath, double noise_ratio) {
    cv::Mat src = cv::imread(inputPath);
    if (src.empty()) {
        std::cerr << "Error opening image!" << std::endl;
        return;
    }

    int amount = static_cast<int>(noise_ratio * src.rows * src.cols);
    for (int counter = 0; counter < amount; ++counter) {
        int x = rand() % src.cols;
        int y = rand() % src.rows;
        src.at<cv::Vec3b>(y, x) = (rand() % 2 == 1) ? cv::Vec3b(255,255,255) : cv::Vec3b(0,0,0);
    }
    cv::imwrite(outputPath, src);
}

void applyCannyEdgeDetection(const std::string& inputPath, const std::string& outputPath, double lowThreshold, double highThreshold) {
    cv::Mat src = cv::imread(inputPath, cv::IMREAD_GRAYSCALE);
    if (src.empty()) {
        std::cerr << "Error opening image!" << std::endl;
        return;
    }

    cv::Mat edges;
    cv::Canny(src, edges, lowThreshold, highThreshold);
    cv::imwrite(outputPath, edges);
}

void convertToHSV(const std::string& inputPath, const std::string& outputPath) {
    cv::Mat src = cv::imread(inputPath);
    if (src.empty()) {
        std::cerr << "Error opening image!" << std::endl;
        return;
    }

    cv::Mat hsvImage;
    cv::cvtColor(src, hsvImage, cv::COLOR_BGR2HSV);
    cv::imwrite(outputPath, hsvImage);
}
