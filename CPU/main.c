#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgmUtility.h"
#include <time.h>
  
void usage();

int main(int argc, char *argv[]){

    FILE * fp = NULL;
    FILE * out = NULL; 

    char ** header = (char**) malloc( sizeof(char *) * rowsInHeader);
    int i;
    int * pixels = NULL;
    int * cpuArray = NULL;
    int * gpuArray = NULL;
    
    
    for(i = 0; i < 4; i++){
        header[i] = (char *) malloc (sizeof(char) * maxSizeHeadRow);
    }
    int numRows, numCols;

    int p1y = 0;
    int p1x = 0;
    int p2y = 0;
    int p2x = 0;

    int m, n, l, x, ch;
    int edgeWidth, circleCenterRow, circleCenterCol, radius;
    char originalImageName[100], newImageFileName[100];
    if(argc != 5 && argc != 7 && argc != 8)
    {
                usage();
        return 1;
        }
    else
    {            
        l = strlen( argv[1] );
        if(l != 2){
            usage();
            return 1;
        }
        ch = (int)argv[1][1];
        if(ch < 97)
            ch = ch + 32;
            
        //Variables for timing    
        clock_t before;
        clock_t difference;
        //int msec = 0;
        double msec = 0;
        switch( ch )
        {
            case 'c':
            {  
                if(argc != 7){
                    usage();
                    break;
                }
                circleCenterRow = atoi(argv[2]);
                circleCenterCol = atoi(argv[3]);
                radius = atoi(argv[4]);
                strcpy(originalImageName, argv[5]);
                strcpy(newImageFileName, argv[6]);

                fp = fopen(originalImageName, "r");
                if(fp == NULL){
                    usage();
                    return 1;
                }
                out = fopen(newImageFileName, "w");
                if(out == NULL){
                    usage();
                    fclose(fp);
                    return 1;
                }


                pixels = pgmRead(header, &numRows, &numCols, fp);
                
                //Timing the circleDraw method
		before = clock();
                pgmDrawCircle(pixels, numRows, numCols, circleCenterRow, circleCenterCol, radius, header );
                difference = clock() - before;
                msec = (double)difference * 1,000,000 / CLOCKS_PER_SEC;
                
                pgmWrite((const char **)header, (const int *)pixels, numRows, numCols, out );    
                break;
            }
            case 'e':  
                if(argc != 5){
                    usage();
                    break;
                }
                edgeWidth = atoi(argv[2]);
                strcpy(originalImageName, argv[3]);
                strcpy(newImageFileName, argv[4]);
                fp = fopen(originalImageName, "r");
                if(fp == NULL){
                    usage();
                    return 1;
                }
                out = fopen(newImageFileName, "w");
                if(out == NULL){
                    usage();
                    fclose(fp);
                    return 1;
                }

                pixels = pgmRead(header, &numRows, &numCols, fp);
                
                //Timing the drawEdge method
                before = clock();
                pgmDrawEdge(pixels, numRows, numCols, edgeWidth, header);
                difference = clock() - before;
                msec = (double)difference * 1,000,000 / CLOCKS_PER_SEC;
                
                pgmWrite((const char **)header, (const int *)pixels, numRows, numCols, out );
                break;

            case 'l':  
                if(argc != 8){
                    usage();
                    break;
                }
                p1y = atoi(argv[2]);
                p1x = atoi(argv[3]);

                p2y = atoi(argv[4]);
                p2x = atoi(argv[5]);


                strcpy(originalImageName, argv[6]);
                strcpy(newImageFileName, argv[7]);

                fp = fopen(originalImageName, "r");
                if(fp == NULL){
                    usage();
                    return 1;
                }
                out = fopen(newImageFileName, "w");
                if(out == NULL){
                    usage();
                    fclose(fp);
                    return 1;
                }

                pixels = pgmRead(header, &numRows, &numCols, fp);
                
                //Timing the drawLine method
                before = clock();
                pgmDrawLine(pixels, numRows, numCols, header, p1y, p1x, p2y, p2x);
                difference = clock() - before;                
                msec = (double)difference * 1,000,000 / CLOCKS_PER_SEC;
                
                pgmWrite((const char **)header, (const int *)pixels, numRows, numCols, out );
                break;
        }
        
        //printf("%d%s\n", msec, " milliseconds");  
        printf("%f%s\n", msec, " milliseconds");   
    }

        
    free(pixels);
    i = 0;
    for(;i < rowsInHeader; i++)
        free(header[i]);
    free(header);
    if(out != NULL)
        fclose(out);
    if(fp != NULL)
        fclose(fp);
        
    
    
    return 0;
}

void usage()
{
        printf("Usage:\n    -e edgeWidth  oldImageFile  newImageFile\n    -c circleCenterRow circleCenterCol radius  oldImageFile  newImageFile\n    -l  p1row  p1col  p2row  p2col  oldImageFile  newImageFile\n");

}
