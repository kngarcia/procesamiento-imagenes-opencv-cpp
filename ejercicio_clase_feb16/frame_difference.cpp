#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main() {

    // Abrimos la cámara (0 = cámara por defecto)
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        return -1;
    }

    // Matrices necesarias
    Mat frame;       // Frame actual en BGR
    Mat prevFrame;   // Frame anterior en BGR (solo para inicializar)
    Mat gray;        // Frame actual en escala de grises
    Mat prevGray;    // Frame anterior en escala de grises
    Mat diff;        // Imagen de diferencia absoluta
    Mat thresh;      // Imagen binaria (movimiento / no movimiento)

    // Capturamos el primer frame
    cap >> prevFrame;

    // Lo convertimos a escala de grises
    cvtColor(prevFrame, prevGray, COLOR_BGR2GRAY);

    // Inicializamos las imágenes de trabajo
    diff   = Mat(prevGray.rows, prevGray.cols, CV_8U);
    thresh = Mat(prevGray.rows, prevGray.cols, CV_8U);

    while (true) {

        // Capturamos un nuevo frame
        cap >> frame;

        // Convertimos el frame actual a escala de grises
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // Calculamos la diferencia absoluta entre frame actual y frame anterior
        for (int i = 0; i < gray.rows; i++) {
            for (int j = 0; j < gray.cols; j++) {
                diff.at<uchar>(i, j) =
                    abs(gray.at<uchar>(i, j) - prevGray.at<uchar>(i, j));
            }
        }

        // Aplicamos un umbral para detectar movimiento
        for (int i = 0; i < diff.rows; i++) {
            for (int j = 0; j < diff.cols; j++) {
                thresh.at<uchar>(i, j) =
                    (diff.at<uchar>(i, j) > 10) ? 255 : 0;
            }
        }

        // Mostramos la imagen binaria de movimiento
        imshow("Frame Difference", thresh);

        // El frame actual pasa a ser el frame anterior para la siguiente iteración
        prevGray = gray.clone();

        // Salimos si se presiona 'q'
        if (waitKey(1) == 'q') {
            break;
        }
    }

    return 0;
}
