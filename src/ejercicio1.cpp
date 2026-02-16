#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

void ejercicio1_rgb_a_hsv() {

    // Cargar imagen en formato BGR
    cv::Mat img_bgr = cv::imread("../images/imagen.jpeg");

    if (img_bgr.empty()) {
        std::cout << "Error: No se pudo cargar la imagen" << std::endl;
        return;
    }

    int rows = img_bgr.rows;
    int cols = img_bgr.cols;

    // Matriz para almacenar la imagen HSV resultante
    cv::Mat img_hsv(rows, cols, CV_8UC3);

    // Recorrer cada píxel de la imagen
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            // Obtener píxel en BGR
            cv::Vec3b pixel_bgr = img_bgr.at<cv::Vec3b>(i, j);

            // Normalizar valores BGR al rango [0,1]
            float B = pixel_bgr[0] / 255.0f;
            float G = pixel_bgr[1] / 255.0f;
            float R = pixel_bgr[2] / 255.0f;

            // Calcular valores máximos, mínimos y diferencia
            float Cmax = std::max(R, std::max(G, B));
            float Cmin = std::min(R, std::min(G, B));
            float delta = Cmax - Cmin;

            // Cálculo del tono (Hue)
            float H = 0.0f;

            if (delta == 0) {
                H = 0.0f;
            }
            else if (Cmax == R) {
                H = 60.0f * std::fmod(((G - B) / delta), 6.0f);
            }
            else if (Cmax == G) {
                H = 60.0f * (((B - R) / delta) + 2.0f);
            }
            else {
                H = 60.0f * (((R - G) / delta) + 4.0f);
            }

            if (H < 0.0f) {
                H += 360.0f;
            }

            // Saturación
            float S = (Cmax == 0.0f) ? 0.0f : delta / Cmax;

            // Valor (brillo)
            float V = Cmax;

            // Conversión al formato HSV usado por OpenCV
            unsigned char H_opencv = static_cast<unsigned char>(H / 2.0f);
            unsigned char S_opencv = static_cast<unsigned char>(S * 255.0f);
            unsigned char V_opencv = static_cast<unsigned char>(V * 255.0f);

            img_hsv.at<cv::Vec3b>(i, j) =
                cv::Vec3b(H_opencv, S_opencv, V_opencv);
        }
    }

    cv::imshow("Original BGR", img_bgr);
    cv::imshow("HSV Manual", img_hsv);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main() {
    ejercicio1_rgb_a_hsv();
    return 0;
}
