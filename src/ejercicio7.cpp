#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

int main() {

    cv::Mat img = cv::imread("../images/imagen.jpg");
    if (img.empty()) return 0;

    int rows = img.rows;
    int cols = img.cols;

    double cx = cols / 2.0;
    double cy = rows / 2.0;
    double d_max = std::sqrt(cx * cx + cy * cy);
    double k = 0.6;

    cv::Mat resultado = img.clone();

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {

            double dx = x - cx;
            double dy = y - cy;
            double d = std::sqrt(dx * dx + dy * dy);
            double d_norm = d / d_max;

            double factor = 1.0 - k * d_norm;
            if (factor < 0.0) factor = 0.0;

            cv::Vec3b p = img.at<cv::Vec3b>(y, x);
            for (int c = 0; c < 3; c++) {
                resultado.at<cv::Vec3b>(y, x)[c] =
                    cv::saturate_cast<uchar>(p[c] * factor);
            }
        }
    }

    cv::imwrite("vignette_debug.jpg", resultado);
    std::cout << "Imagen guardada como vignette_debug.jpg\n";
    return 0;
}
