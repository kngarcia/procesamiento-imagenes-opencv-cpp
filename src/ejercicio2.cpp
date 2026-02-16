#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

void ejercicio2_modificar_saturacion() {

    cv::Mat img_bgr = cv::imread("../images/imagen.jpeg");
    if (img_bgr.empty()) {
        std::cout << "Error: No se pudo cargar la imagen" << std::endl;
        return;
    }

    int rows = img_bgr.rows;
    int cols = img_bgr.cols;

    cv::Mat img_hsv(rows, cols, CV_8UC3);

    
    // PARTE 1: BGR → HSV MANUAL
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            cv::Vec3b bgr = img_bgr.at<cv::Vec3b>(i, j);

            float B = bgr[0] / 255.0f;
            float G = bgr[1] / 255.0f;
            float R = bgr[2] / 255.0f;

            float Cmax = std::max(R, std::max(G, B));
            float Cmin = std::min(R, std::min(G, B));
            float delta = Cmax - Cmin;

            float H = 0.0f;
            if (delta != 0) {
                if (Cmax == R)
                    H = 60.0f * std::fmod(((G - B) / delta), 6.0f);
                else if (Cmax == G)
                    H = 60.0f * (((B - R) / delta) + 2.0f);
                else
                    H = 60.0f * (((R - G) / delta) + 4.0f);
            }
            if (H < 0) H += 360.0f;

            float S = (Cmax == 0) ? 0 : delta / Cmax;
            float V = Cmax;

            img_hsv.at<cv::Vec3b>(i, j) = cv::Vec3b(
                static_cast<unsigned char>(H / 2.0f),   // 0–179
                static_cast<unsigned char>(S * 255.0f), // 0–255
                static_cast<unsigned char>(V * 255.0f)  // 0–255
            );
        }
    }

    
    // DEPURACIÓN HSV
    cv::Vec3b hsv_test = img_hsv.at<cv::Vec3b>(100, 100);
    std::cout << "[DEBUG HSV] H=" << (int)hsv_test[0]
              << " S=" << (int)hsv_test[1]
              << " V=" << (int)hsv_test[2] << std::endl;

    // PARTE 2: MODIFICAR SATURACIÓN
       
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            cv::Vec3b& hsv = img_hsv.at<cv::Vec3b>(i, j);

            int S = static_cast<int>(hsv[1] * 1.5);
            if (S > 255) S = 255;

            hsv[1] = static_cast<unsigned char>(S);
        }
    }

    //   PARTE 3: HSV → BGR MANUAL

    cv::Mat img_resultado(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            cv::Vec3b hsv = img_hsv.at<cv::Vec3b>(i, j);

            float H = hsv[0] * 2.0f;       // 0–360
            float S = hsv[1] / 255.0f;     // 0–1
            float V = hsv[2] / 255.0f;     // 0–1

            float C = V * S;
            float X = C * (1 - std::fabs(std::fmod(H / 60.0f, 2) - 1));
            float m = V - C;

            float r = 0, g = 0, b = 0;

            if (H < 60)      { r = C; g = X; b = 0; }
            else if (H < 120){ r = X; g = C; b = 0; }
            else if (H < 180){ r = 0; g = C; b = X; }
            else if (H < 240){ r = 0; g = X; b = C; }
            else if (H < 300){ r = X; g = 0; b = C; }
            else             { r = C; g = 0; b = X; }

            img_resultado.at<cv::Vec3b>(i, j) = cv::Vec3b(
                static_cast<unsigned char>((b + m) * 255),
                static_cast<unsigned char>((g + m) * 255),
                static_cast<unsigned char>((r + m) * 255)
            );
        }
    }

    //   DEPURACIÓN BGR

    cv::Vec3b bgr_test = img_resultado.at<cv::Vec3b>(100, 100);
    std::cout << "[DEBUG BGR] B=" << (int)bgr_test[0]
              << " G=" << (int)bgr_test[1]
              << " R=" << (int)bgr_test[2] << std::endl;

    cv::imshow("Original", img_bgr);
    cv::imshow("Saturacion Aumentada", img_resultado);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main() {
    ejercicio2_modificar_saturacion();
    return 0;
}
