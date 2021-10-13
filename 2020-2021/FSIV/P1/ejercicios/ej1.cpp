#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

//OpenCV objects that can be use in all the program
Mat image;
Point point;
Point point2;
Rect area;

//Flags to know if the user clicked or not
bool flag_mouse = false;
bool flag_selected = false;

Mat imageAux;

void on_mouse(int event, int x, int y, int flags, void* coordinates) {

	if (flag_mouse==true)
	{
		//With this we will create the animation of the rectangle
		area.x = min(x, point.x);
		area.y = min(y, point.y);
		area.width = abs(x - point.x);
		area.height = abs(y - point.y);

	}

  if(event == EVENT_LBUTTONDOWN){
    point = Point(x, y);
		area = Rect(x, y, 0, 0);
		flag_mouse = true;
		//We share the first points of the rectangle
		//Casting is need because coordinates is void*
		static_cast<int*>(coordinates)[0]= x;
		static_cast<int*>(coordinates)[1]= y;

  } else if(event == EVENT_LBUTTONUP){
    flag_mouse = false;
		flag_selected = true;
		//We do the same as before but once the rectangle is done
		static_cast<int*>(coordinates)[2]= x;
		static_cast<int*>(coordinates)[3]= y;
  }

	//We create the rectangle area.
	//We refresh the image everytime the rectangle changes his shape.
	//Actually the animation is a lot images, so what we do is copy the image
	//with differente rectangle, little by little and very quickly,
	//that is how we create the animation.
	image.copyTo(imageAux);
	rectangle(imageAux, area, Scalar(0, 0, 255), 1, 8, 0);
	imshow("image", imageAux);
}

int main(int argc, char** argv) {

try {

for(;;){
		if(argc!=2){
	    std::cerr<<"Usage:image"<<std::endl; //If case user writes one or mor than two parameters
	    return 0; //We end the program
		}

		image = imread(argv[1]);

		if (image.empty()){
			 std::cerr << "No se ha podido abrir el fichero" << std::endl;
			 return 0;
		}

		int coordinates[4];
		int pointA[2];
		int pointB[2];

	  namedWindow("image");

		setMouseCallback("image", on_mouse, coordinates);

		imshow("image", image);

		cv::waitKey(0) & 0xff;

		//We storage the minimun coordinate of the X and Y
		pointA[0]=std::min(coordinates[0],coordinates[2]);
		pointA[1]=std::min(coordinates[1],coordinates[3]);
		//We do the same but with the maximun
		pointB[0]=std::max(coordinates[0],coordinates[2]);
		pointB[1]=std::max(coordinates[1],coordinates[3]);

		//After this, we have the square animation and the value of
		//this square in variables. Now we can color the rest of the
		//image with black and white

		int flag = 1;
		while (flag == 1)
		{
			if (flag_selected)
			{
				//If writte 'area' we will crop the image
				Mat blackWhite;
				image.copyTo(blackWhite);
				namedWindow("blackWhite");

				//We go across the image to change the colors
				for (int i=0; i<blackWhite.rows; i++){
					for(int j=0; j<blackWhite.cols; j++){
						//Now we DON NOT want to color in the rectangle
						//so if we are not in the rectangle, we color the image to black and white
							if (not (i>pointA[1] and i < pointB[1] and j > pointA[0] and j < pointB[0])) {

								//Type of data of OpenCV that store a pixel of our images
								//We take the pixel of i,j and we change it color.
								cv::Vec3b ptrV = blackWhite.at<cv::Vec3b>(i, j);

								//The adds of the values of the pixel divided by 3
								//will give us the value on grey scale. We must cast to int

		            ptrV[0]=(int)((ptrV[0]+ptrV[1]+ptrV[2])/3);
		            ptrV[1]=(int)((ptrV[0]+ptrV[1]+ptrV[2])/3);
		            ptrV[2]=(int)((ptrV[0]+ptrV[1]+ptrV[2])/3);

								//After this we have to save the values in the real pixel of our image
		            blackWhite.at<cv::Vec3b>(i, j)=ptrV;
		          }

					}
				}
				//We show in another window the black and white image
				imshow("blackWhite", blackWhite);
				flag = 0;
			}
			std::cout<<"A:"<<pointA[0]<<","<<pointA[1]<<std::endl;
			std::cout<<"B:"<<pointB[0]<<","<<pointB[1]<<std::endl;
			waitKey(0);
		}
	}
	} catch(std::exception &ex) {
	    std::cout<<ex.what()<<std::endl;
	}
}
