// ----------------------------------------
// common_code.cpp
// (c) FSIV, University of Cordoba
// ----------------------------------------

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "common_code.hpp"
#include <opencv2/imgproc.hpp>

#ifndef NDEBUG
#include<opencv2/highgui.hpp>

const std::string __Debug_Padding =
"                                                                              "
"                                                                              "
"                                                                              "
"                                                                              "
"                                                                              ";
size_t __Debug_PPL = 3;
#endif

cv::Mat
fsiv_normalize_mean_var(cv::Mat const& src)
{
    assert(!src.empty() && src.channels()==1);
    cv::Mat dst;

    //TODO: normalize source image so its mean will be equal to 0.0 and
    // its var equal to 1.0.
    // Hint: use cv::meanStdDev() to get the source mean and stdev.

    std::vector <double> mean, stdev;
    cv::normalize(src, dst, 0.0, 1.0, cv::NORM_MINMAX);
    cv::meanStdDev(dst, mean, stdev); // We get the mean and standar derivation of our image

    //
#ifndef NDEBUG
    assert(!dst.empty());
    {
        std::vector<double> mean, stdev;
        cv::meanStdDev(dst, mean, stdev);
        assert(std::abs(mean[0])<=1.0e-5 && std::abs(stdev[0]-1.0)<=1.0e-5);
    }
#endif
    return dst;
}

cv::Mat
fsiv_normalize_minmax(cv::Mat const& src)
{
    assert(!src.empty() && src.channels()==1);
    cv::Mat dst;

    //TODO: normalize the source image so its mininum value will be 0.0 and its
    // maximun value be 1.0
    // Hint: use cv::normalize()

    src.convertTo(dst, CV_32FC1); // One channel image
    cv::normalize(dst, dst, 0, 1, cv::NORM_MINMAX); // Nomralization

    //

#ifndef NDEBUG
    assert(!dst.empty());
    {
        assert(dst.type()==CV_32FC1);
        double min,max;
        cv::minMaxLoc(dst, &min, &max);
        assert(std::abs(min)<=1.0e-6 && std::abs(max-1.0)<=1.0e-6);
    }
#endif
    return dst;
}

bool
string_to_ncells(const std::string& str, int n_cells[])
{
    bool ret_val = true;
    std::istringstream input(str);
    char sep;
    input >> n_cells[0] >> sep >> n_cells[1];
    if (!input)
        ret_val = false;
    else
        ret_val = ((n_cells[0]*n_cells[1]) > 0);
    return ret_val;
}

// Loads the classes and their descriptions from the dataset
bool
load_gtsrb_categories(const std::string& dataset_pathname,
                      std::vector<int>& cats,
                      std::vector<std::string>& descs)
{
    bool ret_val = false;
    std::ifstream in(dataset_pathname+"/train/CLASSES.TXT");
    if (in)
    {
        int class_label = 0;
        char sep = ' ';
        std::string class_description;
        while(in)
        {
            in >> class_label >> sep >> sep >> sep >> class_description;
            if (in)
            {
                cats.push_back(class_label);
                descs.push_back(class_description);
            }
        }
        ret_val = true;
    }
    return ret_val;
}

// Loads training data for validation part
bool
load_gtsrb_train_metadata(const std::string& metadata_file,
                          std::vector<std::string> & lfiles,
                          std::vector<cv::Rect>& rois,
                          cv::Mat & labels)
{
    bool ret_val = true;
    DEBUG(1, "Loading metadata from file '"<< metadata_file << "'." << std::endl);
    std::ifstream input (metadata_file);
    if (input)
    {
        std::vector<int> labels_v;
        std::istringstream line;
        std::string dataset_path;

        size_t pos = metadata_file.rfind("/");
        if (pos != std::string::npos)
            dataset_path=metadata_file.substr(0, pos);
        else
            dataset_path=".";
        DEBUG(2, "\tDataset path is: "<< dataset_path << "'." << std::endl);
        while(input && ret_val)
        {
            std::string buffer;
            //get a line.
            input >> buffer;
            if (input)
            {
                DEBUG(3,"\tDecoding line: '"<< buffer << "'."<< std::endl);
                //replace ; by ' '
                for(size_t i=0;i<buffer.size(); ++i)
                    if (buffer[i]==';')
                        buffer[i]=' ';
                //get the line's metadata.
                std::istringstream line (buffer);
                std::string filename;
                int w, h, x1, y1, x2, y2, label;
                line >> filename >> w >> h >> x1 >> y1 >> x2 >> y2 >> label;
                if (line)
                {
                    lfiles.push_back(dataset_path+'/'+filename);
                    rois.push_back(cv::Rect(x1, y1, x2-x1, y2-y1));
                    labels_v.push_back(label);
                    DEBUG(3,"\tDecoded fname: '" << lfiles.back() << "'." << std::endl);
                    DEBUG(3,"\tDecoded roi  :  " << rois.back() << std::endl);
                    DEBUG(3,"\tDecoded label:  " << labels_v.back() << std::endl);
                }
                else
                    ret_val = false;
            }
        }
        if (ret_val)
        {
            //Transform vector to cv::Mat.
            labels = cv::Mat(labels_v.size(), 1, CV_32SC1);
            std::copy(labels_v.begin(), labels_v.end(), labels.begin<int>());
        }
    }
    else
        ret_val = false;
    return ret_val;
}

