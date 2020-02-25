// Simple algorithm that normalizes faces with respect to location, size, orientation, and lighting
// Uses 4 facial features: 
// - left eye center 
// - right eye center
// - nose tip
// - mouth center

#include <iostream>

#include "ReadImage.cpp"
#include "WriteImage.cpp"

using namespace std;

void find_affine_parameters(int P1, int P2, int P3, int P4, int P1_F, int P2_F, int P3_F, int P4_F, int A[2][2], int b[2][1]);
int calculate_pixel_error(int** img1, int** img2);

void find_affine_parameters(int P1, int P2, int P3, int P4, int P1_F, int P2_F, int P3_F, int P4_F, int A[2][2], int b[2][1])
{

}

int calculate_pixel_error(int** img1, int** img2)
{
    int error = 0;
    return error;
}

int main()
{
    // Read in image
    int** input, ** output;
    int x_size, y_size, Q;
    char name[20] = "./S1/1.pgm";
    char outfile[25] = "./S1/1_transform.pgm";

    ReadImage(name, &input, x_size, y_size, Q);

    // Manually extract acutal coordinates of 4 facial features from each image
    int P1, P2, P3, P4;

    // Choose predetermined locations of features in fixed window size
    int P1_F, P2_F, P3_F, P4_F;

    // Computer parameters of affine transformation (A and b)
    int A[2][2];
    int b[2][1];
    //find_affine_parameters(P1, P2, P3, P4, P1_F, P2_F, P3_F, P4_F, A, b);

    // Once parameters for affine transformation are found, 
    // normalize each image using computer affine transformation

    WriteImage(outfile, output, x_size, y_size, Q);

    // Verify how well the computer affine transformation aligns 
    // by calculating average error in pixels
        
}