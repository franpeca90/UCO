#include <iostream>
#include <exception>
//Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//parametros de linea de comandos
const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{@inputImage    |<none>| image to edit   }"
    "{@outputImage   |salida.jpg| name of the output image  }"
    ;

//structura para operar con la imagen
struct Variables{
  int coords[4];
  cv::Mat imgRealce;
  cv::Mat imgSinCuadrado;
  cv::Mat img;
  int flag;
};

//funcion que captura el ratón
void on_mouse(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN)//si se presiona el botón izquierdo del ratón se guardan las coordendas y se desactiva el flag y se resetea la imagen
    {
      static_cast<struct Variables*>(userdata)->img.copyTo(static_cast<struct Variables*>(userdata)->imgRealce);
      static_cast<struct Variables*>(userdata)->img.copyTo(static_cast<struct Variables*>(userdata)->imgSinCuadrado);
      static_cast<struct Variables*>(userdata)->coords[0] = x;
      static_cast<struct Variables*>(userdata)->coords[1] = y;
      static_cast<struct Variables*>(userdata)->flag=0;
    }else if(event==cv::EVENT_LBUTTONUP){//si se levanta el botón del ratón se modifica la imagen poniendo en monocromo todo lo que esté fuera del cuadrado formado por las coordenadas
      static_cast<struct Variables*>(userdata)->coords[2] = x;
      static_cast<struct Variables*>(userdata)->coords[3] = y;
      if (static_cast<struct Variables*>(userdata)->coords[0]!=-1 and   static_cast<struct Variables*>(userdata)->coords[3]!=-1) {
        int negro, negro2;
        //se hace en dos imagenes para guardar la imagen sin el cuadrado de selección
        int punto1[2]={std::min(static_cast<struct Variables*>(userdata)->coords[0],static_cast<struct Variables*>(userdata)->coords[2]),std::min(static_cast<struct Variables*>(userdata)->coords[1],static_cast<struct Variables*>(userdata)->coords[3])};
        int punto2[2]={std::max(static_cast<struct Variables*>(userdata)->coords[0],static_cast<struct Variables*>(userdata)->coords[2]),std::max(static_cast<struct Variables*>(userdata)->coords[1],static_cast<struct Variables*>(userdata)->coords[3])};
        for (int i = 0; i < static_cast<struct Variables*>(userdata)->imgRealce.rows; i++) {
          for (int j = 0; j < static_cast<struct Variables*>(userdata)->imgRealce.cols; j++) {
            if (not (i>punto1[1] and i < punto2[1] and j > punto1[0] and j < punto2[0])) {
              cv::Vec3b v1 = static_cast<struct Variables*>(userdata)->imgRealce.at<cv::Vec3b>(i, j);
              cv::Vec3b v2 = static_cast<struct Variables*>(userdata)->imgSinCuadrado.at<cv::Vec3b>(i, j);
              negro=(int)((v1[0]+v1[1]+v1[2])/3);
              negro2=(int)((v2[0]+v2[1]+v2[2])/3);
              v1[0]=negro;
              v1[1]=negro;
              v1[2]=negro;
              v2[0]=negro2;
              v2[1]=negro2;
              v2[2]=negro2;
              static_cast<struct Variables*>(userdata)->imgRealce.at<cv::Vec3b>(i, j)=v1;
              static_cast<struct Variables*>(userdata)->imgSinCuadrado.at<cv::Vec3b>(i, j)=v2;
            }
          }
        }
        //se activa el flag para que no se forme el cuadrado al mover el ratón
        static_cast<struct Variables*>(userdata)->flag=1;
      }
      //se crea el cuadrado de selección si existe un punto inicial
    }else if(event==cv::EVENT_MOUSEMOVE and static_cast<struct Variables*>(userdata)->flag==0 and static_cast<struct Variables*>(userdata)->coords[0]!=-1){
          static_cast<struct Variables*>(userdata)->img.copyTo(static_cast<struct Variables*>(userdata)->imgRealce);
          static_cast<struct Variables*>(userdata)->coords[2] = x;
          static_cast<struct Variables*>(userdata)->coords[3] = y;
          cv::Point p1(static_cast<struct Variables*>(userdata)->coords[0],static_cast<struct Variables*>(userdata)->coords[1]),
          p2(static_cast<struct Variables*>(userdata)->coords[2],static_cast<struct Variables*>(userdata)->coords[3]);
          cv::rectangle(static_cast<struct Variables*>(userdata)->imgRealce,p1,p2,cv::Scalar(255,255,0),0.1,8,0);
    }
}


int main(int argc, char* const* argv){
  int retCode=EXIT_SUCCESS;

  try {

    //se declaran dos structuras, una para pasar a on_mouse y otra para introducir los valores iniciales
    struct Variables *varp,var;

      //Configuramos el parser
      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Este programa sirve para hacer el realce de una imagen en el rectangulo definido por el arrastre del ratón");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }
      cv::String img_name = parser.get<cv::String>(0);

      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

      //Cargamos la imagen en una matriz
      var.img=cv::imread(img_name, cv::IMREAD_COLOR);

      //Comprobamos si hemos podido cargar la imagen
      if (var.img.empty())
      {
         std::cerr << "Error: no he podido abrir el fichero '" << img_name << "'." << std::endl;
         return EXIT_FAILURE;
      }

      //Creamos la ventana
      cv::namedWindow("IMG");

      //Inicializamos las coordenadas
      int coordenadas[4]={-1, -1,-1,-1};
      var.coords[0] = coordenadas[0];
      var.coords[1] = coordenadas[1];
      var.coords[2] = coordenadas[2];
      var.coords[3] = coordenadas[3];
      //inicializamos el puntero
      varp=&var;
      //llamamos a la función on_mouse
      cv::setMouseCallback ("IMG", on_mouse, varp);


      int key = 255;

      //copiamos las imágenes
      var.img.copyTo(var.imgRealce);
      var.img.copyTo(var.imgSinCuadrado);

      //mientras no se pulse una tecla se actualiza la imagen para visualizar los cambios
      while (key==255)
      {
         //muestro el frame.
         cv::imshow("IMG", var.imgRealce);
         key = cv::waitKey(34) & 0xff;

      }

      //se muestra la imagen final y se decide si se guarda o no
      cv::imshow("IMG", var.imgSinCuadrado);
      key = cv::waitKey(0) & 0xff;
      if (key!=27) {
        imwrite(parser.get<cv::String>(1),var.imgSinCuadrado);
      }


  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
