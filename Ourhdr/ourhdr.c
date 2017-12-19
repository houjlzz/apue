#include "ourhdr.h"
#include <errno.h>
#include <stdarg.h>
#include <string.h>

static void err_doit(int, const char*,va_list);

char *pname = NULL;

void
err_dump(const char *fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,fmt,ap);
	va_end(ap);
	abort();
	exit(1);
}
void    
err_msg(const char *fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(0,fmt,ap);
	va_end(ap);
	return;
}
void
err_quit(const char *fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(0,fmt,ap);
	va_end(ap);
	exit(1);
}
void
err_ret(const char *fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,fmt,ap);
	va_end(ap);
	return;
}
void
err_sys(const char *fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,fmt,ap);
	va_end(ap);
	exit(1);
}

static void
err_doit(int errnoflag, const char* fmt,va_list ap)
{
	int errno_save;
	char buf[MAXLINE];

	errno_save = errno;
	vsprintf(buf,fmt,ap);
	if(errnoflag)
		sprintf(buf+strlen(buf),": %s",strerror(errno_save));
	strcat(buf,"\n");
	fflush(stdout);
	fputs(buf,stderr);
	fflush(NULL);
	return;
}

ssize_t readn(int fd, void *ptr, size_t n){
    size_t    nleft;
    ssize_t   nread;

    nleft = n;
    while (nleft > 0){
        if((nread = read(fd, ptr, nleft)) < 0){
            if(nleft == n){
                return(-1);
            }
            else{
                break;
            }
        }else if(nread == 0){
            break;
        }

        nleft -= nread;
        ptr += nread;
    }
    return(n - nleft);
}
ssize_t writen(int fd, void *ptr, size_t n){
    size_t    nleft;
    ssize_t   nwritten;

    nleft = n;
    while (nleft > 0){
        if((nwritten = write(fd, ptr, nleft)) < 0){
            if(nleft == n){
                return(-1);
            }
            else{
                break;
            }
        }else if(nwritten == 0){
            break;
        }

        nleft -= nwritten;
        ptr += nwritten;
    }
    return(n - nleft);
}

int fd_pipe(int fd[2]){
    return(socketpair(AF_UNIX, SOCK_STREAM, 0, fd));
}

#define CONTROLLEN CMSG_LEN(sizeof(int))
 

int send_fd(int fd, int fd_to_send){
    struct cmsghdr *cmptr = NULL;
    
    struct iovec       iov[1];
    struct msghdr     msg;
    char              buf[2];
    
    iov[0].iov_base   = buf;
    iov[0].iov_len    = 2;
    msg.msg_iov       = iov;
    msg.msg_iovlen    = 1;
    msg.msg_name      = NULL;
    msg.msg_namelen   = 0;
    
    if(fd_to_send < 0){
        msg.msg_control    = NULL;
        msg.msg_controllen = 0;
        buf[1] = -fd_to_send;
        if()
        
    }
}
int send_err(int fd, int errcode, const char *msg){
    int      n;

    if((n = strlen(msg)) > 0){
        if(writen(fd, msg, n) != n){
            return(-1);
        }
    }
    
    if(errcode >= 0){
        errcode = -1;
    }
    
    if(send_fd(fd,errcode) < 0){
        return(-1);
    }
    return(0);
}
int recv_fd(int fd, ssize_t (*userfunc)(int, const void*, size_t)){

}
