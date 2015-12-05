#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include <semaphore.h>

#define N 5
#define MAX_LENGTH 100

void consumer(void){
	int bytes_read = 0;
	int fd;
	char *buffer;
	int j;
	int cons= 0;
	int iteration = 0;
	int count = 0;
	/* allocate memory for character buffers HERE before you use them */
	buffer = (char*)calloc(MAX_LENGTH, sizeof(char));
	if (buffer == NULL){
		return errno;
	}


  	fd = open("/dev/mypipe", O_RDWR);
  	if (fd < 0) {
		perror("Failed to open mypipe");
		return errno;
		}
	// check for error during open 
	while(count < N){
		bytes_read = read(fd, buffer, MAX_LENGTH); // read a string from the pipe
		if (bytes_read < 0){
			perror("Failed to read from the kernel");
			return errno;
		}
		// don't forget to check for readerror. 
		++cons;
		++iteration;
		// print the string to screen, making sure to identify the consumer who read it
		// For example,
		//		"Consumer c, iteration j:" followed by string you read above 
		// increment j across each loop iteration 
		// use a unique c for each consumer.
		printf("Consumer %d, iteration %d : %s \n", cons, iteration, buffer);
		count++;
	}
free(buffer);
close(fd);
}

void producer(void){
 int fd;
 int n = 0;
 int size_of_string = 0;
 char string[] = "hello world";
 int j;
 int i;
 int stringNum = 0;
 int prod = 0;
 int count = 0;

	/* allocate memory for character buffers HERE before you use them */
  fd = open("/dev/mypipe", O_RDWR);
	// check for error during open
	printf("%d\n", N);
	if (fd < 0) {
		perror("Failed to open mypipe");
		return errno;
		}

	while(count < N){
		//srand(time(NULL));
		//for (i = 0; i < MAX_LENGTH; ++i){
		//	string[i] = '0' + rand()%72;
		//}d";
		stringNum++;
		prod++;
		//printf("Producer %d ", prod);
		//  generate a string somehow, making sure to identify the producer and the string number
		// For example,
		//		"Producer p generated this string i"
		// increment i across each loop iteration 
		// use a unique p for each producer.
		printf("Producer %d generated this string %d : %s \n", prod,stringNum, string);
		// write string to pipe
		printf("count %d\n", count);
		count++;
		n = write(fd, string, strlen(string));
		if (n < 0){
			perror("Failed to write to the kernel");
			return errno;
			}
			// don't forget to check for write error. 
	}
close(fd);
}

int main(){
	char ch;
        printf ("Press r to read from device or w to write the device ");
        scanf ("%c", &ch);
	if (ch == 'w'){
		producer();
	}
	else if(ch == 'r'){
		consumer();
	}
	else{
	    printf("wrong character");
		return -1;
	}
return 0;
}
