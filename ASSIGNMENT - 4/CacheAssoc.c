#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>
#include <time.h>

//We already know Cache block size is 64B
//We also know Cache sets are 64;

void help(int *c,int j)
{ 
    uint64_t t1, t2, ov, diff2;
 volatile int temp;
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
        temp = *c;
        _mm_lfence();
       t2 = __rdtsc();
       _mm_lfence();

        diff2 = t2 - t1;
printf("Block - %d  --  Access Time:- %lld\n", j, diff2 - ov);
         

}

int main()
{
    
    int d[100000];
    int *a = &d[0];

    
    unsigned long long int b = 1 <<10 ;
   
    int i,j;

    for (i = 0;i < 10000;i++)
 {
_mm_clflush( &a[i]);
    _mm_lfence();
 }
      
      uint64_t t1,t2,ov;
        t1 = __rdtsc();
    _mm_lfence();
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    ov = t2 - t1;

_mm_clflush( d);
    _mm_lfence();

    for (i = 1;i < 13;i++)
    {
         int *c;
         int h;

 printf("Blocks loaded %d\n",i);
       for (j = 0;j < i;j++)
       {
             c = a + b*(j); 
             h = *c;
       }

       
        
       
       
         for (j = 0;j < i; j++ )
         {
           

            
            c = a + b*(j);
            _mm_lfence();
            help(c,j);
            _mm_lfence();
          
            
            
         }

             

             printf("\n");

    

  
    }



}