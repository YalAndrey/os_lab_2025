#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>
#include "utils.h"
#include <pthread.h>

struct SumArgs {
  int *array;
  int begin;
  int end;
};


int Sum(const struct SumArgs *args) {
  int sum = 0;
  for (int i = args->begin; i < args->end; i++) 
    sum += args->array[i];
  return sum;
}

void *ThreadSum(void *args) {
  struct SumArgs *sum_args = (struct SumArgs *)args;
  return (void *)(size_t)Sum(sum_args);
}