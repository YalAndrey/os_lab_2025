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

int Sum(const struct SumArgs *args);

void *ThreadSum(void *args);