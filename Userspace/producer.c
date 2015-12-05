#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

#define N 5
#define MAX_LENGTH 300
int main(){
  
  fd = open("/dev/mypipe", O_WRONLY);
	// check for error during open 

	while(TRUE){

		//  generate a string somehow, making sure to identify the producer and the string number
		// For example,
		//		"Producer p generated this string i"
		// increment i across each loop iteration 
		// use a unique p for each producer.

		// write string to pipe
		n = write( fd, string, size_of_string);
		// don't forget to check for write error. 
	}

	close(fd);

  return 0;
}
