#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

// ESTRUCTURA PIXEL
struct Pixel {
    double r, g, b;
    Pixel() : r(0), g(0), b(0) {}
    Pixel(double r_, double g_, double b_) : r(r_), g(g_), b(b_) {}
};

//   DISTANCIA EUCLIDIANA RGB

double distancia_euclidiana(const Pixel& p1, const Pixel& p2) {
    return std::sqrt(
        (p1.r - p2.r) * (p1.r - p2.r) +
        (p1.g - p2.g) * (p1.g - p2.g) +
        (p1.b - p2.b) * (p1.b - p2.b)
    );
}

//   EJERCICIO 3: K-MEANS MANUAL

void ejercicio3_kmeans_manual(int K = 5) {

    cv::Mat img_bgr = cv::imread("../images/imagen.jpeg");
    if (img_bgr.empty()) {
        std::cout << "Error: No se pudo cargar la imagen" << std::endl;
        return;
    }

    /* Redimensionar para acelerar */
    cv::Mat img_small;
    cv::resize(img_bgr, img_small, cv::Size(160, 120));

    int rows = img_small.rows;
    int cols = img_small.cols;
    int total_pixels = rows * cols;

    std::cout << "Procesando " << total_pixels
              << " píxeles con K=" << K << std::endl;


    //   PASO 1: Vector de píxeles

    std::vector<Pixel> pixels;
    pixels.reserve(total_pixels);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cv::Vec3b bgr = img_small.at<cv::Vec3b>(i, j);
            pixels.emplace_back(
                bgr[2], // R
                bgr[1], // G
                bgr[0]  // B
            );
        }
    }

    //   PASO 2: Inicializar centroides

    std::srand((unsigned int)std::time(0));
    std::vector<Pixel> centroides(K);

    for (int k = 0; k < K; k++) {
        int idx = std::rand() % total_pixels;
        centroides[k] = pixels[idx];
    }


    //   PASO 3: Asignaciones

    std::vector<int> labels(total_pixels, 0);


    //   PASO 4: Iteraciones K-Means

    int max_iteraciones = 20;

    for (int iter = 0; iter < max_iteraciones; iter++) {

        std::cout << "Iteración "
                  << (iter + 1) << "/"
                  << max_iteraciones << std::endl;

        /* --- PASO 4a: Asignación --- */
        for (int i = 0; i < total_pixels; i++) {

            double min_dist = distancia_euclidiana(pixels[i], centroides[0]);
            int best_cluster = 0;

            for (int k = 1; k < K; k++) {
                double dist = distancia_euclidiana(pixels[i], centroides[k]);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_cluster = k;
                }
            }

            labels[i] = best_cluster;
        }

        /* --- PASO 4b: Recalcular centroides --- */
        std::vector<double> sum_r(K, 0.0);
        std::vector<double> sum_g(K, 0.0);
        std::vector<double> sum_b(K, 0.0);
        std::vector<int> count(K, 0);

        for (int i = 0; i < total_pixels; i++) {
            int k = labels[i];
            sum_r[k] += pixels[i].r;
            sum_g[k] += pixels[i].g;
            sum_b[k] += pixels[i].b;
            count[k]++;
        }

        for (int k = 0; k < K; k++) {
            if (count[k] > 0) {
                centroides[k].r = sum_r[k] / count[k];
                centroides[k].g = sum_g[k] / count[k];
                centroides[k].b = sum_b[k] / count[k];
            }
        }
    }


    //   PASO 5: Imagen cuantizada

    cv::Mat img_quantized(rows, cols, CV_8UC3);

    int idx = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            int k = labels[idx++];
            img_quantized.at<cv::Vec3b>(i, j) = cv::Vec3b(
                (unsigned char)centroides[k].b,
                (unsigned char)centroides[k].g,
                (unsigned char)centroides[k].r
            );
        }
    }


    //   PASO 6: Paleta de colores

    cv::Mat paleta(50, K * 50, CV_8UC3);

    for (int k = 0; k < K; k++) {
        cv::rectangle(
            paleta,
            cv::Rect(k * 50, 0, 50, 50),
            cv::Scalar(
                centroides[k].b,
                centroides[k].g,
                centroides[k].r
            ),
            cv::FILLED
        );
    }

    cv::imshow("Original", img_small);
    cv::imshow("K-Means Manual", img_quantized);
    cv::imshow("Paleta", paleta);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

// Main
int main() {
    ejercicio3_kmeans_manual(5);
    return 0;
}
