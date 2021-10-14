/****************************************
 * Autor: Francisco Javier Perez Castillo
 * Universidad de Córdoba (Spain)
 * 
 * Foreground highlight
 * 
 * **************************************/
#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include "opencv2/imgproc.hpp" //for rectangle options
#include <iostream>

using namespace std;
using namespace cv;

Mat user_image;
bool flag_drag = false;
bool flag_selected = false;

void mouse_handler( int event, int x, int y, int flags, void* param ){

    vector<Point>* pointsPtr = (vector<Point>*)param;
    Mat imageAux;

    user_image.copyTo(imageAux);

    //Initial elements, we need this to prevent memory errors, because
    //rectangle function need values to create the rectangle and if we dont set values for it it will
    //throw an error.
    if(pointsPtr->size()==0){
        pointsPtr->push_back(Point(-1,-1));
        pointsPtr->push_back(Point(-1,-1));
    }

    //Meanwhile user keeps with left bottom clicked he can draw a rectangle
    if (flag_drag == true){
        //We remove the last position of the mouse and add the new one
        pointsPtr->pop_back();  
        pointsPtr->push_back(Point(x,y));
    }

    //If users clicks, we start creating our rectangle
    if (event == EVENT_LBUTTONDOWN){
        
        //Every time user clicks in the image he/she can create a new rectangle
        //To do this, we have to reset the vector to 0 coords
        //Then we create the initial rectangle
        pointsPtr->clear();
        pointsPtr->push_back(Point(x,y));
        //We add an "auxiliar" point that will be use if the user only does
        //one click without draggint the pointer
        pointsPtr->push_back(Point(x+1,y+1));
        //This flags means that user clicked in the image
        flag_drag = true;

    //If user stop clicking left bottom, means that the rectangle is created
    } else if (event == EVENT_LBUTTONUP){
        flag_drag = false;
        flag_selected = true;
    }

    //So we only show the rectangle if user created it
    rectangle(imageAux, pointsPtr->at(0), pointsPtr->at(1), Scalar(200, 200, 0), 1, 8, 0);
	imshow("Landscape", imageAux);
}

int main(int argc,char **argv){
try{
    //Loading of RGB image introduced as argument
    vector<Point> rectangle_points;
    vector<int> pointA {0,0};
    vector<int> pointB {0,0};
    char c;
    //Checking arguments
    if(argc!=2) {
        cerr<<"You have to insert an image as an argument"<<endl;
        return 0;
    }

    //Reading of user's image
    //Creation of Mat object, will contain the user's image
    user_image=imread(argv[1]);
    
    //Checking that the image is not empty
    if(user_image.rows==0) {
        cerr<<"Your image is empty or you wrote image's name wrongly"<<endl;
        return 0;
    }
    
    //Creates a window with the image
    namedWindow("Landscape"); //Name of the window

    //We repeat the program until user press ESC
    while(c!=27){
        //Calling mouse callback function
        setMouseCallback( "Landscape", mouse_handler, (void*) &rectangle_points ); //Casting is needed

        //The image is shown, the user will interact with it
        imshow("Landscape",user_image);//Creation and shown of the image

        //We wait until user creates the rectangle
        //We store the key user press to know when the program must end
        c=waitKey(0) & 0xff;

    //We storage the minimun coordinate of the X and Y
        pointA[0]=min(rectangle_points.at(0).x,rectangle_points.at(1).x);
        pointA[1]=min(rectangle_points.at(0).y,rectangle_points.at(1).y);
        //We do the same but with the maximun
        pointB[0]=max(rectangle_points.at(0).x,rectangle_points.at(1).x);
        pointB[1]=max(rectangle_points.at(0).y,rectangle_points.at(1).y);
        //This is needed to allow users to make the rectangle as he wants

        Mat blackWhite;
        user_image.copyTo(blackWhite);
        namedWindow("blackWhite");

        //We go across the image to change the colors
        for (int i=0; i<blackWhite.rows; i++){
            for(int j=0; j<blackWhite.cols; j++){
                //Now we DON NOT want to color in the rectangle
                //so if we are not in the rectangle, we color the image to black and white
                if (not (i>pointA[1] and i < pointB[1] and j > pointA[0] and j < pointB[0])) {
                    
                    //Type of data of OpenCV that store a pixel of our images
                    //We take the pixel of i,j and we change it color.
                    Vec3b ptrV = blackWhite.at<Vec3b>(i, j);
                
                    //The adds of the values of the pixels divided by 3
                    //will give us the values on grey scale. We must cast to int
                    ptrV[0]=(int)((ptrV[0]+ptrV[1]+ptrV[2])/3);
                    ptrV[1]=(int)((ptrV[0]+ptrV[1]+ptrV[2])/3);
                    ptrV[2]=(int)((ptrV[0]+ptrV[1]+ptrV[2])/3);

                    //We update our pixels
                    blackWhite.at<Vec3b>(i,j)=ptrV;

                } 
            }
        }
        imshow("blackWhite",blackWhite);//Creation and shown of the image
    }
}catch(std::exception &ex){
  cout<<ex.what()<<endl;
}
}
