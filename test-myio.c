#include "myio.h"

int main(int argc, char *argv[]){
  void *bufferToReadTo = malloc(10000);
  void *bufferToReadTo2 = malloc(10000);
  FileStruct *fileToTest3 = myopen("test", O_CREAT | O_RDWR);
  FileStruct *fileToTest2 = myopen("sourceTest", O_CREAT | O_RDWR);
  int writeFile = open("test2", O_CREAT | O_RDWR, 0666);
  int fileToRead = open("sourceTest", O_RDONLY);


  myread(fileToTest2,bufferToReadTo2,3);
  read(fileToRead, bufferToReadTo, 3);
  myread(fileToTest2,(char *)bufferToReadTo2+3,12);
  read(fileToRead,(char *) bufferToReadTo+3, 12);
  //myread(fileToTest2,(char *)bufferToReadTo2 +8,13);
  //read(fileToRead, (char *)bufferToReadTo +8, 13);

  //printf("my string is %s \n",(char *) bufferToReadTo2);
  //printf("The Correctstring is %s \n", (char *)bufferToReadTo);
  //int compValue = memcmp(bufferToReadTo, bufferToReadTo2, 9000);
  ///printf("memcmp val is %d \n\n", compValue);

  printf("return val is %ld \n", mywrite(fileToTest3, bufferToReadTo, 8));
  write(writeFile, bufferToReadTo,8);
  mywrite(fileToTest3, bufferToReadTo, 8);
  mywrite(fileToTest3, bufferToReadTo, 8);
  write(writeFile, bufferToReadTo,8);
  write(writeFile, bufferToReadTo,8);

  myclose(fileToTest2);
  close(fileToRead);
  free(bufferToReadTo);
  free(bufferToReadTo2);


  return 0;


}
