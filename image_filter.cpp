#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp> // Include OpenCV header
#include <algorithm>
#include <string>

using namespace std;

// Constants
const int CHANNELS = 3; // Assuming the image has RGB color channels

// Function to read a raw image file
std::vector<uint8_t> readRawImage(const std::string& filename, int width, int height) {
    std::ifstream file(filename, std::ios::binary); // Open the file in binary mode
    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl; // Error message if file can't be opened
        return std::vector<uint8_t>(); // Return empty vector
    }

    // Create a vector to hold the image data
    std::vector<uint8_t> image(width * height * CHANNELS);
    file.read(reinterpret_cast<char*>(image.data()), width * height * CHANNELS); // Read image data into the vector

    return image; // Return the image data
}

// Function to apply a median filter to a color image (RGB)
std::vector<uint8_t> applyMedianFilter(const std::vector<uint8_t>& inputImage, int width, int height, int filterSize) {
    std::vector<uint8_t> outputImage(width * height * CHANNELS); // Vector to store the output image

    int padding = filterSize / 2; // Calculate padding based on filter size

    // Loop through each pixel in the image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int channel = 0; channel < CHANNELS; channel++) { // Loop over each RGB channel
                std::vector<uint8_t> neighborhood; // Vector to store neighboring pixels

                // Extract pixels from the neighborhood
                for (int i = -padding; i <= padding; i++) {
                    for (int j = -padding; j <= padding; j++) {
                        // Calculate the coordinates of the neighboring pixel, ensuring they are within bounds
                        int neighborX = std::min(std::max(x + j, 0), width - 1);
                        int neighborY = std::min(std::max(y + i, 0), height - 1);
                        // Add the neighboring pixel to the neighborhood vector
                        neighborhood.push_back(inputImage[(neighborY * width + neighborX) * CHANNELS + channel]);
                    }
                }

                // Apply median filter to the neighborhood by sorting and picking the median
                std::sort(neighborhood.begin(), neighborhood.end()); // Sort the neighborhood pixels
                outputImage[(y * width + x) * CHANNELS + channel] = neighborhood[neighborhood.size() / 2]; // Set the output pixel to the median value
            }
        }
    }

    return outputImage; // Return the filtered image
}

// Function to save a raw image to a file
void saveRawImage(const std::string& filename, const std::vector<uint8_t>& image, int width, int height) {
    std::ofstream file(filename, std::ios::binary); // Open the file for writing in binary mode
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl; // Error message if file can't be opened
        return; // Exit the function
    }

    file.write(reinterpret_cast<const char*>(image.data()), width * height * CHANNELS); // Write the image data to the file
    std::cout << "Image saved to " << filename << std::endl; // Confirmation message
}

int main() {
    string inputFileName = "D:\\Project_Images\\img_2.raw"; // Replace with your input file name

    // Read the input image with input image height and width
    int width = 1500, height = 800;
    vector<uint8_t> inputImage = readRawImage(inputFileName, width, height);

    if (!inputImage.empty()) {
        for (int i = 3; i <= 7; i += 2) { // Iterate through filter sizes (odd numbers only)
            for (int j = 0; j <= 100; j += 10) { // Iterate through positions for median selection
                int pos = ceil((j * ((i * i) - 1)) / 100); // Calculate the median position based on j

                // Apply median filter to the image
                vector<uint8_t> filtered = applyMedianFilter(inputImage, width, height, i);

                // Save the filtered image
                saveRawImage(inputFileName + "_" + to_string(i) + "_" + to_string(j) + ".raw", filtered, width, height);
            }
        }
    } else {
        cout << "No image data read from the file." << endl; // Error message if no data was read
    }

    return 0; // Exit the program
}
