
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

  struct stat sb;
  if ((fd->size_of_file - fd->fileOffset)<count) {
    if (fstat(fd->fileDescriptor, &sb) < 0) {
      return -1;
    }
    if (munmap(fd->fileData, sb.st_size)<0) {
      perror("munmap failed because");
      return -3;
    }
    if (ftruncate(fd->fileDescriptor, count+fd->fileOffset)<0){
      return -1;
    }
    if (fstat(fd->fileDescriptor, &sb) < 0) {
      return -1;
    }
    fd->size_of_file = sb.st_size;
    fd->fileData = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd->fileDescriptor,0);
    if (fd->fileData == MAP_FAILED) {
      return -2;
    }
  }
  memcpy((char *)fd->fileData + fd->fileOffset, buf, count);
  fd->fileOffset = fd->fileOffset + count;
return count;
}

// myread implementations
ssize_t myread(struct FileStruct *fd, void *buf, size_t count)  {

  if (fd->size_of_file - fd->fileOffset<count) {
    count = fd->size_of_file - fd->fileOffset;
  }
  memcpy(buf, (char *)fd->fileData + fd->fileOffset, count);
  fd->fileOffset = fd->fileOffset + count;
return count;
}

//implementation of myopen
struct FileStruct* myopen(char *fileName, int flags)  {

  struct FileStruct *fileStruct = malloc(sizeof(struct FileStruct));
  if (fileStruct == NULL){
    fileStruct->error = 1;
    return fileStruct;
  }
  fileStruct->fileName = fileName;
  fileStruct->bytesWritten =0;
  fileStruct->flags = flags;
  fileStruct->fileDescriptor = open(fileName, O_RDWR | O_CREAT, 0666);
  fileStruct->error = 0;
  fileStruct->fileOffset = 0;
  if (fileStruct->fileDescriptor == -1) {
    free(fileStruct);
    fileStruct->error = 1;
  }
  struct stat sb;
  if (fstat(fileStruct->fileDescriptor, &sb) < 0) {

    fileStruct->error = -1;
    return fileStruct;
  }
  if ((fileStruct->size_of_file = sb.st_size)==0){
    if (ftruncate(fileStruct->fileDescriptor, 1)<0){
      fileStruct->error = -4;
      return fileStruct;
    }
    if (fstat(fileStruct->fileDescriptor, &sb) < 0) {
      fileStruct->error = -5;
      return fileStruct;
    }
    fileStruct->size_of_file = sb.st_size;
  }
  fileStruct->fileData = mmap(NULL, fileStruct->size_of_file, PROT_READ | PROT_WRITE, MAP_SHARED, fileStruct->fileDescriptor,0);
  if (fileStruct->fileData == MAP_FAILED) {
    fileStruct->error = -3;
    return fileStruct;
  }
  return fileStruct;
}

int myclose(struct FileStruct *fd)  {
  if (munmap(fd->fileData, fd->size_of_file)<0) {
    return -3;
  }
  int returnVal = close(fd->fileDescriptor);
  if (returnVal == -1){
    fd->error = 4;
  }
  free(fd);
  return returnVal;
}
