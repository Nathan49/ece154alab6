/*
Nathan Bornfreund
ECE 154A - Fall 2018
Lab 6 - Mystery Caches
Due: 12/7/18, 11:00 pm

Mystery Cache Geometries:
mystery0:
    block size = 4194304
    cache size = 64
    associativity = 16
mystery1:
    block size = 4 bytes
    cache size = 4096 bytes
    associativity = 1
mystery2:
    block size = 32 bytes
    cache size = 4096 bytes
    associativity = 128
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/* 
   Returns the size (in B) of the cache
*/
int get_cache_size(int block_size) {
  /* YOUR CODE GOES HERE */
  flush_cache();
  int i = 0;
  int z = i;
  int x = 1;
  while(1) {
	  for(int k = z; k < i + block_size; k += block_size) {
		 access_cache(k);
	  } 
	  for(int c = 0; c < i + block_size; c+= block_size) {
		if(!access_cache(c)) {
		  	x = 0;
		  	break;
		}
	  }
		if(!x)
			break;
		z = i;
	  i *= 2;
	  if(i == 0)
		  i+=1;
  }
  return i;
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
	flush_cache();
	int i = 0;
	int x = 1;
	while(x) {
		access_cache(i);
		for(int c = 0; c < i + size; c+= size) {
			if(!access_cache(c)) {
				x = 0;
				break;
			}
		}
		i+= size;
	}
	return (i - size)/size;
}

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size() {
  /* YOUR CODE GOES HERE */
	flush_cache();
	int i = 0;
	while(1) {
		access_cache(i);
		i += 4;
		if(!access_cache(i))
			break;
	}
	return i;
}

int main(void) {
  int size;
  int assoc;
  int block_size;
  
  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.
     You can test your geometry paramter discovery routines by 
     calling cache_init() w/ your own size and block size values. */
  cache_init(0,0);
  
  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);


  printf("Cache size: %d bytes\n",size);
  printf("Cache associativity: %d\n",assoc);
  printf("Cache block size: %d bytes\n",block_size);
  
  return EXIT_SUCCESS;
}
