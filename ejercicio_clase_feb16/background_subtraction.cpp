#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

    //   1. Inicializar cámara
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Error: no se pudo abrir la camara" << endl;
        return -1;
    }

    // 2. Declaración de matrices

    Mat frame;        // Frame actual (color)
    Mat gray;         // Frame actual en escala de grises
    Mat prevGray;     // Primer frame en gris (inicialización)
    Mat avgFrame;     // Modelo de fondo (running average)
    Mat diff;         // Diferencia absoluta
    Mat thresh;       // Imagen binaria final

    /*
       3. Capturar primer frame
       (condición inicial)
    */
    cap >> frame;
    if (frame.empty()) return -1;

    cvtColor(frame, prevGray, COLOR_BGR2GRAY);

  
    // 4. Inicializar estructuras

    avgFrame = prevGray.clone();                 // Fondo inicial
    diff = Mat(prevGray.size(), CV_8U);
    thresh = Mat(prevGray.size(), CV_8U);

    float alpha = 0.5f;  // Velocidad de adaptación del fondo

    // 5. Bucle principal

    while (true) {

        /* ---- Capturar frame ---- */
        cap >> frame;
        if (frame.empty()) break;

        cvtColor(frame, gray, COLOR_BGR2GRAY);

        /*
           PASO 1: Actualizar fondo
           B_t = α·B_{t-1} + (1−α)·I_t
        */

        for (int i = 0; i < gray.rows; i++) {
            for (int j = 0; j < gray.cols; j++) {

                uchar currentPixel = gray.at<uchar>(i, j);
                uchar backgroundPixel = avgFrame.at<uchar>(i, j);

                float newValue =
                    alpha * backgroundPixel +
                    (1.0f - alpha) * currentPixel;

                avgFrame.at<uchar>(i, j) =
                    static_cast<uchar>(newValue);
            }
        }

        /*
           PASO 2: Diferencia absoluta
           D_t = |I_t − B_t|
        */

        for (int i = 0; i < gray.rows; i++) {
            for (int j = 0; j < gray.cols; j++) {
                diff.at<uchar>(i, j) =
                    abs(gray.at<uchar>(i, j) -
                        avgFrame.at<uchar>(i, j));
            }
        }

         
        // PASO 3: Umbralización
        

        for (int i = 0; i < diff.rows; i++) {
            for (int j = 0; j < diff.cols; j++) {
                thresh.at<uchar>(i, j) =
                    (diff.at<uchar>(i, j) > 20) ? 255 : 0;
            }
        }

        /* ---- Visualización ---- */
        imshow("Movimiento Detectado", thresh);

        if (waitKey(1) == 'q') break;
    }

    return 0;
}
