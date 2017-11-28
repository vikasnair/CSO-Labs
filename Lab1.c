/*
AUTHOR: Vikas Nair
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function declarations */

void arrange(int *, int);
void find_fibonacci(int, int);
void flipping(unsigned int);
void file_histogram(char *);
void file2upper(char *);
void file_encrypt(char *);
void swap(int *a, int *b);
int fib (int n);

// swap helper function with pointers used in a simple sorting algorithm, used in the first problem

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

// recursive helper function to find fibonacci for a single int n, used in the second problem

int fib(int n) {
	if (n <= 1) 
		return n;

	return fib(n - 1) + fib(n - 2);
}

/*********************************************************************************/

int main(int argc, char * argv[])
{
  int option = 0;
  int i, j;
  int * list;
  
  if(argc < 2 )
  {
     fprintf(stderr,"Usage: lab1 num [input]\n");
     fprintf(stderr,"num: 1, 2, 3, 4, 5, or 6\n");
     exit(1);
  }
  
  option = atoi(argv[1]);
  
  switch(option)
  {
    case 1: if(argc != 3)
	    {
	      fprintf(stderr,"Usage: lab1 1 num\n");
	      fprintf(stderr,"num: number of elements of the array to be arranged\n");
	      exit(1);
	    }
	    j = atoi(argv[2]);
	    list = (int *)malloc(j*sizeof(int));
	    if(!list)
	    {
	      fprintf(stderr,"Cannot allocate list in option 1\n");
	      exit(1);
	    }
	    
	    /* Gnerate random numbers in the range [0, 100) */
	    for(i = 0; i < j; i++)
	      list[i] = rand()% 100;
	    
	    /* Print the unsorted array */
	    printf("The original array:\n");
	    for(i = 0; i < j; i++) 
	      printf("%d ", list[i]);
	    printf("\n");
	    
	    printf("The arranged array:\n");
	    arrange(list, j);
	    
	    break;
	    
	    
    case 2: if(argc != 4)
	    {
	      fprintf(stderr,"Usage: lab1 2 x y\n");
	      fprintf(stderr,"x and y: positive integers and x < y and y < 1 million\n");
	      exit(1);
	    }
	    i = atoi(argv[2]);
	    j = atoi(argv[3]);
	    
	    find_fibonacci(i, j);
	    
	    break;

	    
    case 3: if(argc != 3)
	    {
	      fprintf(stderr,"Usage: lab1 3 num\n");
	      fprintf(stderr,"num: unsigned intger number\n");
	      exit(1);
	    }
	    
	    flipping( atof(argv[2]));
	    
	    break; 
	    
	    
    case 4: if(argc != 3)
	    {
	      fprintf(stderr,"Usage: lab1 4 filename\n");
	      exit(1);
	    }
	    
	    file_histogram(argv[2]);
	    
	    break;

	    
    case 5: if(argc != 3)
	    {
	      fprintf(stderr,"Usage: lab1 5 filename\n");
	      exit(1);
	    } 
	    
	    file2upper(argv[2]);
	    
	    break;

	    
    case 6: if(argc != 3)
	    {
	      fprintf(stderr,"Usage: lab1 46filename\n");
	      exit(1);
	    }
	    
	    file_encrypt(argv[2]);
	    
	    break;	      
	    
    default: fprintf(stderr, "You entered an invalid option!\n");
	     exit(1);
  }
  
  return 0;
}

/*
 * Part 1:
 * inputs: an array of int list[], number of elements in that array: num
 * outputs: prints array with even numbers first (if any), sorted in ascending order, followed by the odd numbers (if any) sorted in ascending order too.
 * Example: a list of 5 elements: 5 4 3 2 1 
 * The output will be: 2 4 1 3 5 
*/

void arrange(int *list, int num) {

	// declaring accumulator variables

	int i, left = 0, right = num - 1;

	// first, segregate even and odd integers to two sides

	while (left < right) {

		// skip if in correct positions

		while (list[left] % 2 == 0 && left < right) 
			left++;
		while (list[right] % 2 == 1 && left < right)
			right--;

		// else, swap

		if (left < right) {
			swap(&list[left], &list[right]);
			left++;
			right--;
		}
	}

	// modified bubble sort, only swap evens with evens, odds with odds if out of order

	for (i = 0; i<num; i++)
		for (int j = 0; j < num - i - 1; j++)
			if ((list[j] % 2 == 0 && list[j + 1] % 2 == 0) || (list[j] % 2 != 0 && list[j + 1] % 2 != 0))
				if (list[j] > list[j + 1])
					swap(&list[j], &list[j + 1]);
	
	// loop through and print

	for (i = 0; i < num; i++)
		printf("%d ", list[i]);
}


/*********************************************************************************/

/* 
 * Part 2:
 * inputs: two positive integer, x and y, larger than 0.
 * outputs: print all the Fibonacci numbers between x and y (NOT including x and y themselves), if any.
*/

void find_fibonacci(int x, int y) {

	// call the helper fibonacci function from 0 ... n, only print if the result is within range

	int i = 0;

	while (fib(i) < y) {
		int n = fib(i);

		if (n > x)
			printf("%d ", n);
		
		i++;
	} 
}


