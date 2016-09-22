/* Created by Alessandro Bigiotti */

int SetKernel(int W, int H){

  // Set Kernel Negative
  err = clSetKernelArg(kernel_negativo, 0, sizeof(cl_mem), (void *)&dev_image);
  err |= clSetKernelArg(kernel_negativo, 1, sizeof(cl_mem), (void *)&out_put);
  err |= clSetKernelArg(kernel_negativo, 2, sizeof(int), (void *)&W);
  err |= clSetKernelArg(kernel_negativo, 3, sizeof(int), (void *)&H);
  if (err != CL_SUCCESS)	{
    printf("Error, Impossible set Negative Kernel! %d\n", err);
    exit(1);
  }
  // Set Kernel Binarizations
  err |= clSetKernelArg(binarizza, 0, sizeof(cl_mem), (void *)&dev_image);
  err |= clSetKernelArg(binarizza, 1, sizeof(cl_mem), (void *)&out_put);
  err |= clSetKernelArg(binarizza, 2, sizeof(int), (void *)&W);
  err |= clSetKernelArg(binarizza, 3, sizeof(int), (void *)&H);
  if (err != CL_SUCCESS)	{
    printf("Error, Impossible set Binarization Kernel! %d\n", err);
    exit(1);
  }
  // Set Kernel gauss 5x5 (gauss_mask2 in file dataStruct.c)
  err |= clSetKernelArg(kernel_mask_factor, 0, sizeof(cl_mem), (void *)&dev_image);
  err |= clSetKernelArg(kernel_mask_factor, 1, sizeof(cl_mem), (void *)&out_put);
  err |= clSetKernelArg(kernel_mask_factor, 2, sizeof(int), (void *)&W);
  err |= clSetKernelArg(kernel_mask_factor, 3, sizeof(int), (void *)&H);
  err |= clSetKernelArg(kernel_mask_factor, 4, sizeof(cl_mem), (void *)&mask_gaus2);
  err |= clSetKernelArg(kernel_mask_factor, 5, sizeof(int), (void *)&range1);
  err |= clSetKernelArg(kernel_mask_factor, 6, sizeof(int), (void *)&factor);
  if (err != CL_SUCCESS)	{
    printf("Error, Impossible set Gauss Kernel! %d\n", err);
    exit(1);
  }
  // Set Kernel Smooth 5x5
  err |= clSetKernelArg(kernel_mask_factor2, 0, sizeof(cl_mem), (void *)&dev_image);
  err |= clSetKernelArg(kernel_mask_factor2, 1, sizeof(cl_mem), (void *)&out_put);
  err |= clSetKernelArg(kernel_mask_factor2, 2, sizeof(int), (void *)&W);
  err |= clSetKernelArg(kernel_mask_factor2, 3, sizeof(int), (void *)&H);
  err |= clSetKernelArg(kernel_mask_factor2, 4, sizeof(cl_mem), (void *)&smooth);
  err |= clSetKernelArg(kernel_mask_factor2, 5, sizeof(int), (void *)&range);
  err |= clSetKernelArg(kernel_mask_factor2, 6, sizeof(int), (void *)&factor);
  if (err != CL_SUCCESS)	{
    printf("Error, Impossible set Smooth Kernel! %d\n", err);
    exit(1);
  }
  // Set Kernel PrewittNorth
  err |= clSetKernelArg(kernel_mask, 0, sizeof(cl_mem), (void *)&dev_image);
  err |= clSetKernelArg(kernel_mask, 1, sizeof(cl_mem), (void *)&out_put);
  err |= clSetKernelArg(kernel_mask, 2, sizeof(int), (void *)&W);
  err |= clSetKernelArg(kernel_mask, 3, sizeof(int), (void *)&H);
  err |= clSetKernelArg(kernel_mask, 4, sizeof(cl_mem), (void *)&prewN);
  err |= clSetKernelArg(kernel_mask, 5, sizeof(int), (void *)&range2);
  if (err != CL_SUCCESS)	{
    printf("Error, Impossible set PrewittNorth Kernel! %d\n", err);
    exit(1);
  }
  // Set Kernel PrewittEst
  err |= clSetKernelArg(kernel_mask2, 0, sizeof(cl_mem), (void *)&dev_image);
  err |= clSetKernelArg(kernel_mask2, 1, sizeof(cl_mem), (void *)&out_put);
  err |= clSetKernelArg(kernel_mask2, 2, sizeof(int), (void *)&W);
  err |= clSetKernelArg(kernel_mask2, 3, sizeof(int), (void *)&H);
  err |= clSetKernelArg(kernel_mask2, 4, sizeof(cl_mem), (void *)&prewE);
  err |= clSetKernelArg(kernel_mask2, 5, sizeof(int), (void *)&range2);
  if (err != CL_SUCCESS)	{
    printf("Error, Impossible set PrewittNorth Kernel! %d\n", err);
    exit(1);
  }
  // Set Kernel PrewittSouth
  err |= clSetKernelArg(kernel_mask3, 0, sizeof(cl_mem), (void *)&dev_image);
  err |= clSetKernelArg(kernel_mask3, 1, sizeof(cl_mem), (void *)&out_put);
  err |= clSetKernelArg(kernel_mask3, 2, sizeof(int), (void *)&W);
  err |= clSetKernelArg(kernel_mask3, 3, sizeof(int), (void *)&H);
  err |= clSetKernelArg(kernel_mask3, 4, sizeof(cl_mem), (void *)&sharp);
  err |= clSetKernelArg(kernel_mask3, 5, sizeof(int), (void *)&range2);
  if (err != CL_SUCCESS)	{
    printf("Error, Impossible set Sharp Kernel! %d\n", err);
    exit(1);
  }

  // Set Kernel Edge Detection
  err |= clSetKernelArg(edge_detection, 0, sizeof(cl_mem), (void *)&dev_image);
  err |= clSetKernelArg(edge_detection, 1, sizeof(cl_mem), (void *)&out_put);
  err |= clSetKernelArg(edge_detection, 2, sizeof(int), (void *)&W);
  err |= clSetKernelArg(edge_detection, 3, sizeof(int), (void *)&H);
  err |= clSetKernelArg(edge_detection, 4, sizeof(cl_mem), (void *)&prewN);
  err |= clSetKernelArg(edge_detection, 5, sizeof(cl_mem), (void *)&prewE);
  err |= clSetKernelArg(edge_detection, 6, sizeof(int), (void *)&range2);
  if (err != CL_SUCCESS)	{
    printf("Error, Impossible set Smooth Kernel! %d\n", err);
    exit(EXIT_FAILURE);
  }
}
