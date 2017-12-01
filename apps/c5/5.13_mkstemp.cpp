#include "apue.h"
#include <errno.h>

void make_temp(char *template_);

int main(){
  char good_template[] = "/tmp/dirXXXXXX";
  char *bad_template = "/tmp/driXXXXXX";

  printf("trying to create first temp file...\n");
  make_temp(good_template);
  printf("trying to create second temp file...\n");
  make_temp(bad_template);
  return 0;
}

void make_temp(char *template_){
  int fd;
  struct stat sbuf;

  if((fd=mkstemp(template_))<0)
    err_sys("can't create temp file");
  printf("temp name = %s\n", template_);
  close(fd);
  if(stat(template_, &sbuf)<0){
    if(errno==ENOENT)
      printf("file doesn't exist\n");
    else
      err_sys("stat failed");
  }else{
    printf("file exists\n");
    unlink(template_);
  }
}
