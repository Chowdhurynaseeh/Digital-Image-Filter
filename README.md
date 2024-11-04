![image](https://github.com/user-attachments/assets/f17d0832-31bf-4c2c-bbfb-2a1ce6cae4fb)
# Digital Image Processing - RAW Image Median Filter

This project implements a median filter for processing raw RGB images using C++. The code reads a raw image file, applies a median filter with varying filter sizes, and saves the filtered images back to disk.

## Overview

The median filter is a non-linear filter used to remove noise from images while preserving edges. This implementation processes RGB images stored in raw format, allowing for customizable filter sizes.

### Features

- Read and process raw RGB images.
- Apply median filtering with adjustable filter sizes.
- Save the filtered images in raw format.
- Supports OpenCV for potential enhancements and additional image processing capabilities.

## Code Structure

The main components of the code include:

1. **Image Reading**: Function to read raw images into a vector.
2. **Median Filter Application**: Function to apply a median filter across the image.
3. **Image Saving**: Function to save the processed image back to a raw file.
4. **Main Function**: Orchestrates the reading, processing, and saving of images.

### Functions

- `std::vector<uint8_t> readRawImage(const std::string& filename, int width, int height)`: Reads a raw image file and returns the pixel data as a vector.
- `std::vector<uint8_t> applyMedianFilter(const std::vector<uint8_t>& inputImage, int width, int height, int filterSize)`: Applies a median filter to the input image and returns the filtered image.
- `void saveRawImage(const std::string& filename, const std::vector<uint8_t>& image, int width, int height)`: Saves the processed image to a specified file.

## Dependencies

- **C++ Standard Library**: For basic input/output and data structures.
- **OpenCV**: For advanced image processing capabilities (optional for this implementation, but recommended for future enhancements).

### Installation

1. Ensure you have a C++ compiler installed (e.g., g++, clang).
2. Install OpenCV if you plan to use its functionalities.
3. Clone this repository or download the source code files.
4. Compile the code using a command like:
   ```bash
   g++ -o median_filter testing_filter_code.cpp `pkg-config --cflags --libs opencv4`

