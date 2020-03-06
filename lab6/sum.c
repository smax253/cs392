/*******************************************************************************
 * Name        : sum.c
 * Author      : Max Shi and Hamzah Nizami
 * Date        : 3/6/2020
 * Description : Implementation of libsum.so
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include "sum.h"

/**
 * TODO:
 * Takes in an array of integers and its length.
 * Returns the sum of integers in the array.
 */
int sum_array(int *array, const int length) {
	int sum = 0; 
	for(int i = 0; i < length; i++){ 
		sum += *array;
		array++;
	}
	return sum;

}
