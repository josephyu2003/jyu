#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <errno.h>   // errno
#include <time.h>     

#define BUF_SIZE 2048 //buffer size

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char* src_filename, char* dst_filename) {
	
	FILE *src = fopen(src_filename, "r");	// opens a file for reading
	if (src == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		exit(0);
	}
	FILE *dst = fopen(dst_filename, "w");	// opens a file for writing; erases old file/creates a new file
	if (dst == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		exit(0);
	}

	char *buf = malloc((size_t)BUF_SIZE);  // allocate a buffer to store read data
	size_t byte_read;
	
	// reads content of file is loop iterations until end of file
	while((byte_read = fread(buf, 1, BUF_SIZE, src)) > 0) {
	  fwrite(buf, 1, byte_read, dst);
	}

	// closes src file pointer
	fclose(src);
	
	// closes dst file pointer
	fclose(dst);
	
	// frees memory used for buf
	return 0;
}

int main(int argc, char* argv[]) {
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        if (argc != 3) {  // check correct usage
		fprintf(stderr, "usage: %s <src_filename> <dst_filename>\n", argv[0]);
		exit(1);
	}
	//get the source and destination files from the command line arguments
	func_copy(argv[1], argv[2]);	
	
	//call the check copy times function
	end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("%f sec\n", cpu_time_used);
	return 0;
}
