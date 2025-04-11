#include "types.h"
#include "user.h"

int
main(void)
{
  int p[2];
  char buf;

  if(pipe(p) < 0){
    fprintf(2, "pipe failed\n");
    exit(1);
  }

  if(fork() == 0){
    // Filho
    close(p[1]);
    read(p[0], &buf, 1);
    printf("%d: received ping\n", getpid());
    write(p[1], &buf, 1);
    exit(0);
  } else {
    // Pai
    close(p[0]);
    write(p[1], &buf, 1);
    close(p[1]);
    read(p[0], &buf, 1);
    printf("%d: received pong\n", getpid());
    exit(0);
  }
}
