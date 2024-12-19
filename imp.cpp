#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    // Check if the image filename is provided
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <Path_to_Image>" << std::endl;
        return -1;
    }

    // Read the image file
    cv::Mat image = cv::imread(argv[1]);
    if (image.empty()) {
        std::cout << "Could not read the image: " << argv[1] << std::endl;
        return -1;
    }

    // Apply Gaussian Blur
    cv::Mat image_blurred;
    cv::GaussianBlur(image, image_blurred, cv::Size(5, 5), 0);

    // Save the blurred image
    std::string outputFilename = "blurred_image.jpg";
    cv::imwrite(outputFilename, image_blurred);

    // Display the original and blurred images
    cv::imshow("Original Image", image);
    cv::imshow("Gaussian Blurred Image", image_blurred);

    // Wait for key press
    cv::waitKey(0);

    return 0;
}
