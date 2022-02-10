#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;

using namespace cv; // Recordar que las funciones tienen su propio espacio de nombres


// Es contar el numero de veces que sucede cada intensidad respectivamente
void calcular_histograma(cv::Mat img , vector<int> img_histogram) {
    for(int i=0 ; i<img.rows ; i++){ // Vamos a traves de filas y columnas
        for(int j=0 ; j<img.cols ; j++){
            int val = img.at<uchar>(i,j); // Para cada misma intensidad
            img_histogram[val] = img_histogram[val] + 1; // aumentamos el numero de veces que aparece
         }
    }
}

// El acumulativo es sumar el numero de sucesos de la posicion anterior a la actual
void calcular_histograma_acumulativo(vector<int> img_histogram, vector<double> acc_histogram){
    acc_histogram[0] = img_histogram[0]; // No va dentro del for porque no hay un elemento anterior al 0
    for(int i=1 ; i<acc_histogram.size() ; i++){
        acc_histogram[i] = img_histogram[i] + acc_histogram[i-1]; // i-1, lo anterior
    }
}

int main(int argc,char **argv){

    // Leer una imagen
    Mat image; // Creo el objeto imagen
    image = imread(argv[1]); // Leo la imagen

    // Mostrar una imagen
    namedWindow("Nombre"); // Creo la ventana con el nombre
    imshow("Nombre", image); // Muestro la imagen en la ventana creada

    //waitKey(0); // Espero el tiempo indicado hasta que se pulse una tecla cualquiera
    // Esperar hasta presionar una tecla
    int c;
    while(c!=27){  //Espero hasta que se presione ESC
	    c=cv::waitKey(0);
    }

    Mat aux_image=image.clone(); // Creo una copia

    //--------------------------------------------------


    // Acceder a los valores de los pixeles -  https://learntutorials.net/es/opencv/topic/1957/acceso-a-pixeles
    
    // --> Grey-scale con "at"
//    image.at<uchar>(30,10) = 100; // Le puedo dar una valor
//    cout << "El pixel fila 30 columna 10 tiene el vlaor: " << (float)image.at<uchar>(30,10) << endl;
    
    // --> RGB con "at"
    Vec3b pixel_aux = image.at<Vec3b>(30,10); // Tomamos el pixel con B G R
    uchar B = pixel_aux[0]; // Ya tenemos los valores por separado
    uchar G = pixel_aux[1];
    uchar R = pixel_aux[2];

    // Podemos cambiar los colores de una imagen accediendo a los pixeles:
    for(int i=0 ; i<image.rows ; i++){ // Vamos a través de la imagen
        for(int j=0 ; j<image.cols ; j++){
      
       /*   // Tomamos el pixel de cualquier posicion
            Vec3b& aux = image.at<Vec3b>(i,j);
            // Accedemos a sus valores (ya que tenemos un PUNTERO, estaremos accediendo directamente a ese pixel)
            aux[0] = 255; //B
            aux[1] = 0; //G
            aux[2] = 0; //R*/

            // Podemos resumir el paso anterior sin tener que usar un puntero
            image.at<Vec3b>(i,j)[0] = 255;
            image.at<Vec3b>(i,j)[1] = 15;
            image.at<Vec3b>(i,j)[3] = 90;
        }
    }

    namedWindow("Nombre"); // Creo la ventana con el nombre
    imshow("Nombre", image); // Muestro la imagen en la ventana creada
    waitKey(0);
    // --> Punto "ptr"
    // https://docs.opencv.org/2.4/modules/core/doc/basic_structures.html?highlight=mat#mat-ptr
    // Da el inicio de la FILA. Usa uchar para grey-scale y vec3b para rgb (bgr)


    //--------------------------------------------------

    // Calcular el histograma de una imagen
    vector<int> img_histogram(256,0); // En blanco y negro son 256 elementos. Valor inicial de 0  [!]
    calcular_histograma(aux_image, img_histogram);

    // Calculamos el histograma acumulativo
    vector<double> acc_histogram(256,0); // En blanco y negro 256 elementos DOUBLE inicializados a 0 [!]
    calcular_histograma_acumulativo(img_histogram, acc_histogram);

    // Equializar una imagen 
    // Calculamos el histograma y su acumulativo
    // Usamos un factor, dado por el tamaño de la imagen
    double factor = (double)255 / double(image.rows*image.cols);
    // Obtenemos el factor para cada valor
    vector<double> factores(256,0);
    for(int i=0 ; i<acc_histogram.size() ; i++){
        factores[i] = acc_histogram[i]*factor;
    }
    // Usamos los factores anteriormente calculados como nuevos valores de los pixeles
    for(int i=0 ; i<aux_image.rows ; i++){
        for(int j=0; j<aux_image.cols ; j++){
            aux_image.at<uchar>(i,j) = factores[aux_image.at<uchar>(i,j)]; // La posicion del nuevo valor en el vector viene dada por el pixel correspondiente
        }
    }
    //Falla, pero no veo el fallo
    namedWindow("Nombre"); // Creo la ventana con el nombress
    imshow("Nombre", aux_image); // Muestro la imagen en la ventana creada
    waitKey(0);


    //--------------------------------------------------
    // ------ Equalizar usando una funcion
    //--------------------------------------------------

    // Leer una imagen
    Mat image2; // Creo el objeto imagen
    image2 = imread(argv[1]); // Leo la imagen en blanco y negro
    cvtColor(image2, image2, COLOR_RGB2GRAY);
    Mat aux2;
    image2.copyTo(aux2);

    // Equalizar una imagen solo con una funcion (Cuidado, preguntar si deja usarla en el examen en caso de que lo pida)
    equalizeHist(aux2,aux2);
    
    namedWindow("Image");
    imshow("Image", image2);

    namedWindow("Modified image");
    imshow("Modified image", aux2);
    waitKey(0);
}