bool
load_gtsrb_test_metadata(const std::string& dataset_path,
                          std::vector<std::string> & lfiles,
                          std::vector<cv::Rect>& rois,
                          cv::Mat & labels)
{
    bool ret_val = true;
    std::string metadata_file = dataset_path + "/test/metadada.csv";
    DEBUG(1, "Loading metadata from file '"<< metadata_file << "'."
          << std::endl);
    std::ifstream input (metadata_file);
    if (input)
    {
        std::vector<int> labels_v;
        std::istringstream line;
        while(input && ret_val)
        {
            std::string buffer;
            //get a line.
            input >> buffer;
            if (input)
            {
                DEBUG(3,"\tDecoding line: '"<< buffer << "'."<< std::endl);
                //replace ; by ' '
                for(size_t i=0;i<buffer.size(); ++i)
                    if (buffer[i]==';')
                        buffer[i]=' ';
                //get the line's metadata.
                std::istringstream line (buffer);
                std::string filename;
                int w, h, x1, y1, x2, y2, label;
                line >> filename >> w >> h >> x1 >> y1 >> x2 >> y2 >> label;
                if (line)
                {
                    lfiles.push_back(dataset_path+"/test/"+filename);
                    rois.push_back(cv::Rect(x1, y1, x2-x1, y2-y1));
                    labels_v.push_back(label);
                    DEBUG(3,"\tDecoded fname: '" << lfiles.back() << "'." << std::endl);
                    DEBUG(3,"\tDecoded roi  :  " << rois.back() << std::endl);
                    DEBUG(3,"\tDecoded label:  " << labels_v.back() << std::endl);
                }
                else
                    ret_val = false;
            }
        }
        if (ret_val)
        {
            //Transform vector to cv::Mat.
            labels = cv::Mat(labels_v.size(), 1, CV_32SC1);
            std::copy(labels_v.begin(), labels_v.end(), labels.begin<int>());
        }
    }
    else
        ret_val = false;
    return ret_val;
}

bool fsiv_desc_simple_gray(const cv::Mat & image, cv::Mat & desc)
{
    //TODO: compute the descriptor and save into desc
    // I assume that this descriptor is created by taking the pixels in grey-scale and putting them into a one dimension image
    
    cv::Mat greyImg;
    /*
    cv::imshow("Imagen",image);
    cv::waitKey(0);
    cv::cvtColor(image, greyImg, cv::COLOR_BGR2GRAY); // Original image in grey-scale
    */

    cv::Mat auxImg(cv::Size(1, greyImg.cols*greyImg.rows), CV_32F);
    int i = 0;

    for(int x=0 ; x < greyImg.rows ; x++){
        for(int y=0 ; y < greyImg.cols ; y++){
            auxImg.at<uchar>(0,i) = greyImg.at<uchar>(x,y);
            i++;
        }
    }

    //Now we create our descriptor
    auxImg.copyTo(desc);

    return true;
}

