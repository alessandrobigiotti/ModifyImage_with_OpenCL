/* Created by Alessandro Bigiotti */

// Kernel to calculate the Negative of the image
__kernel void negativo(__global float* image_matrix, __global float* output, int W, int H){

	int Width_dim = get_global_size(0);
	int row = get_global_id(0);
	int col = get_global_id(1);
	int rgb = get_global_id(2);

	output[row * H + col + rgb*H*W] = 1.0f - image_matrix[row*H + col + rgb*H*W];
}

// Kernel to calculate the Binarization of the image
__kernel void binarizza(__global float* image_matrix, __global float* output, int W, int H){

	int row = get_global_id(0);
	int col = get_global_id(1);
	int rgb = get_global_id(2);

	if (image_matrix[row*H + col + rgb*H*W] < 0.5f)
		output[row * H + col + rgb*H*W] = 0.0f;
	else
	  output[row * H + col + rgb*H*W] = 1.0f;

}

// Kernel to applicate some median fileter (gauss, smooth, ....)
__kernel void mask_factor(__global float* image_matrix, __global float* output, int W, int H, __global float* mask, 
												int range, int factor){

	int row = get_global_id(1);
	int col = get_global_id(0);

	int pixels = 0;
	float value_pixels = 0.0f;

	for (int i = row - (range); i < row + (range + 1); i++)	{
		for (int j = col - (range * 3); j < col + (range + 1)*3 ; j+=3){
			if (!(i < 0) && !(i > H) && !(j < 0) && !(j > W*3)){
				pixels++;
				value_pixels += image_matrix[j + i * W * 3] * mask[(row - i + range) * 3 + (col -j)/3 + range];
			}
		}
	}
	value_pixels = value_pixels/(pixels);
	if( value_pixels > 1.0f)
		value_pixels = 1.0f;

	output[row*W*3 + col] = value_pixels;
}
// Kernel to applicate some Non Median filters (sharp, prewitt, sobel, ...)
__kernel void mask(__global float* image_matrix, __global float* output, int W, int H,
									__global float* mask, int range){

	int row = get_global_id(1);
	int col = get_global_id(0);

	float value_pixels = 0.0f;

	for (int i = row - (range); i < row + (range + 1); i++)	{
		for (int j = col - (range * 3); j < col + (range + 1)*3 ; j+=3){
			if (!(i < 0) && !(i > H) && !(j < 0) && !(j > W*3)){
				value_pixels += image_matrix[j + i * W * 3] * 
							mask[(row - i + range) * 3 + (col -j)/3 + range];
			}
		}
	}
	if (value_pixels > 1.0f)
		output[row*W*3 + col] = 1.0f;
	else if (value_pixels < 0.0f)
		output[row*W*3 + col] = 0.0f;
	else
		output[row*W*3 + col] = value_pixels;
}
// Kernel to calculate the Edge_Detection with Prewitt Mask
__kernel void edge_detection(__global float* image_matrix, __global float* output, int W, int H,
								__global float* prewittX, __global float* prewittY, int range){

	int row = get_global_id(1);
	int col = get_global_id(0);

	float gx = 0.0f;
	float gy = 0.0f;
	float G = 0.0f;

	for (int i = row - (range); i < row + (range + 1); i++)	{
		for (int j = col - (range * 3); j < col + (range + 1)*3 ; j+=3){
			if (!(i < 0) && !(i > H) && !(j < 0) && !(j > W*3)){

				gx += image_matrix[j + i * W * 3] *
							prewittX[(row - i + range) * 3 + (col -j)/3 + range];

				gy += image_matrix[j + i * W * 3] *
							prewittY[(row - i + range) * 3 + (col -j)/3 + range];
			}
		}
	}
  	G = sqrt((gx*gx)+(gy*gy));

	output[row*W*3 + col] = G;
}
