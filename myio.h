// Import all necissary libraries for myio
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sys/mman.h>
#include <stdio.h>
#include <errno.h>
// Needed for open

#include <fcntl.h>
#include <sys/stat.h>
// Needed for close, read
#include <unistd.h>
#include <stdlib.h>
// Needed for memcpy
#include <string.h>

#ifndef __MYIO_H
#define __MYIO_H
#define BUFFER_SIZE 4

//struct stat sb;
typedef struct FileStruct{
    char *fileName;
    char fileBuffer[BUFFER_SIZE];
    int fileDescriptor;
    int flags;
    size_t size_of_file;
    int size_of_data;
    int bytesWritten;
    int error;
    void *fileData;
    int fileOffset;
    int fileWrittenTo;
    //void *pointer_to_sb;
    //struct stat sb;


}FileStruct;

struct FileStruct* myopen(char *pathname, int flags);

int myclose(struct FileStruct *fd);

struct FileStruct* myflush(struct FileStruct *fd);

ssize_t myread(struct FileStruct *fd, void *buf, size_t count);

ssize_t mywrite(struct FileStruct *fd, const void *buf, size_t count);

#endif
