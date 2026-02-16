#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>

void ejercicio4_gray_world() {

    cv::Mat img_bgr = cv::imread("../images/imagen.jpeg");
    if (img_bgr.empty()) {
        std::cout << "Error: No se pudo cargar la imagen" << std::endl;
        return;
    }

    int rows = img_bgr.rows;
    int cols = img_bgr.cols;
    int total_pixels = rows * cols;

    //   PASO 1: Suma de canales

    double sum_R = 0.0;
    double sum_G = 0.0;
    double sum_B = 0.0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            cv::Vec3b bgr = img_bgr.at<cv::Vec3b>(i, j);

            sum_B += bgr[0];
            sum_G += bgr[1];
            sum_R += bgr[2];
        }
    }


    //   PASO 2: Promedios

    double avg_R = sum_R / total_pixels;
    double avg_G = sum_G / total_pixels;
    double avg_B = sum_B / total_pixels;

    std::cout << "[DEBUG] avg_R = " << avg_R
              << " avg_G = " << avg_G
              << " avg_B = " << avg_B << std::endl;


    //   PASO 3: Promedio gris

    double gray_avg = (avg_R + avg_G + avg_B) / 3.0;

    std::cout << "[DEBUG] gray_avg = " << gray_avg << std::endl;


    //   PASO 4: Factores de escala

    double scale_R = gray_avg / avg_R;
    double scale_G = gray_avg / avg_G;
    double scale_B = gray_avg / avg_B;

    std::cout << "[DEBUG] scale_R = " << scale_R
              << " scale_G = " << scale_G
              << " scale_B = " << scale_B << std::endl;


    //   PASO 5: Imagen corregida

    cv::Mat img_resultado(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            cv::Vec3b bgr = img_bgr.at<cv::Vec3b>(i, j);

            int B_new = static_cast<int>(bgr[0] * scale_B);
            int G_new = static_cast<int>(bgr[1] * scale_G);
            int R_new = static_cast<int>(bgr[2] * scale_R);

            B_new = std::min(B_new, 255);
            G_new = std::min(G_new, 255);
            R_new = std::min(R_new, 255);

            img_resultado.at<cv::Vec3b>(i, j) = cv::Vec3b(
                static_cast<unsigned char>(B_new),
                static_cast<unsigned char>(G_new),
                static_cast<unsigned char>(R_new)
            );
        }
    }

    cv::imshow("Original", img_bgr);
    cv::imshow("Gray World", img_resultado);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

// Main
int main() {
    ejercicio4_gray_world();
    return 0;
}
