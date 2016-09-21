/*Created by Alessandro Bigiotti*/


// Inlcude C library
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

// Include DevIL library
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

// Include OpenCL Library
#include "CL/cl.h"
#include "CL/cl_gl_ext.h"
#include "CL/cl_ext.h"
#include "CL/opencl.h"

// Include the file with the data structures
#include "./dataStruct.c"

// Include a file with the OpenCL Inizialization
#include "./setOpenCLAmbient.c"

// Include a file with the Kernel Inizialization
#include "./initKernel.c"

// Include a file with the
#include "./setKernel.c"

#define MAX_SOURCE_SIZE (0x100000)

// Define the prototype of the auxiliary function
int initilizeOpenCL();
int CreateKernel();
int SetKernel(int W, int H);

int main()
{
  // Ask the path of the image
  printf("Insert the path to image\n");
  // Read the path of the image and save it
  scanf("%s", image);

  // Retrieve the path of the current directory
  getcwd(currentDirectory, sizeof(currentDirectory));

  // Create Path to output image
  strcat(strcpy(result, currentDirectory), "/Image/output.bmp");

	//Inizializza DevIL
	ilInit();

	// Load the image specified by image
	ilLoadImage(image);

	// Create a Pointer to the image
	ILubyte* raw_image = ilGetData();

	// Retrieve the WIDTH and the HEIGHT of the image
  ILuint W = ilGetInteger(IL_IMAGE_WIDTH);
	ILuint H = ilGetInteger(IL_IMAGE_HEIGHT);
  printf ("Dimensioni Immagine: %d, %d \n", W, H);

	// Buffer to copy the pixels
	data_raw = (ILubyte*)malloc(sizeof(ILubyte)*H*W * 3);

	// Calculate the image pixels Dimensions
	unsigned int S = W * H * 3;

	// Copy the pixels of the image into data_raw
	ilCopyPixels(0, 0, 0, W, H, 1, IL_RGB, IL_UNSIGNED_BYTE, data_raw);

	// Some Vector for ILubyte* output image;
  ILubyte* out_result = (ILubyte*)malloc(sizeof(ILubyte)*S);
	ILubyte* out_result2 = (ILubyte*)malloc(sizeof(ILubyte)*S);
	ILubyte* out_result3 = (ILubyte*)malloc(sizeof(ILubyte)*S);
	ILubyte* out_result4 = (ILubyte*)malloc(sizeof(ILubyte)*S);

	// Float vector to calculate the changes of the image
	float* data = (float*)malloc(sizeof(float)*S);
	float* output = (float*)malloc(sizeof(float)*S);
	float* output2 = (float*)malloc(sizeof(float)*S);
	float* output3 = (float*)malloc(sizeof(float)*S);
	float* output4 = (float*)malloc(sizeof(float)*S);

  // Normalize the pixels to 255 (float values)
	//per occupare meno memoria
	for (int i=0; i < S; i+=3)	{
		data[i + 0] = (float)(data_raw[i + 0] / 255.0);
		data[i + 1] = (float)(data_raw[i + 1] / 255.0);
		data[i + 2] = (float)(data_raw[i + 2] / 255.0);
	}


  InitializeOpenCL();

  CreateKernel();

  // Copy all necessary data into GPU
	dev_image = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(float)*S, data, &err);
	out_put = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float)*S, NULL, &err);

	out_put2 = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float)*S, NULL, &err);
	out_put3 = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float)*S, NULL, &err);
	out_put4 = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float)*S, NULL, &err);

	smooth = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * 49, smooth_mask, &err);
	smooth2 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * 25, smooth_mask2, &err);
	mask_gaus = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * 9, gauss_mask, &err);
	mask_gaus2 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * 25, gauss_mask2, &err);
	prewN = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * 9, prewitt_mask_Nord, &err);
	prewE = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * 9, prewitt_mask_Est, &err);
	sharp = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * 9, sharpening, &err);
	if (err < 0){
		printf("Impossibile copire i dati su GPU!\n");
		return EXIT_FAILURE;
	}

	///////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  //Dimensione WorkGroup per operazioni puntuali
  size_t globalWorkSize3D[3] = {W,H,3};
  //defauls localWorkSize3D { 1, 1, 1 }

  //Dimensione WorkGroup per operazioni locali
  size_t globalWorkSize2D[2] = { W * 3, H };
  //default localWorkSize2D { 1, 1 }

  // Set the kernel parameters
  SetKernel(W,H);

  // Select the Kernel to Run
  printf(" Select the filter to applicate:\n");
  printf("    1: Negative filter \n");
  printf("    2: Binarization filter \n");
  printf("    3: Gauss (5x5) \n");
  printf("    4: Smooth (5x5) \n");
  printf("    5: Prewitt North (3x3) \n");
  printf("    6: Prewitt East (3x3) \n");
  printf("    7: Sharp (3x3) \n");
  printf("    8: Edge Detection \n");
  scanf("%d", &filter_selected);

  if(filter_selected == 1){
    printf("Start image changes...\n");
    err = clEnqueueNDRangeKernel(commands, kernel_negativo, 3, NULL, globalWorkSize3D, NULL,
      0, NULL,NULL);
    err |= clEnqueueReadBuffer(commands, out_put, CL_TRUE, 0, sizeof(float)*S, output, 0, NULL, NULL);
    if (err != CL_SUCCESS)  {
      printf("Errore, Impossibile leggere array di output! %d\n", err);
      exit(EXIT_FAILURE);
    }
  }
  else if(filter_selected == 2){
    printf("Start image changes...\n");
    err = clEnqueueNDRangeKernel(commands, binarizza, 3, NULL, globalWorkSize3D, NULL,
      0, NULL,NULL);
    err |= clEnqueueReadBuffer(commands, out_put, CL_TRUE, 0, sizeof(float)*S, output, 0, NULL, NULL);
    if (err != CL_SUCCESS)  {
      printf("Errore, Impossibile leggere array di output! %d\n", err);
      exit(EXIT_FAILURE);
    }
  }
  else if(filter_selected == 3){
    printf("Start image changes...\n");
    err = clEnqueueNDRangeKernel(commands, kernel_mask_factor, 2, NULL, globalWorkSize2D, NULL,
      0, NULL,NULL);
    err |= clEnqueueReadBuffer(commands, out_put, CL_TRUE, 0, sizeof(float)*S, output, 0, NULL, NULL);
    if (err != CL_SUCCESS)  {
      printf("Errore, Impossibile leggere array di output! %d\n", err);
      exit(EXIT_FAILURE);
    }
  }
  else if(filter_selected == 4){
    printf("Start image changes...\n");
    err = clEnqueueNDRangeKernel(commands, kernel_mask_factor2, 2, NULL, globalWorkSize2D, NULL,
      0, NULL,NULL);
    err |= clEnqueueReadBuffer(commands, out_put, CL_TRUE, 0, sizeof(float)*S, output, 0, NULL, NULL);
    if (err != CL_SUCCESS)  {
      printf("Errore, Impossibile leggere array di output! %d\n", err);
      exit(EXIT_FAILURE);
    }
  }
  else if(filter_selected == 5){
    printf("Start image changes...\n");
    err = clEnqueueNDRangeKernel(commands, kernel_mask, 2, NULL, globalWorkSize2D, NULL,
      0, NULL,NULL);
    err |= clEnqueueReadBuffer(commands, out_put, CL_TRUE, 0, sizeof(float)*S, output, 0, NULL, NULL);
    if (err != CL_SUCCESS)  {
      printf("Errore, Impossibile leggere array di output! %d\n", err);
      exit(EXIT_FAILURE);
    }
  }
  else if(filter_selected == 6){
    printf("Start image changes...\n");
    err = clEnqueueNDRangeKernel(commands, kernel_mask2, 2, NULL, globalWorkSize2D, NULL,
      0, NULL,NULL);
    err |= clEnqueueReadBuffer(commands, out_put, CL_TRUE, 0, sizeof(float)*S, output, 0, NULL, NULL);
    if (err != CL_SUCCESS)  {
      printf("Errore, Impossibile leggere array di output! %d\n", err);
      exit(EXIT_FAILURE);
    }
  }
  else if(filter_selected == 7){
    printf("Start image changes...\n");
    err = clEnqueueNDRangeKernel(commands, kernel_mask3, 2, NULL, globalWorkSize2D, NULL,
      0, NULL,NULL);
    err |= clEnqueueReadBuffer(commands, out_put, CL_TRUE, 0, sizeof(float)*S, output, 0, NULL, NULL);
    if (err != CL_SUCCESS)  {
      printf("Errore, Impossibile leggere array di output! %d\n", err);
      exit(EXIT_FAILURE);
    }
  }
  else if(filter_selected == 8){
    printf("Start image changes...\n");
    err = clEnqueueNDRangeKernel(commands, edge_detection, 2, NULL, globalWorkSize2D, NULL,
      0, NULL,NULL);
    err |= clEnqueueReadBuffer(commands, out_put, CL_TRUE, 0, sizeof(float)*S, output, 0, NULL, NULL);
    if (err != CL_SUCCESS)  {
      printf("Errore, Impossibile leggere array di output! %d\n", err);
      exit(EXIT_FAILURE);
    }
  }
  clFinish(commands);

  //Conversione del risultato (float) in byte
	for (int i = 0; i < S; i += 3){
		out_result[i + 0] = (ILubyte)(output[i + 0] * 255.0f);
		out_result[i + 1] = (ILubyte)(output[i + 1] * 255.0f);
		out_result[i + 2] = (ILubyte)(output[i + 2] * 255.0f);
  }
  //Copio il risultato in un'immagine specificata da result#
  ilTexImage(W, H, 1, 3, IL_RGB, IL_UNSIGNED_BYTE, out_result);
  ilEnable(IL_FILE_OVERWRITE);
  ilSave(IL_BMP, result);

  printf("Changes Completed! \n");
  //libero le risorse
	clReleaseMemObject(dev_image);
	clReleaseMemObject(out_put);
	clReleaseMemObject(out_put2);
	clReleaseMemObject(out_put3);
	clReleaseMemObject(out_put4);
	clReleaseMemObject(smooth);
	clReleaseMemObject(smooth2);
	clReleaseMemObject(mask_gaus);
	clReleaseMemObject(mask_gaus2);
	clReleaseMemObject(prewE);
	clReleaseMemObject(prewN);
	clReleaseMemObject(sharp);
	clReleaseKernel(kernel_negativo);
	clReleaseKernel(binarizza);
	clReleaseKernel(kernel_mask_factor2);
	clReleaseKernel(kernel_mask_factor);
	clReleaseKernel(kernel_mask);
	clReleaseKernel(kernel_mask2);
	clReleaseKernel(kernel_mask3);
	clReleaseProgram(program);
	clReleaseCommandQueue(commands);
	clReleaseContext(context);

	return 0;

}
