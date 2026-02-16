#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

void ejercicio6_gamma(double gamma = 1.5) {

    cv::Mat img_bgr = cv::imread("../images/imagen.jpeg");
    if (img_bgr.empty()) {
        std::cout << "Error: No se pudo cargar la imagen" << std::endl;
        return;
    }

    int rows = img_bgr.rows;
    int cols = img_bgr.cols;

    //   PASO 1: Crear LUT (0–255)

    unsigned char LUT[256];

    for (int i = 0; i < 256; i++) {
        double normalized = i / 255.0;
        double corrected = std::pow(normalized, gamma);
        int value = static_cast<int>(255.0 * corrected);
        LUT[i] = static_cast<unsigned char>(std::min(value, 255));
    }


    //   PASO 2: Aplicar LUT

    cv::Mat img_resultado(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            cv::Vec3b bgr = img_bgr.at<cv::Vec3b>(i, j);

            img_resultado.at<cv::Vec3b>(i, j) = cv::Vec3b(
                LUT[bgr[0]], // B
                LUT[bgr[1]], // G
                LUT[bgr[2]]  // R
            );
        }
    }

    cv::imshow("Original", img_bgr);
    cv::imshow("Gamma corregida", img_resultado);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

// Main
int main() {
    ejercicio6_gamma(1.5);
    return 0;
}
