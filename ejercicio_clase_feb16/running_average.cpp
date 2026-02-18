#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main() {

    // Abrimos la cámara
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        return -1;
    }

    Mat frame;     // Frame actual en BGR
    Mat gray;      // Frame actual en escala de grises
    Mat avgFrame;  // Modelo del fondo (promedio acumulado)

    // Factor de aprendizaje
    // alpha pequeño = fondo más estable
    // alpha grande  = fondo se adapta rápido
    float alpha = 0.5f;

    // Capturamos el primer frame
    cap >> frame;

    // Inicializamos el fondo con el primer frame en gris
    cvtColor(frame, avgFrame, COLOR_BGR2GRAY);

    while (true) {

        // Capturamos un nuevo frame
        cap >> frame;

        // Convertimos a escala de grises
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // Actualizamos el modelo de fondo píxel a píxel
        for (int i = 0; i < avgFrame.rows; i++) {
            for (int j = 0; j < avgFrame.cols; j++) {

                uchar currentPixel = gray.at<uchar>(i, j);
                uchar avgPixel     = avgFrame.at<uchar>(i, j);

                // Fórmula del running average
                float newValue =
                    alpha * currentPixel +
                    (1.0f - alpha) * avgPixel;

                avgFrame.at<uchar>(i, j) =
                    static_cast<uchar>(newValue);
            }
        }

        // Mostramos el fondo aprendido
        imshow("Running Average", avgFrame);

        // Salimos si se presiona 'q'
        if (waitKey(1) == 'q') {
            break;
        }
    }

    return 0;
}
