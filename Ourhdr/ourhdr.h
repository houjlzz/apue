#ifndef __ourhdr_h
#define __ourhdr_h

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

#define STDIN_FILENO 0

#define STDOUT_FILENO 1

#define MAXLINE 4096

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

#define min(a,b) ((a) < (b) ? (a) : (b))

#define max(a,b) ((a) > (b) ? (a) : (b))


void    err_dump(const char *,...);
void    err_msg(const char *,...);
void    err_quit(const char *,...);
void    err_ret(const char *,...);
void    err_sys(const char *,...);

ssize_t readn(int, void*, size_t);
ssize_t writen(int, const void *, size_t);

int fd_pipe(int *);
int send_fd(int fd, int fd_to_send);
int send_err(int fd, int status, const char *errmsg);
int recv_fd(int fd, ssize_t (*userfunc)(int, const void*, size_t));


#endif