// We calculate a pool of descriptors
bool
fsiv_compute_desc_from_list(const std::vector<std::string> & lfiles,
                      const std::vector<cv::Rect>& rois,
                      const cv::Size& canonical_size,
                      cv::Mat & l_descs, const int desctype,
                      const int img_norm, bool hist_norm)
{
    DEBUG(1, "Computing lbp descriptors from files" << std::endl);
    bool ret_val = true;
    for (size_t i =0; i < lfiles.size() && ret_val; i++)
    {
        DEBUG(2, "\t Processing image: '" << lfiles[i] << "'." << std::endl);
        cv::Mat image = cv::imread(lfiles[i], cv::IMREAD_GRAYSCALE);       
        if (!image.empty())
        {
            image.convertTo(image, CV_32F, 1.0/255.0, 0.0);
#ifndef NDEBUG
            if (__Debug_Level>=3)
            {
                cv::imshow("IMAGE", image);
                cv::imshow("ROI", image(rois[i]));
            }
#endif
            if (img_norm==1)
                image = fsiv_normalize_minmax(image);
            else if (img_norm==2)
                image = fsiv_normalize_mean_var(image);

            cv::Mat canonical_img;
            cv::resize(image(rois[i]), canonical_img, canonical_size);            

            // TODO: compute the selected descriptor
            cv::Mat aux_desc;

            if (desctype == 0) { // Simple grey descriptor
                fsiv_desc_simple_gray(canonical_img, aux_desc);
      
            } else { 
                // The other type of descriptor is LBP
                cv::Mat lbp;
                int ncells[2];
                ncells[1]=5; //This values can change, we are going to use always 5x5
                ncells[2]=5;

                fsiv_lbp(canonical_img, lbp);
 
                fsiv_desc_lbp(lbp, aux_desc, ncells, hist_norm);
            }

            if (i==0) // Finally, we add the descriptor into the array of descriptors
            {

                l_descs = cv::Mat(lfiles.size(), aux_desc.cols, CV_32FC1);
                aux_desc.copyTo(l_descs.row(0));
                                
            }
            else
                aux_desc.copyTo(l_descs.row(i));
                                
#ifndef NDEBUG
            if (__Debug_Level>=3)
            {
                if ((cv::waitKey(0)&0xff)==27)
                    return false;
            }
#endif
        }
        else
            ret_val = false;
    }
#ifndef NDEBUG
            if (__Debug_Level>=3)
                cv::destroyAllWindows();
#endif
    return ret_val;
}


float
compute_file_size(std::string const& fname, const long units)
{
    float size = -1.0;
    std::ifstream file (fname);
    if (file)
    {
        file.seekg (0, file.end);
        long length = file.tellg();
        size = static_cast<float>(length) / static_cast<float>(units);
    }
    return size;
}

void
fsiv_lbp(const cv::Mat& img, cv::Mat& lbp){
    
    // · Documentation: https://www.bytefish.de/blog/local_binary_patterns.html
    lbp = cv::Mat::zeros(img.rows, img.cols, CV_8UC1); // We fill the image with zeros

    for (auto i = 1; i < img.rows - 1; i++){
		for (auto j = 1; j < img.cols - 1; j++){
			
            float center = img.at<float>(i, j); // We take our central pixel
			uchar code = 0;

			code |= ( img.at<float>(i, j - 1) > center ) << 7; // We compare the pixels
			code |= ( img.at<float>(i + 1, j - 1) > center ) << 6;
			code |= ( img.at<float>(i + 1, j) > center ) << 5;
			code |= ( img.at<float>(i + 1, j + 1) > center ) << 4;
			code |= ( img.at<float>(i, j + 1) > center ) << 3;
			code |= ( img.at<float>(i - 1, j + 1) > center ) << 2;
			code |= ( img.at<float>(i - 1, j) > center ) << 1;
			code |= ( img.at<float>(i - 1, j - 1) > center ) << 0;

			lbp.at<uchar>(i, j - 1) = code;
		}
	}
}


void 
fsiv_desc_lbp(const cv::Mat& lbp, cv::Mat& desc, const int* ncells, const bool normalize){

    // The idea is split the lbp into cells and calculate the histogram for each cells. After this, we concatenate all the histograms
    // to obtain the descriptor
    std::vector<cv::Mat> histograms(ncells[0] * ncells[1]);
    std::vector<cv::Mat> cell_vec;


    const int cell_h = cvFloor(double(lbp.rows) / ncells[0]);
	const int cell_w = cvFloor(double(lbp.cols) / ncells[1]);

    // We split the lbp image
    for(int i=0; i<=lbp.rows - cell_h; ){
        for (int j = 0; j <= lbp.cols - cell_w; ){
            
            // We only want one region of the lbp image, that is why we use Rect
            cv::Mat aux = lbp(cv::Rect(j, i , cell_w, cell_h)); 
            cell_vec.push_back(aux.clone());
            j=j+cell_w;
        }
        i=i+cell_h;
    }
                          std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
    // After this, all histograms are calculated
    for(int i=0; i<cell_vec.size(); i++){
        		fsiv_lbp_hist(cell_vec[i], histograms[i], normalize);

    }

    cv::hconcat(histograms, desc);

}

void
fsiv_lbp_hist(const cv::Mat & lbp, cv::Mat & lbp_hist, const bool hist_norm){
      
	float hranges[] = {0, 256};
	const float* phranges = hranges;   
    int histSize = 256;
          
    cv::calcHist(&lbp, 1, 0, cv::Mat(), lbp_hist, 1, &histSize, &phranges, true, false);

    cv::transpose(lbp_hist, lbp_hist);

    if (hist_norm){
		cv::normalize(lbp_hist, lbp_hist, 1.0, 0.0, cv::NORM_L1);
	}

    lbp_hist.convertTo(lbp_hist, CV_32FC1);
}