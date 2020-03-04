// Simple algorithm that normalizes faces with respect to location, size, orientation, and lighting
// Uses 4 facial features: 
// - left eye center 
// - right eye center
// - nose tip
// - mouth center

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <fstream>
#include <iostream>
#include <cmath>

#include <stdlib.h>
#include <math.h>

extern "C" void solve_system(int, int, float**, float*, float*);

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
    // Manually extract acutal coordinates of 4 facial features from each image
    int P1_F[2] = { 26, 51 };
    int P2_F[2] = { 63, 49 };
    int P3_F[2] = { 44, 88 };
    int P4_F[2] = { 46, 69 };


    // IDEAL coordinates for each feature
    int P1[2] = { 18, 16 };
    int P2[2] = { 38, 15 };
    int P3[2] = { 33, 23 };
    int P4[2] = { 31, 31 };


    // Read in image
    Mat img = imread("C:\\Users\\Lee\\source\\repos\\PA2_pb1\\PA2_pb1\\S1\\1.pgm", IMREAD_GRAYSCALE);
    Mat dst = imread("C:\\Users\\Lee\\source\\repos\\PA2_pb1\\PA2_pb1\\S1\\1.pgm", IMREAD_GRAYSCALE);
    imshow("File", img);

    cout << "Width: " << img.cols << endl;
    cout << "Height: " << img.rows << endl << endl;

    /*
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            cout << (int)img.at<uchar>(i, j) << " ";
        }
        cout << endl;
    }
    */

    
    // Solve system of equations
    int i, m, n;
    float** a, * x, * b;

    // Set m to the number of equations 
    m = 8;
    // Set n to the number of unknowns
    n = 6;

    a = new float* [m+1];
    for (i = 0; i < m+1; i++)
        a[i] = new float[n+1];

    x = new float[n+1];

    b = new float[m+1];

    // Fill matrix a and vector b with the desired values
    // The values should be placed at indices 1..m, 1..n
    a[1][1] = P1[0];
    a[1][2] = P1[1];
    a[1][3] = 1;
    a[1][4] = 0;
    a[1][5] = 0;
    a[1][6] = 0;

    a[2][1] = 0;
    a[2][2] = 0;
    a[2][3] = 0;
    a[2][4] = P1[0];
    a[2][5] = P1[1];
    a[2][6] = 1;

    a[3][1] = P2[0];
    a[3][2] = P2[1];
    a[3][3] = 1;
    a[3][4] = 0;
    a[3][5] = 0;
    a[3][6] = 0;

    a[4][1] = 0;
    a[4][2] = 0;
    a[4][3] = 0;
    a[4][4] = P2[0];
    a[4][5] = P2[1];
    a[4][6] = 1;

    a[5][1] = P3[0];
    a[5][2] = P3[1];
    a[5][3] = 1;
    a[5][4] = 0;
    a[5][5] = 0;
    a[5][6] = 0;

    a[6][1] = 0;
    a[6][2] = 0;
    a[6][3] = 0;
    a[6][4] = P3[0];
    a[6][5] = P3[1];
    a[6][6] = 1;

    a[7][1] = P4[0];
    a[7][2] = P4[1];
    a[7][3] = 1;
    a[7][4] = 0;
    a[7][5] = 0;
    a[7][6] = 0;

    a[8][1] = 0;
    a[8][2] = 0;
    a[8][3] = 0;
    a[8][4] = P4[0];
    a[8][5] = P4[1];
    a[8][6] = 1;

    for (int i = 1; i < m+1; i++) {
        for (int j = 1; j < n+1; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    b[1] = P1_F[0];
    b[2] = P1_F[1];
    b[3] = P2_F[0];
    b[4] = P2_F[1];
    b[5] = P3_F[0];
    b[6] = P3_F[1];
    b[7] = P4_F[0];
    b[8] = P4_F[1];

    for (int i = 1; i < m+1; i++) {
        cout << b[i] << " ";
    }
    cout << endl << endl;

    
    for (int i = 1; i < n+1; i++) {
        x[i] = 0;
    }    
    solve_system(m, n, a, x, b);


    // The solution is now in vector x, at indices 1..n 
    for (int i = 1; i < n+1; i++) {
        cout << x[i] << " ";
    }
    cout << endl << endl;

    
    // Once parameters for affine transformation are found, 
    // normalize each image using computer affine transformation
    int k_11 = x[1];
    int k_12 = x[2];
    int k_13 = x[3];
    int k_21 = x[4];
    int k_22 = x[5];
    int k_23 = x[6];

    // Downsample image to 48 x 40
    resize(img, dst, Size(48, 40));

    for (int i = 0; i < dst.rows; i++) {
        for (int j = 0; j < dst.cols; j++) {
            // Get affine X and Y
            int x_o = (i * k_11) + (j * k_12) + k_13;
            int y_o = (i * k_21) + (j * k_22) + k_23;
            
            //cout << i << " " << j << endl;
            //cout << x_o << " " << y_o << endl;

            // Get original image pixel value at x_o, y_o 
            int orig_value = (int)img.at<uchar>(x_o, y_o);
            //cout << orig_value << endl << endl;

            // Place original pixel value 
            dst.at<uchar>(i, j) = orig_value;
        }
    }

    // Verify how well the computer affine transformation aligns 
    // by calculating average error in pixels
    float error = 0.0;
    int correct = 0;
    int total = 0;

    for (int i = 0; i < dst.rows; i++) {
        for (int j = 0; j < dst.rows; j++) {
            
            if ((int)dst.at<uchar>(i,j) == (int)img.at<uchar>(i,j))
                correct += 1;

            total += 1;
        
        }
    }
    error = correct / total;
    cout << "Percent Error: " << error << endl;
    

    imshow("Normalized File", dst);
    imwrite("C:\\Users\\Lee\\source\\repos\\PA2_pb1\\PA2_pb1\\S1\\1_norm.pgm", dst);

    waitKey(0);
    return 0;
}