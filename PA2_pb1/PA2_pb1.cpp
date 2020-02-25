// Simple algorithm that normalizes faces with respect to location, size, orientation, and lighting
// Uses 4 facial features: 
// - left eye center 
// - right eye center
// - nose tip
// - mouth center

#include <iostream>

using namespace std;

int main()
{
    // Manually extract acutal coordinates of 4 facial features from each image
    int P1, P2, P3, P4;

    // Choose predetermined locations of features in fixed window size
    int P1_F, P2_F, P3_F, P4_F;

    // Computer parameters of affine transformation (A and b)
    int A[2][2];
    int b[2][1];

    // Once parameters for affine transformation are found, 
    // normalize each image using computer affine transformation

    // Verify how well the computer affine transformation aligns 
    // by calculating average error in pixels
    // For image
    
    // For set
    
}