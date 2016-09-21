
int CreateKernel(){
  /////////////////////////\\\\\\\\\\\\
  KERNEL NEGATIVO CREATE
  kernel_negativo = clCreateKernel(program, "negativo", &err);
  if (!kernel_negativo || err != CL_SUCCESS)	{
    printf("Errore, Impossibile creare il kernel_negativo!\n");
    scanf("%d",e);
    exit(1);
  }
  //////////////////\\\\\\\\\\\\\\\\\\
  KERNEL BINARIZZA CREATE
  binarizza = clCreateKernel(program, "binarizza", &err);
  if (!binarizza || err != CL_SUCCESS) {
    printf("Errore, Impossibile creare il kernel2!\n");
    scanf("%d", e);
    exit(1);
  }
  ///////////////////////\\\\\\\\\\\\\\\\\\\
  KERNEL MASK
  kernel_mask_factor2 = clCreateKernel(program, "mask_factor", &err);
  if (!kernel_mask_factor2 || err != CL_SUCCESS)	{
    printf("Errore, Impossibile creare il kernel_mask_factor!\n");
    scanf("%d", e);
    exit(1);
  }
  ///////////////////////\\\\\\\\\\\\\\\\\\\
  KERNEL Mask_Fator CREATE

  kernel_mask_factor = clCreateKernel(program, "mask_factor", &err);
  if (!kernel_mask_factor || err != CL_SUCCESS)	{
    printf("Errore, Impossibile creare il kernel_mask_factor!\n");
    scanf("%d", e);
    exit(1);
  }
  ///////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  //KERNEL Mask CREATE
  kernel_mask = clCreateKernel(program, "mask", &err);
  if (!kernel_mask || err != CL_SUCCESS)	{
    printf("Errore, Impossibile creare il kernel_mask!\n");
    scanf("%d", e);
    exit(1);
  }
  ///////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  //KERNEL Mask2 CREATE
  kernel_mask2 = clCreateKernel(program, "mask", &err);
  if (!kernel_mask2 || err != CL_SUCCESS)	{
    printf("Errore, Impossibile creare il kernel_mask!\n");
    scanf("%d", e);
    exit(1);
  }
  ///////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  //KERNEL Mask2 CREATE
  kernel_mask3 = clCreateKernel(program, "mask", &err);
  if (!kernel_mask3 || err != CL_SUCCESS)	{
    printf("Errore, Impossibile creare il kernel_mask!\n");
    scanf("%d", e);
    exit(1);
  }

  /////\\\\\\\\
  //KERNEL EDGE DETECTION
  edge_detection = clCreateKernel(program, "edge_detection", &err);
  if (!edge_detection || err != CL_SUCCESS)	{
    printf("Errore, Impossibile creare il edge_detection!\n");
    scanf("%d", e);
    exit(1);
  }
}
