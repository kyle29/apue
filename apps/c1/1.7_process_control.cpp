#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
  char    buf[MAXLINE];  /* apue.h에서 */
  pid_t   pid;
  int     status;

  printf("%% ");  /* 프롬프트를 출력(printf로 %를 출력하려면
                    %%라고 해야 함) */
  while(fgets(buf, MAXLINE, stdin) != NULL){
    if(buf[strlen(buf) - 1] == '\n')
       buf[strlen(buf) - 1] = 0;  /* 새 줄을 널로 대체 */

    if((pid = fork()) < 0) {
      err_sys("fork error");
    } else if(pid == 0) { /* 자식 */
      execlp(buf, buf, (char *)0);
      err_ret("couldn't execute: %s", buf);
      exit(127);
    }

    /* 부모 */
    if ((pid = waitpid(pid, &status, 0)) < 0)
      err_sys("waitpid error");
    printf("%% ");
  }
  exit(0);
}
