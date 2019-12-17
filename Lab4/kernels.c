/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "rlv220",              		/* Team name */

    "Raymond Van Zandt",     	/* First member full name */
    "rlv220",  					/* First member email address */

    "",                   		/* Second member full name (leave blank if none) */
    ""                    		/* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
	int i, j;
    int dst_index = (dim - 1) * dim;
    int src_index = 0;

//Assume dim of size 32
    for(i = 0; i < dim; i += 32)
    {
    	for(j = 0; j < dim; j++)
	      {
			  //unroll loop (32 total groups
    	      dst[dst_index] = src[src_index];
        	  dst_index++;
         	  src_index += dim;

	          dst[dst_index] = src[src_index];
	          dst_index++;
 	          src_index += dim;

    	      dst[dst_index] = src[src_index];
  	      	  dst_index++;
	          src_index += dim;

    	      dst[dst_index] = src[src_index];
        	  dst_index++;
	          src_index += dim;

    	      dst[dst_index] = src[src_index];
        	  dst_index++;
	          src_index += dim;

    	      dst[dst_index] = src[src_index];
        	  dst_index++;
          	  src_index += dim;

    	      dst[dst_index] = src[src_index];
    	      dst_index++;
	          src_index += dim;

          	  dst[dst_index] = src[src_index];
              dst_index++;
       	      src_index += dim;

   	          dst[dst_index] = src[src_index];
    	      dst_index++;
	          src_index += dim;

        	  dst[dst_index] = src[src_index];
    	      dst_index++;
	          src_index += dim;

        	  dst[dst_index] = src[src_index];
    	      dst_index++;
	          src_index += dim;

        	  dst[dst_index] = src[src_index];
    	      dst_index++;
	          src_index += dim;

         	  dst[dst_index] = src[src_index];
    	      dst_index++;
   	          src_index += dim;

        	  dst[dst_index] = src[src_index];
    	      dst_index++;
	          src_index += dim;

        	  dst[dst_index] = src[src_index];
       	      dst_index++;
          	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

	          dst[dst_index] = src[src_index];
    	      dst_index++;
        	  src_index += dim;

        	  dst[dst_index] = src[src_index];
    	      dst_index++;
	          src_index += dim;

        	  dst[dst_index] = src[src_index];
    	      dst_index++;
	          src_index += dim;

    	      dst[dst_index] = src[src_index];
	          src_index -= 31 * dim;
        	  src_index++;
    	      dst_index -= 31;
	          dst_index -= dim;
 		}
	    dst_index += dim * dim;
   		dst_index += 32;
	    src_index += 31 * dim;
    }
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
		    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
 int i, j, temp, temp_dim;

    //Upper Left
    dst[0].red = (src[0].red + src[1].red + src[dim].red + src[dim + 1].red) >> 2;
    dst[0].blue = (src[0].blue + src[1].blue + src[dim].blue + src[dim + 1].blue) >> 2;
    dst[0].green = (src[0].green + src[1].green + src[dim].green + src[dim + 1].green) >> 2;

    //Upper Right
    dst[dim - 1].red = (src[dim - 1].red + src[dim - 2].red + src[dim * 2 - 1].red + src[dim * 2 - 2].red) >> 2;
    dst[dim - 1].blue = (src[dim - 1].blue + src[dim - 2].blue + src[dim * 2 - 1].blue + src[dim * 2 - 2].blue) >> 2;
    dst[dim - 1].green = (src[dim - 1].green + src[dim - 2].green + src[dim * 2 - 1].green + src[dim * 2 - 2].green) >> 2;

    //Lower Left
    dst[dim * (dim - 1)].red = (src[dim * (dim - 1)].red + src[dim * (dim - 1) + 1].red + src[dim * (dim - 2)].red + src[dim * (dim - 2) + 1].red) >> 2;
    dst[dim * (dim - 1)].blue = (src[dim * (dim - 1)].blue + src[dim * (dim - 1) + 1].blue + src[dim * (dim - 2)].blue + src[dim * (dim - 2) + 1].blue) >> 2;
    dst[dim * (dim - 1)].green = (src[dim * (dim - 1)].green + src[dim * (dim - 1) + 1].green + src[dim * (dim - 2)].green + src[dim * (dim - 2) + 1].green) >> 2;

    //Lower Right
    dst[dim * dim - 1].red = (src[dim * dim - 1].red + src[dim * dim - 2].red + src[dim * (dim - 1) - 1].red + src[dim * (dim - 1) - 2].red) >> 2;
    dst[dim * dim - 1].blue = (src[dim * dim - 1].blue + src[dim * dim - 2].blue + src[dim * (dim - 1) - 1].blue + src[dim * (dim - 1) - 2].blue) >> 2;
    dst[dim * dim - 1].green = (src[dim * dim - 1].green + src[dim * dim - 2].green + src[dim * (dim - 1) - 1].green + src[dim * (dim - 1) - 2].green) >> 2;

	int upper_edge_start = 1;
	int upper_edge_end = dim-1;

	int lower_edge_start = dim * (dim - 1) + 1;
	int lower_edge_end = dim * dim -1;

	int left_edge_start = dim;
	int left_edge_end = dim * (dim - 1);

	int right_edge_start = dim + dim - 1;
	int right_edge_end = dim * dim - 1;

	int center_start = 1;
	int center_end = dim-1;

    for (j = upper_edge_start; j < upper_edge_end; j++)
    {
        dst[j].red = (src[j].red + src[j - 1].red + src[j + 1].red + src[j + dim].red + src[j + 1 + dim].red + src[j - 1 + dim].red) / 6;
        dst[j].blue = (src[j].blue + src[j - 1].blue + src[j + 1].blue + src[j + dim].blue + src[j + 1 + dim].blue + src[j - 1 + dim].blue) / 6;
        dst[j].green = (src[j].green + src[j - 1].green + src[j + 1].green + src[j + dim].green + src[j + 1 + dim].green + src[j - 1 + dim].green) / 6;
    }

    for (j = lower_edge_start; j < lower_edge_end; j++)
    {
        dst[j].red = (src[j].red + src[j - 1].red + src[j + 1].red + src[j - dim].red + src[j + 1 - dim].red + src[j - 1 - dim].red) / 6;
        dst[j].blue = (src[j].blue + src[j - 1].blue + src[j + 1].blue + src[j - dim].blue + src[j + 1 - dim].blue + src[j - 1 - dim].blue) / 6;
        dst[j].green = (src[j].green + src[j - 1].green + src[j + 1].green + src[j - dim].green + src[j + 1 - dim].green + src[j - 1 - dim].green) / 6;
    }

    for (j = left_edge_start; j < left_edge_end; j += dim)
    {
        dst[j].red = (src[j].red + src[j - dim].red + src[j + 1].red + src[j + dim].red + src[j + 1 + dim].red + src[j - dim + 1].red) / 6;
        dst[j].blue = (src[j].blue + src[j - dim].blue + src[j + 1].blue + src[j + dim].blue + src[j + 1 + dim].blue + src[j - dim + 1].blue) / 6;
        dst[j].green = (src[j].green + src[j - dim].green + src[j + 1].green + src[j + dim].green + src[j + 1 + dim].green + src[j - dim + 1].green) / 6;
    }

    for (j = right_edge_start; j < right_edge_end; j += dim)
    {
        dst[j].red = (src[j].red + src[j - 1].red + src[j - dim].red + src[j + dim].red + src[j - dim - 1].red + src[j - 1 + dim].red) / 6;
        dst[j].blue = (src[j].blue + src[j - 1].blue + src[j - dim].blue + src[j + dim].blue + src[j - dim - 1].blue + src[j - 1 + dim].blue) / 6;
        dst[j].green = (src[j].green + src[j - 1].green + src[j - dim].green + src[j + dim].green + src[j - dim - 1].green + src[j - 1 + dim].green) / 6;
    }

    temp_dim = dim;
    for (i = center_start; i < center_end; i++)
    {
        for (j = center_start; j < center_end; j++)
        {
            temp = temp_dim + j;
            dst[temp].red = (src[temp].red + src[temp - 1].red + src[temp + 1].red + src[temp - dim].red + src[temp - dim - 1].red + src[temp - dim + 1].red + src[temp + dim].red + src[temp + dim + 1].red + src[temp + dim - 1].red) / 9;
            dst[temp].green = (src[temp].green + src[temp - 1].green + src[temp + 1].green + src[temp - dim].green + src[temp - dim - 1].green + src[temp - dim + 1].green + src[temp + dim].green + src[temp + dim + 1].green + src[temp + dim - 1].green) / 9;
            dst[temp].blue = (src[temp].blue + src[temp - 1].blue + src[temp + 1].blue + src[temp - dim].blue + src[temp - dim - 1].blue + src[temp - dim + 1].blue + src[temp + dim].blue + src[temp + dim + 1].blue + src[temp + dim - 1].blue) / 9;
        }
        temp_dim += dim;
    }
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

