/* Created by Alessandro Bigiotti */
////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
ONPECL CODE
////////////////////////////////////////////
#define MAX_SOURCE_SIZE (0x100000)

int InitializeOpenCL() {
  printf("Inizializza Device...\n");

  strcat(strcpy(path_to_kernel, currentDirectory), "/filter_kernel.cl");

  //Sappiamo che la Piattaforma con GPU NVIDIA ed ha id 1
  err = clGetPlatformIDs(10, Platform_id, &Num_Platform);
  if (err != CL_SUCCESS){
    printf("Errore, Impossibile ottenere una Piattaforma!\n");
    return EXIT_FAILURE;
  }


  // Per la piattaforma NVIDIA (Platform_id[1])
  //Sappiamo che c'� solo un Device disponibile ed ha id 0
  err = clGetDeviceIDs(Platform_id[1], CL_DEVICE_TYPE_GPU, 10, Devices_id, &Num_Device);
  if (err != CL_SUCCESS){
    printf("Errore, Impossibile ottenere un Device!\n");
    return EXIT_FAILURE;
  }


  // Device_id indica l'id del Device su cui effettuare i calcoli
  context = clCreateContext(0, 1, Devices_id, NULL, NULL, &err);
  if (!context)
  {
    printf("Errore, Impossibile creare un contesto!\n");
    return EXIT_FAILURE;
  }


  // La coda di comando ha un contesto, un device,
  commands = clCreateCommandQueue(context, Devices_id[0], 0, &err);
  if (!commands)
  {
    printf("Errore, Impossibile creare coda di comando!\n");
    return EXIT_FAILURE;
  }

  // Carica il file Kernel
	fp = fopen(path_to_kernel, "r");
	if (!fp) {
		printf("Impossibile aprire il file kernel \n");
		return EXIT_FAILURE;
	}
	source_str = (char *)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);

	program = clCreateProgramWithSource(context, 1, (const char **)& source_str,
		(const size_t *)&source_size, &err);
	if (!program)
	{
		printf("Errore, Impossibile creare il programma!\n");
		scanf("%d", e);
		return EXIT_FAILURE;
	}

	// "Compila" il Programma
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)	{
		size_t len;
		char buffer[2048];
		printf("Errore, Impossibile creare l'eseguibile!\n");
		clGetProgramBuildInfo(program, Devices_id[0], CL_PROGRAM_BUILD_LOG, sizeof(buffer),
			buffer, &len);

		printf("%s\n", buffer);
		scanf("%d",e);
		exit(1);
	}

}
