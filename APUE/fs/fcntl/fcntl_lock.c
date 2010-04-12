#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock    lock;

	lock.l_type = type;     /* F_RDLCK, F_WRLCK, F_UNLCK */
	lock.l_start = offset;  /* byte offset, relative to l_whence */
	lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
	lock.l_len = len;       /* #bytes (0 means to EOF) */

	return( fcntl(fd, cmd, &lock) );
}

#define read_lock(fd, offset, whence, len) \
		lock_reg(fd, F_SETLK, F_RDLCK, offset, whence, len)
#define write_lock(fd, offset, whence, len) \
		lock_reg(fd, F_SETLK, F_WRLCK, offset, whence, len)

#define err_sys(x) { perror(x); exit(1); }

int main(int argc, char *argv[])
{
    int fd, val;
    pid_t pid;
    char buf[5];
    struct stat statbuf;
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC )) < 0)
        err_sys("open error");

    if (write(fd, "hello world", 11) != 11)
        err_sys("write error");

    /* turn on set-group-ID and turn off group-execute */
    if (fstat(fd, &statbuf) < 0)
        err_sys("fstat error");

#if 0
    if (fchmod(fd, (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        err_sys("fchmod error");
#endif

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {   /* parent */
        /* write lock entire file */
        if (write_lock(fd, 0, SEEK_SET, 0) < 0)
            err_sys("write_lock error");
            sleep(20);      /* wait for child to set lock and read data */
            if (waitpid(pid, NULL, 0) < 0)
                err_sys("waitpid error");
    } else {            /* child */
        sleep(10);      /* wait for parent to set lock */
        if ((val = fcntl(fd, F_GETFL, 0)) < 0)
            err_sys("fcntl F_GETFL error");
            
        val |= O_NONBLOCK;           /* turn on O_NONBLOCK flag */
        if (fcntl(fd, F_SETFL, val) < 0)
            err_sys("fcntl F_SETFL error");

        /* first let's see what error we get if region is locked */
        if (read_lock(fd, 0, SEEK_SET, 0) != -1)    /* no wait */
            err_sys("child: read_lock succeeded");

        printf("read_lock of already-locked region returns %d: %s\n", errno, strerror(errno));

        /* now try to read the mandatory locked file */
        if (lseek(fd, 0, SEEK_SET) == -1)
            err_sys("lseek error");
        if (read(fd, buf, 5) < 0)
            printf("read failed (mandatory locking works)\n");
        else
            printf("read OK (no mandatory locking), buf = %5.5s\n", buf);
    }

    exit(0);
}