/*********************************************************************************/

/*
 * Part 3:
 * inputs: an unsigned integer (so has values of 0 and up)
 * outputs: the flip of that number, printed to screen
 * if the number given is: 1234  then you print: 4321
*/

void flipping(unsigned int num) {

	// accumulator variable

	int reversed = 0;
	
	// continually iterate, add remainder after dividing from the variable base place

	while (num > 0) {
		reversed *= 10;
		reversed += (num % 10);
		num /= 10;
	}

	printf("%d", reversed);
}

/*********************************************************************************/

/*
 * Part 4
 * inputs: filename, contains a string of characters (can be upper case letters, lower case letters, numbers, ...).
 * outputs: histogram of the file printed on the screen ONLY for lower case letters.
 * Example: 
 * The input file in.txt contains:  a1aaAbBBb709bbc
 * The output will be:
 * a: 3
 * b: 4
 * c: 1
 * .... and so one
 * The file can contain any characters, not necessarily only lower case characters.
*/

void file_histogram(char *filename) {

	// create a file and memory to add the contained string

	FILE *file;

	char string[100];

	// open file for read, attempt to write contents to array
	
	file = fopen(filename, "r");

	if (file != NULL) {
		if (fgets(string, 100, file) != NULL) 
			puts(string);
		else 
			printf("Error writing to string.");
	} else 
		printf("Error opening file for read permisson.");

	fclose(file);

	// declare accumulator, empty array to hold count for each letter
			
	int i = 0, count[26] = { 0 };

	// loop through the string read from file, plus-equal count at respective position in array

	while(string[i] != '\0') {
		if (string[i] >= 'a' && string[i] <= 'z')
			count[string[i] - 'a']++;
		i++;
	}

	// loop through and print counts

	for (i = 0; i < 26; i++) {
		printf("%c: %d\n", i + 'a', count[i]);
	}
}

/*********************************************************************************/

/* 
 * Part 5:
 * inputs: filename, ONLY contain lower case letters and no spaces.
 * output:filenameCAPITAL, contains the same characters as the input file but in upper case.
 * If the input filename is: mmmm 
 * The output filename is: mmmmCAPITAL
*/

void file2upper(char *filename) {

	// create a file and memory to add the contained string

	FILE *file;

	char string[100];

	// open file for read, attempt to write contents to array
	
	file = fopen(filename, "r");

	if (file != NULL) {
		if (fgets(string, 100, file) != NULL) 
			puts(string);
		else 
			printf("Error writing to string.");
	} else 
		printf("Error opening file for read permisson.");

	fclose(file);

	// a bunch of hack-y logic to essentially get substring and add custom extension
	
	char* filename_without_extension = 0;
	
	filename_without_extension = (char*)malloc(strlen(filename) - 3);
	memcpy(filename_without_extension, filename, strlen(filename) - 4);
	filename_without_extension[strlen(filename) - 4] = 0;

	char* extension = "CAPITAL.txt";
	
	char* filename_with_extension = malloc(strlen(filename_without_extension) + strlen(extension)  + 2);

	strcpy(filename_with_extension, filename_without_extension);
 	strcat(filename_with_extension, extension);

 	// open file for write with modified extension, attempt to write contents to array

	FILE *new_file = fopen(filename_with_extension, "w");
	
	if (new_file != NULL) {
		int i = 0;
		
		// loop through string, if lowercase convert to uppercase using ascii operations

		while(string[i] != '\0') {
			if(string[i] >= 'a' && string[i] <= 'z') {
				string[i] -= 32;
				fprintf(new_file, "%c", string[i]);
			}
			
			i++;
		}
	} else
		printf("Error opening file for write permisson.");

	fclose(new_file);
}

/*********************************************************************************/

/*
 * Part 6: implement a very simple encryption.
 * inputs: filename, contains a series of lower case charaters (may be separated by white space),
 * outputs: replace all non-white space with the lower case letter that exists 3 letters before, in a circular way.
 * For example: 
 * e will be replaced with b
 * d will be replaced with a 
 * c will be replaced with z  <--- circular
 * b will be replaced with y  <--- circular
 * and white spaces will be left unchanged.
 * Print the output on the screen.
*/

void file_encrypt(char * filename) {

	// create a file and memory to add the contained string
 
	FILE *file;

	char str[100];

	// open file for read, attempt to write contents to array
	
	file = fopen(filename, "r");

	if (file != NULL) {
		if (fgets(str, 100, file) != NULL) 
			puts(str);
		else 
			printf("Error writing to string.");
	} else 
		printf("Error opening file for read permisson.");

	fclose(file);

	// loop through string, decrement each item by three using ascii operations (if the result is out of range, adjust range)
	
	int i = 0;

	while(str[i] != '\0') {
		if (str[i] >= 'd' && str[i] <= 'z')
			str[i] -= 3;
		else if (str[i] >= 'a' && str[i] <= 'c') 
			str[i] += 22;
		i++;
	}

	for (int j = 0; j <= i; j++)
		if ((str[j] >= 'a' && str[j] <='z') || str[j] == ' ')
			printf("%c", str[j]);
}