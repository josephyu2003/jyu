#include <stdlib.h>  // malloc(), free()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <errno.h>   // errno
#include <time.h>     

#define BUF_SIZE 2048 //buffer size

// copies a files form src_filename to dst_filename using syscalls open(), read(), write(), close()
int syscall_copy(char* src_filename, char* dst_filename)  {
	
	int src_fd = open(src_filename, O_RDONLY);	// opens a file for reading
	if (src_fd < 0) { // open() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		close(src_fd);
		exit(0);
	}

	// opens a file for writing; erases old file/creates a new file
	int dst_fd = open(dst_filename, O_WRONLY);	
	if (dst_fd < 0) { // open() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		close(dst_fd);
		exit(0);
	}

	// read/ write loop
	void *buf  = malloc((size_t)BUF_SIZE);   // allocate a buffer to store read data
	size_t bytes_read;

	// reads up to BUF_SIZE bytes from src_filename
	while ((bytes_read = read (src_fd, buf, BUF_SIZE)) > 0) {
	   write(dst_fd, buf, bytes_read);
	}

	// closes src_fd file descriptor
	close(src_fd);

	// closes dst_fd file descriptor
	close(dst_fd);
	
	// frees memory used for buf
	free(buf);
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
	syscall_copy(argv[1], argv[2]);	
	
	//call the check copy times function
	end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("%f sec \n", cpu_time_used);
	return 0;
}
