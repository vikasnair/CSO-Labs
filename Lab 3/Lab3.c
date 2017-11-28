#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*	Constants	*/
#define ADDRS_LENGTH  64 /* address length */ 

/*	Global variables	*/
unsigned long total_cache_size = 0; /* total size in bytes */
unsigned long block_size = 0; /* block size in bytes */
unsigned long associativity = 0;
unsigned long num_sets = 0; /* number of sets in the cache */

/* 	Function declarations	*/
/* You need to implement these functions without changes their declarations */
void find_num_sets();
unsigned long find_total_num_blocks();
unsigned int num_bits_set();
unsigned int num_bits_offset();
unsigned int num_bits_tag();
unsigned long find_set(unsigned long);
unsigned long find_tag(unsigned long);
unsigned long find_offset(unsigned long);


int main(int argc, char * argv[])
{
  FILE *fp;
  unsigned long address = 0;
  
  if(argc != 5)
  {
      printf("usage: ./cache size assoc blk filename\n");
      printf("size: total cache size in bytes\n");
      printf("assoc: associativity of the cache (#blocks per set)\n");
      printf("blk: block size in bytes\n");
      printf("filename: the name of the file that contains addresses\n");
      exit(1);
  }
  
  
  total_cache_size = (unsigned long)atol(argv[1]);
  associativity = (unsigned long) atol(argv[2]);
  block_size = (unsigned long) atol(argv[3]);
  
  find_num_sets();
  
  /* Now  printing all cache specs and statistics */
  printf("\n");
  printf("Total cache size (in bytes): %ld\n", total_cache_size);
  printf("Number of sets: %ld \n", num_sets);
  printf("Associativity: %ld \n", associativity);
  printf("Block size (in bytes): %ld \n", block_size);
  printf("Total number of blocks in the cache: %lu\n", find_total_num_blocks());
  
  printf("Number of address bits for set: %u\n", num_bits_set());
  printf("Number of address bits for offset: %u\n", num_bits_offset());
  printf("Number of address bits for TAG: %u\n\n", num_bits_tag());
  
  /* Generating tags, sets, and offsets for each address in the file */
  
  if (!(fp = fopen(argv[4],"r")) )
  {
      printf("Cannot open file %s\n", argv[4]);
      exit(1);
  }
  
  while(fscanf(fp,"%lx ", &address) == 1)
  {
    printf("address = 0x%lx  TAG = %lu   SET = %lu   OFFSET = %lu\n", 
	    address,
	    find_tag(address),
	    find_set(address),
	    find_offset(address)
	  );
    
  }
  
  fclose(fp); 
  
  return 0;
}

/**********************************************************************/
/* This function uses the global variables declared above to calculate
 * the total number of sets and store it in the global variable: num_sets
 */

void find_num_sets(){
  num_sets = total_cache_size / (block_size * associativity);
}



/**********************************************************************/
/* This function uses the global variable above to calculate the total
 * number of blocks in the whole cache and returns it */
unsigned long find_total_num_blocks(){
  return num_sets * associativity;
}


/**********************************************************************/
/* This function uses the global variables declared above to calculate
 * the number of bits from the address used for the set number */
unsigned int num_bits_set(){
  return (unsigned int) log2(num_sets);
}

/**********************************************************************/
/* This function uses the global variables declared above to calculate
 * the number of bits from the address used for the offset */
unsigned int num_bits_offset(){
  return (unsigned int) log2(block_size);
}

/**********************************************************************/
/* This function uses the global variables declared above to calculate
 * the number of bits from the address used for the TAG */
unsigned int num_bits_tag(){
  return (unsigned int) ADDRS_LENGTH - num_bits_set() - num_bits_offset();
}


/**********************************************************************/
/* This function takes an address and returns the set number. It can make
 * use of the global variables above and/or make use of the functions 
 *  num_bits_offset(), num_bits_set(), num_bits_tag()
 */
unsigned long find_set(unsigned long address){
  return (address << num_bits_tag()) >> (num_bits_tag() + num_bits_offset());
}


/**********************************************************************/
/* This function takes an address and returns the tag. It can make
 * use of the global variables above and/or make use of the functions 
 *  num_bits_offset(), num_bits_set(), num_bits_tag()
 */
unsigned long find_tag(unsigned long address){
  return address >> ((unsigned long) num_bits_offset() + (unsigned long) num_bits_set());
}


/**********************************************************************/
/* This function takes an address and returns the offset. It can make
 * use of the global variables above and/or make use of the functions 
 *  num_bits_offset(), num_bits_set(), num_bits_tag()
 */
unsigned long find_offset(unsigned long address){
  return address & (block_size - 1);
}
/**********************************************************************/
