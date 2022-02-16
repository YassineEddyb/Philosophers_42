#include <sys/time.h>
#include <stdio.h>
 
int main() {
 
  struct timeval start, end;
  gettimeofday(&start, NULL);
 
  for (int i = 0; i < 9999999999 ; i++) {
  }
 
  gettimeofday(&end, NULL);
  printf("Time taken to count to 10^5 is : %ld micro seconds\n",
    ((end.tv_sec * 1000) -
    (start.tv_sec * 1000)));

  return 0;
}