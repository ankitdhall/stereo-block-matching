#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

inline int square(int x){ return x*x; }


int main(int argc, char** argv)
{
	if(argc != 2)
	{
		cout << "Enter director index as argument! \n exiting... \n";
		exit(0);
	}
    Mat left, right;
	Mat disp_img;
	// subset of the Middlebury data
	String dir[] = {"img/Art", "img/Books", "img/Dolls", "img/Laundry", "img/Moebius", "img/Reindeer"};
	String left_ = "/view1.png", right_ = "/view5.png";
	
	int choice = atoi(argv[1]);

	cout<< "\n Opening directory: " << dir[choice] << "\n";

	left = imread(dir[choice] + left_);
	right = imread(dir[choice] + right_);
	
	disp_img = Mat::zeros(left.rows, left.cols, CV_8UC1);
	
	int ROW=left.rows, COL=left.cols;
	// stores the disparity and sum of squared distance (SSD)
	int disp[ROW][COL], SSD_value[ROW][COL];

	// set range to search from current pixel
	int disparity_min = -50, disparity_max = 50;
	int disparity_range = disparity_max - disparity_min;
	int half_block_size = 8;
	int MAX_DISP=-1, MIN_DISP=10e6;

	int SSD=0, l_r, l_c, r_r, r_c;

	for(int i=0; i<ROW; i++)
	{
		for(int j=0; j<COL; j++)
		{
			disp[i][j]=0;
			SSD_value[i][j]=10e8;
		}
	}
	
	for(int i=0+half_block_size; i<left.rows-half_block_size; i++)
	{
		for(int j=0+half_block_size; j<left.cols-half_block_size; j++)
		{

			for(int range=disparity_min; range<=disparity_max; range++)
			{
				SSD = 0;

				for(l_r = -half_block_size + i; l_r <= half_block_size + i; l_r++)
				{
					for(l_c = -half_block_size + j; l_c <= half_block_size + j; l_c++)
					{
						r_r = l_r;
						r_c = l_c + range;

						SSD += square(left.at<cv::Vec3b>(l_r,l_c)[0] - right.at<cv::Vec3b>(r_r, min(max(0, r_c), COL-1))[0])
							+ square(left.at<cv::Vec3b>(l_r,l_c)[1] - right.at<cv::Vec3b>(r_r, min(max(0, r_c), COL-1))[1])
							+ square(left.at<cv::Vec3b>(l_r,l_c)[2] - right.at<cv::Vec3b>(r_r, min(max(0, r_c), COL-1))[2]);
					}
				}

				if(SSD < SSD_value[i][j])
				{
					disp[i][j] = range;
					SSD_value[i][j] = SSD;
				}
			}


		}

		// visualize the disparity image in grayscale
		for(int i=0; i<ROW; i++)
		{
			for(int j=0; j<COL; j++)
			{
				disp_img.at<uchar>(i,j) = 63+(int)192.0*(disp[i][j]-disparity_min)/disparity_range;
				if(MAX_DISP < disp[i][j])
					MAX_DISP = disp[i][j];
				if(disp[i][j] < MIN_DISP)
					MIN_DISP = disp[i][j];
			}
		}
		imshow("disparity", disp_img);
		waitKey(1);
	}

	cout << "MAX_DISP:" << MAX_DISP << endl;
	cout << "MIN_DISP:" << MIN_DISP << endl;

	for(int i=0; i<ROW; i++)
	{
		for(int j=0; j<COL; j++)
		{
			disp_img.at<uchar>(i,j) = 63+(int)192.0*(disp[i][j]-disparity_min)/disparity_range;
		}
	}
	imshow("disparity", disp_img);
    waitKey(0);

    return(0);
}
