#include <assert.h>
#include <string.h>

#include "str.h"


void test_strcpy() {
	char first[50] = "zdravsvyinebo";
	char second[50] = "voblakah";
	char true_res[50] = "voblakah";
	char * our_res = my_strcpy(first, second);
	assert(!strcmp(true_res, our_res));
}


void test_strcat() {
	char first[50] = "ok";
	char second[50] = "yznali";
	char true_res[50] = "okyznali";
	char * our_res = my_strcat(first, second);
	assert(!strcmp(true_res, our_res));
}


void test_strcmp() {
	char first[50] = "zdravstvyiunost'vsapogah";
	char second[50] = "zdravstvyiunost'vsapogah";
	int true_res = 0;
	int our_res = my_strcmp(first, second);
	assert(true_res == our_res);
}


void test_strlen() {
	char string[50] = "fintinasyah";
	size_t true_res = 11;
	size_t our_res = my_strlen(string);
	assert(true_res == our_res);
}
