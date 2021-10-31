#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//./augReal rows cols size intrisics.yml <input video-file|cam-idx>

int main(int argc, char** argv){
try {

    vector<Point2f> pattern_centers;

    Size nSize(stoi(argv[1]),stoi(argv[2])); //Number of corners inside of the pattern, not edges of the pattern
    Size winSize = Size(stoi(argv[1])*2+1, stoi(argv[2])*2+1);
    Size zeroZone(-1,-1);
    //Termination of the iterative process of corner refinement
    TermCriteria termcrit(TermCriteria::COUNT|TermCriteria::EPS,20,0.03);

    string pathToVideo = argv[5];
    VideoCapture video(pathToVideo); //We use the clas 'VideoCapture' to use the video for the 3D Cube.
    //We have created the object video, now we want to get every frame of the video and read it as an image

    Mat video_frame;
    Mat grey_video_frame;

    while(video.grab()){ //We get the video frames, returns true in that case, false if there is no frames to get

        video.retrieve(video_frame); //We put the grabbed frame in the while() into the video_frame image object.
      
        cvtColor(video_frame, grey_video_frame, COLOR_BGR2GRAY); //We change the color of the frame
      
        bool flag_pattern = findChessboardCorners(grey_video_frame, nSize, pattern_centers); //Returns different than 0
        //if it find the cornosers of the chessboard pattern.

        if(flag_pattern==false){
            return -1;
        }

        cornerSubPix(grey_video_frame, pattern_centers, winSize, zeroZone, termcrit); //"Half of the side length of the search window"
        //We stemate the camera with respect the board by solving the PnP
        

        /*
        imshow("Video frames", video_frame);
        waitKey(50);
        */
    }


} catch (exception &ex) {
    cout<< "Error in function: " << ex.what()<<endl;
}
}