#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>
#include "utils.h"
#include "parallel_s.h"
#include <pthread.h>


int main(int argc, char **argv) {

  int threads_num = -1;
  int seed = -1;
  int array_size = -1;


  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"threads_num", required_argument, 0, 0},
                                      {"seed", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                                                  
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;


    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            threads_num = atoi(optarg);
             if (threads_num <= 0){ 
                printf("Error threads_num\n");
                return 1;}
          
            break;
          case 1:
            seed = atoi(optarg);

             if (seed <= 0){ 
                printf("Error seed\n");
                return 1;}
         
            break;
          case 2:
            array_size = atoi(optarg);
            if (array_size <= 0) {
                printf("Error array_size\n");
                return 1;
            }
      
            break;

          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;

      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (seed == -1 || array_size == -1 || threads_num == -1) {
    printf("Usage: %s --threads_num \"num\" --seed \"num\" --array_size \"num\"\n",
           argv[0]);
    return 1;
  }

  int total_sum = 0;


  pthread_t threads[threads_num];

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);
  struct SumArgs arg;
  arg.array = array;
  arg.begin = 0;
  arg.end = array_size;
  total_sum = Sum(&arg);

  printf("Total: %d\n", total_sum);

  struct timeval start_time, end_time;
  
  gettimeofday(&start_time, NULL);
  
  int chunk_size = array_size / threads_num;
  struct SumArgs args[threads_num];
  for (int i = 0; i < threads_num; i++) {
    args[i].array = array;
    args[i].begin = i * chunk_size;
    args[i].end = (i == threads_num - 1) ? array_size : (i + 1) * chunk_size;
    
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args[i])) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  total_sum = 0;
  for (int i = 0; i < threads_num; i++) {
    void *result;
    pthread_join(threads[i], &result);
    total_sum += (int)(size_t)result;
  }

  gettimeofday(&end_time, NULL);
        
  double elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000.0;
  printf("Elapsed time: %fms\n", elapsed_time);
  free(array);
  printf("Total: %d\n", total_sum);
  return 0;
}
