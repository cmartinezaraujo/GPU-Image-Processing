

/**
 *  Function Name:
 *      distance()
 *      distance() returns the Euclidean distance between two pixels. This function is executed on CUDA device
 *
 *  @param[in]  p1  coordinates of pixel one, p1[0] is for row number, p1[1] is for column number
 *  @param[in]  p2  coordinates of pixel two, p2[0] is for row number, p2[1] is for column number
 *  @return         return distance between p1 and p2
 */
#include <math.h>
__device__ float distance( int p1x, int p1y, int p2x, int p2y)
{
    return sqrt( (float)(((p1x - p2x) * (p1x - p2x)) + ((p1y - p2y)*(p1y - p2y))) );
}

__global__ void pgmDrawCircleK(int *d_pixels, int numRows, int numCols, int centerRow, int centerCol, int redius){
    
    int Row = blockIdx.y * blockDim.y + threadIdx.y;
    int Col = blockIdx.x * blockDim.x + threadIdx.x;

    int r = redius*redius;

    if((Row < numRows) && (Col < numCols)){
        if( ((Col-centerCol)*(Col-centerCol))+((Row-centerRow)*(Row-centerRow)) < r){
            d_pixels[Row*numCols+Col] = 0;
        }
    }
}

__global__ void pgmDrawEdgeK( int *pixels, int numRows, int numCols, int edgeWidth)
{
    int Row = blockIdx.y * blockDim.y + threadIdx.y;
    int Col = blockIdx.x * blockDim.x + threadIdx.x;
    

    if((Row < numRows) && (Col < numCols)){
        if((Row < edgeWidth | Col <edgeWidth) | (edgeWidth-Row)+numRows < edgeWidth*2 | (edgeWidth-Col)+numCols < edgeWidth*2 )
                pixels[(Row*(numCols))+Col] = 0;
    }
}

__global__ void pgmDrawLineK( int *pixels, int numRows, int numCols, int p1row, int p1col, int p2row, int p2col ){
    int Row = blockIdx.y * blockDim.y + threadIdx.y;
    int Col = blockIdx.x * blockDim.x + threadIdx.x;

    double slope = (double)(p2row-p1row)/(p2col-p1col);

    double c = p1row - slope * p1col;
    double yInt = slope * 0 +c;

     if((Row >= p1row) && (Row < p2row) && (Col < numCols)){
         if( fabs((slope * Col + yInt)-(double)Row) < .5){
                pixels[(Row*(numCols))+Col] = 0;
            } 
     }
}
