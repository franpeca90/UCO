
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;

//If we create the objects here, all fuctions of the program can access to this object
static cv::Mat image; //Object that will storage our image
static cv::Mat imageAux;
static cv::Point point; //Point is a class of CV
static cv::Rect area; //Rect is a class of CV
static bool flag_mouse = false;
static bool flag_selected = false;

static void on_mouse(int event, int x, int y, int flags, void* param){

  if(flag_mouse == true){ //If we left click with our mouse
    //we calculate the coordinates in absolute value in case user creates a rectangle that gives negative values
    //to our points
    area.x = min(x, point.x);
    area.y = min(y, point.y);
    //We storage in class rect's width and height variables the absolute value of our operation
    area.width = abs(x-point.x);
    area.height = abs(y-point.y);
  }

  if (event == cv::EVENT_LBUTTONDOWN){
    point = cv::Point(x, y);
    area = cv::Rect(x, y, 0, 0); //We use CV Class Rect to create the area of our rectangle.
    flag_mouse = true; //Flag in case we click
  } else if (event = cv::EVENT_LBUTTONUP){
    flag_mouse = false; //We stop selecting the area
    flag_selected = true; //When we botton up, it means we selected an area
  }

  image.copyTo(imageAux);
  cv::rectangle(imageAux, area, cv::Scalar(0, 0, 255), 1, 8, 0);
  cv::imshow("image", imageAux);

}

int main(int argc, char** argv){

try{

  if(argc!=2){
    cerr<<"Usage:image"<<endl; //If case user writes one or mor than two parameters
    return 0; //we end the program
  }

  image = cv::imread(argv[1]); //We create a Mat object where we storage the user's picture

  cv::namedWindow("image"); //We create the name of the window where the picture is going to be displayed

  cv::setMouseCallback("image",on_mouse); //Sets mouse handler for "My image" window

  cv::imshow("image",image); //We show the image

  cv::waitKey(0); //We keep the windows open

  int d = 1;
	while (d == 1)
	{
		if (flag_selected == true)
		{
			cv::Mat crop = image(area);
			cv::namedWindow("crop");
			cv::imshow("crop", crop);
			d = 0;
		}
		cv::waitKey(10);
	}

} catch(std::exception &ex) { //Se toma la excepcion encontrada
    cout<<ex.what()<<endl; //Se muestra el error
}
}















cv::Mat imgRealce;
 img.copyTo(imgRealce);
 int negro;
 int punto1[2]={std::min(coords[0],coords[2]),std::min(coords[1],coords[3])};
 int punto2[2]={std::max(coords[0],coords[2]),std::max(coords[1],coords[3])};

 for (int i = 0; i < imgRealce.rows; i++) {
   for (int j = 0; j < imgRealce.cols; j++) {
     if (not (i>punto1[1] and i < punto2[1] and j > punto1[0] and j < punto2[0])) {
       cv::Vec3b v1 = imgRealce.at<cv::Vec3b>(i, j);
       negro=(int)((v1[0]+v1[1]+v1[2])/3);
       v1[0]=negro;
       v1[1]=negro;
       v1[2]=negro;
       imgRealce.at<cv::Vec3b>(i, j)=v1;
     }
   }
 }
