#include "./PreComputation/FreqPool.h"

namespace PreCmpt{

freq_pool::freq_pool(){
    malloc_number=0;
	free_number=0;
	int i;
    for(i=0;i<POOL_SIZE;i++){
        pool[i].p=NULL;
	    pool[i].size=0;
	}
}

freq_pool::~freq_pool(){
	for(int i=0;i<POOL_SIZE;i++){
		if(pool[i].p!=NULL)
			delete []pool[i].p;
	}
}

int* freq_pool::malloc_freq(int size){
   int i;
   int* tp;
   for(i=0;i<POOL_SIZE;i++){
     if((pool[i].p!=NULL)&&(pool[i].size>=size)){
	    tp=pool[i].p;
		pool[i].p=NULL;
		pool[i].size=0;
		return tp;
		}
   }
   //tp=(int *) malloc(size);
   tp=new int[size];
   if(tp==NULL)
	   printf("malloc is error");
   malloc_number++;
   return tp;
}

void freq_pool::free_freq(int *p,int size){
    int i;
	int temp=0;
	int temp_pool=pool[0].size;
	for(i=0;i<POOL_SIZE;i++){
	    if(temp_pool>pool[i].size){
			temp_pool=pool[i].size;
			temp=i;
		}
		
	}
	if(temp_pool<size){
		if(pool[temp].p!=NULL){
		    //free(pool[temp].p);
			delete []pool[temp].p;
			free_number++;
		}
		pool[temp].p=p;
		pool[temp].size=size;
	}
	else{
		//free(p);
		delete []p;
		free_number++;
	}
}
     
}
