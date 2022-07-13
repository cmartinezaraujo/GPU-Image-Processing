//  pgmUtility.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgmUtility.h"
double distance( int p1x, int p1y, int p2x, int p2y); 

//---------------------------------------------------------------------------
int * pgmRead( char **header, int *numRows, int *numCols, FILE *in )
{
    int i, j;
    
    // read in header of the image first
    for( i = 0; i < rowsInHeader; i ++)
    {
        if ( header[i] == NULL )
        {
            return NULL;
        }
        if( fgets( header[i], maxSizeHeadRow, in ) == NULL )
        {
            return NULL;
        }
    }
    // extract rows of pixels and columns of pixels
    sscanf( header[rowsInHeader - 2], "%d %d", numCols, numRows );  // in pgm the first number is # of cols
    
    int *pixels = (int*)malloc((*numCols) * (*numRows) * sizeof(int));

    // read in all pixels into the pixels array.
    for( i = 0; i < *numRows; i ++ )
        for( j = 0; j < *numCols; j ++ )
            if(fscanf(in, "%d ", &pixels[(i*(*numCols))+j]) < 0 )
                return NULL;
    
    return pixels;
}

//---------------------------------------------------------------------------
int pgmDrawCircle( int *pixels, int numRows, int numCols, int centerRow,
                  int centerCol, int radius, char **header )
{
    int i, j; 

    int r = radius*radius;

    for( i = 0; i < numRows; i ++ )
        for( j = 0; j < numCols; j ++ )
            if( ((j-centerCol)*(j-centerCol))+((i-centerRow)*(i-centerRow)) < r)
                pixels[(i*(numCols))+j] = 0;

    
    return 1;  
}

//---------------------------------------------------------------------------
int pgmDrawEdge( int *pixels, int numRows, int numCols, int edgeWidth, char **header )
{
    int i, j;

    for( i = 0; i < numRows; i ++ )
        for( j = 0; j < numCols; j ++ )
            if((i < edgeWidth | j <edgeWidth) | (((edgeWidth-i)+numRows < edgeWidth*2) | ((edgeWidth-j)+numCols < edgeWidth*2)) )
                pixels[(i*(numCols))+j] = 0;

    return 1;
}

//---------------------------------------------------------------------------

int pgmDrawLine( int *pixels, int numRows, int numCols, char **header,
                int p1row, int p1col, int p2row, int p2col )
{  
    int m = 2 * (p2row - p1row);
    int slopeError = m - (p2col - p1col);
    
    if(p1row <= p2row)
    {
	 for(int x = p1col, y = p1row; x < p2col; x++)
   	 {
    		pixels[((y * numCols) + x)] = 0;
    
		slopeError += m;
    	
    	
    		if(slopeError >= 0)
    		{
    			y++;
    			slopeError -= 2 * (p2col - p1col);
    		}	
    	}
    }
    else if(p1row >= p2row)
    {
    	for(int x = p1col, y = p1row; x < p2col; x++)
    	{
    		pixels[((y * numCols) + x)] = 0;
    
		slopeError -= m;
    	
    	
    		if(slopeError >= 0)
    		{
    			y--;
    			slopeError -= 2 * (p2col - p1col);
    		}	
    	}
    }
    return 1;
     
}

//----------------------------------------------------------------------------
int pgmWrite( const char **header, const int *pixels, int numRows, int numCols, FILE *out )
{
    int i, j;
    
    // write the header
    for ( i = 0; i < rowsInHeader; i ++ )
    {
        fprintf(out, "%s", *( header + i ) );
    }
    
    // write the pixels
    for( i = 0; i < numRows; i ++ )
    {
        for ( j = 0; j < numCols; j ++ )
        {
            if ( j < numCols - 1 )
                fprintf(out, "%d ", pixels[(i*numCols)+j]);
            else
                fprintf(out, "%d\n", pixels[(i*numCols)+j]);
        }
    }
    return 0;
}

//-------------------------------------------------------------------------------
double distance( int p1x, int p1y, int p2x, int p2y)
{
    double res = sqrt( pow( p1x - p2x, 2 ) + pow( p1y - p2y, 2 ) );
    return res;
}


