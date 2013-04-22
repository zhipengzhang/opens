#ifndef ___FREQPOOL_H
#define ___FREQPOOL_H 1

#include "Common.h"

namespace PreCmpt{

const int POOL_SIZE = 16;

struct freq_p{
   int* p;
   int size;
   };

class freq_pool{
 

   struct freq_p pool[POOL_SIZE];
   
   
   public:
	   freq_pool();
	   int malloc_number,free_number;
       int *malloc_freq(int size);
       void free_freq(int *p,int size);
       ~freq_pool();
};

}
#endif