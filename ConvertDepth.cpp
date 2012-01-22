#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <string.h>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


using namespace std;

std::vector<string> all_depth_files;

void setFileList(std::string target_path){
  boost::filesystem::directory_iterator end_itr; // Default ctor yields past-the-end
  for( boost::filesystem::directory_iterator i( target_path ); i != end_itr; ++i )
  {

    if ( i->leaf().find("bmp") != string::npos){
      all_depth_files.push_back(i->leaf() );
    } 
  }
  printf("There are %d depth files in this folder. \n", all_depth_files.size()); 
}

int main(int argc, char** argv) {
  if (argc <= 1){
    printf("Please supply the directory \n");
    return -1;
  }

  string imdir = argv[1];

  setFileList(imdir);
  unsigned int distance_from_cam;
  double min_range_ = 500;
  double max_range_ = 5000;

  system("mkdir convdepth");

  for (unsigned int im=0; im < all_depth_files.size(); im++){

    IplImage* depthImage = cvLoadImage( (imdir + "/" + all_depth_files[im]).c_str(), CV_LOAD_IMAGE_COLOR);
    cout << "Image #" << im << " out of " << all_depth_files.size() << endl;
    IplImage* newDepthImage1=cvCreateImage(cvSize(640,480),IPL_DEPTH_8U,1);
    for (int i = 0; i < depthImage->width; i++)
    {
      for (int j = 0; j < depthImage->height; j++)
      {
        int part1 = 0xFF & depthImage->imageData[3 * (j * depthImage->width + i) + 0];
        int part2 = 0xFF & depthImage->imageData[3 * (j * depthImage->width + i) + 1];
        distance_from_cam = (part1 << 8) + part2;
        unsigned int newdepth = (255*((distance_from_cam-min_range_)/(max_range_-min_range_)));
        newDepthImage1->imageData[(j * depthImage->width + i)] = part1; 
      }
    }
    cvSaveImage(("convdepth/" + all_depth_files[im]).c_str(), newDepthImage1);
    cvReleaseImage(&depthImage);
    cvReleaseImage(&newDepthImage1);
  }

  return 0;
}
