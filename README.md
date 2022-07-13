# GPU Image Processing Using CUDA

![Balloons](./CPU/balloons.png)

This is a comand line program used to manipulate PGM (Portable Gray Map) images. The format of PGM images is fairly simple and is layed out in rows/columns defined in a header.This makes the data perfect for processing on CUDA enabled Nvidia GPU.

A Sequential version of the program is used to evaluate any efficiancy gained from processing the image in parallel. Kernel functions are implemented for each sequential function so the same process can be achieved on the GPU.

**Usage**:

 -e edgeWidth  oldImageFile  newImageFile
 -c circleCenterRow circleCenterCol radius  oldImageFile  newImageFile
 -l  p1row  p1col  p2row  p2col  oldImageFile  newImageFile

`./myPaint –e edgeWidth  originalImage  newImageFile`

To paint an edge of width of **edgeWidth** in the image of **originalImage**.

`./programName –c circleCenterRow circleCenterCol  radius  originalImage  newImageFile`

To paint an big round dot on the image with center at (**circleCenterRow**, **circleCenterCol**) and radius of **radius**.

`./programName -l  p1row  p1col  p2row  p2col  oldImageFile  newImageFile`
 
To paint a line at a start point with row number = **p1row** and column number = **p1col**, the line segment ends at a point with row number = **p2row** and column number **p2col**.

## Examples

Below are some test runs of the program. While in most cases we can see a speed increase when processing the image on the GPU there is also some overhead when transfering memory from the CPU to the GPU. This outcome is to be expected as the image being processed is small and the overhead is not as significant when processing larger files.

![Ballons image with circle](./images/processed/balloons_circle.png)

Drawing a circle on an image.

`$ ./myPaint -c 228 285 75 balloons.pgm baloons_circle.pgm`

`CPU process time: 546.000000 microseconds`

`$ ./myPaint -c 228 285 75 ./balloons.pgm balloons_circle.pgm`

`Kernel process time: 10.000000 microseconds`

`Process run time: 46572.000000 microseconds`

![Ballons image with line](./images/processed/balloons_line.png)

Drawing a line.

`$ ./myPaint -l  1 50 479 639 ./balloons.pgm balloons_line.pgm`

`CPU process time: 3.000000 microseconds`

`$ ./myPaint -l  1 50 479 639 ./balloons.pgm balloons_line.pgm`

`Kernel process time: 9.000000 microseconds`

`Process run time: 48842.000000 microseconds`

![Ballons image with edge](./images/processed/balloons_edge.png)

Drawing an edge

`$ ./myPaint -e 50 ./balloons.pgm balloons_edge.pgm`

`CPU process time: 865.000000 microseconds`

`$ ./myPaint -e 50 ./balloons.pgm balloons_edge.pgm`

`Kernel process time: 9.000000 microseconds`

`Process run time: 46719.000000 microseconds`
