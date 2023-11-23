#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>
#include <time.h>


int main()
{
   int a[200];

  

    volatile int i, temp;
 uint64_t t1, t2, ov, diff2;
    for (i = 0;i < 200 ;i++)
    {
    _mm_clflush( &a[i ] );
    _mm_lfence();
    
    }



     _mm_lfence();
    t1 = __rdtsc();
    _mm_lfence();
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    ov = t2 - t1;

    

    for (i = 0;i < 190;i++)
    {
         _mm_lfence();
    t1 = __rdtsc();
    _mm_lfence();
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    ov = t2 - t1;

        _mm_lfence();
        t1 = __rdtsc();
        _mm_lfence();
        temp = a[i];
        _mm_lfence();
       t2 = __rdtsc();
       _mm_lfence();


       diff2 = t2 - t1;
      // printf("%ld\n",diff2);
      // diff2 -= ov;
    

       printf("Offset  %-3d  --- Access time :- %ld  \n",i,diff2 - ov);
    }


   


}