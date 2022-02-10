#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;

using namespace cv; // Recordar que las funciones tienen su propio espacio de nombres


int main(int argc,char **argv){
    
    // -- KNearest --
    cv::Ptr<cv::ml::KNearest> knn;
    knn = cv::ml::KNearest::create();	

    // Setting of BRUTE_FORCE, as classifier and hyperparameter K
    knn -> setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
    knn->setIsClassifier(true);
    // K means the k closest patterns
    knn->setDefaultK(knn_K);  


    // -- KNearest --
    cv::Ptr<cv::ml::SVM> svm;
    svm = cv::ml::SVM::create();

    // Setting as classifier
     svm->setType(cv::ml::SVM::C_SVC);

    // Setting hyperparameters
    svm->setC(svm_C);
    svm->setKernel(svm_K);
    svm->setGamma(svm_G);
    svm->setDegree(svm_D);


    // -- RTrees --
    cv::Ptr<cv::ml::RTrees> rtrees;
    rtrees->cv::ml::RTrees::create();

    // Setting hyperparameter
    rtrees->setActiveVarCount(rtrees_V);

    // Setting max number of trees
    rtrees->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, rtrees_T, rtrees_E));

    // Independiente del clasificador:
    cv::Ptr<cv::ml::TrainData> train_data = cv::ml::TrainData::create(patterns, cv::ml::SampleTypes::ROW_SAMPLE, labels);
    clf->train(train_data)
}