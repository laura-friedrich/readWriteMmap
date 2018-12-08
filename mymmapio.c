
#include "myio.h"

// Include our header file

/* Accepts Flags:
- O_CREAT
- O_WRONLY
- O_RDONLY
- O_RDWR
- O_TRUNC
*/

struct FileStruct* myflush(struct FileStruct *fd)  {

  return fd;
}

//mywrite implementations
ssize_t mywrite(struct FileStruct *fd, const void *buf, size_t count)  {
  printf("HEREE\n");
  struct stat sb;
  if (fstat(fd->fileDescriptor, &sb) < 0) {

    return -1;
  }
  if (sb.st_size<count) {
    //ONLY do this for now. Must truncate the file later to make biggeer.
    count = sb.st_size;

  }
  fd->fileData = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd->fileDescriptor,0);
  if (fd->fileData == MAP_FAILED) {

    return -2;
  }
  printf("%d is the file offset\n", fd->fileOffset);
  memcpy((char *)fd->fileData + fd->fileOffset, buf, count);
  fd->fileOffset = fd->fileOffset + count;
  if (munmap(fd->fileData, sb.st_size)<0) {

    return -3;
  }



return 0;
}

// myread implementations
ssize_t myread(struct FileStruct *fd, void *buf, size_t count)  {

  struct stat sb;
  if (fstat(fd->fileDescriptor, &sb) < 0) {
    return -1;
  }
  if (sb.st_size<count) {
    count = sb.st_size;
  }
  fd->fileData = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd->fileDescriptor,0);
  if (fd->fileData == MAP_FAILED) {
    return -2;
  }
  memcpy(buf, (char *)fd->fileData + fd->fileOffset, count);
  fd->fileOffset = fd->fileOffset + count;
  if (munmap(fd->fileData, sb.st_size)<0) {
    return -3;
  }
return count;
}


//implementation of myopen
struct FileStruct* myopen(char *fileName, int flags)  {

  struct FileStruct *fileStruct = malloc(sizeof(struct FileStruct));
  if (fileStruct == NULL){
    fileStruct->error = 1;
  }
  fileStruct->fileName = fileName;
  fileStruct->bytesWritten =0;
  fileStruct->flags = flags;
  fileStruct->fileDescriptor = open(fileName, flags, 0666);
  fileStruct->error = 0;
  fileStruct->fileOffset = 0;
  if (fileStruct->fileDescriptor == -1) {
    free(fileStruct);
    fileStruct->error = 1;
  }
    return fileStruct;
}


int myclose(struct FileStruct *fd)  {
  int returnVal = close(fd->fileDescriptor);
  if (returnVal == -1){
    fd->error = 4;
  }
  free(fd);
  return returnVal;
}
