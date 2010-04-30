#ifndef LIB_SB_H
#define LIB_SB_H

enum NETWORK_TYPE {
    HTTP = 0,
    FTP
};

enum ERROR_TYPE {
    CONNECTION_LOST = 0
};

/*
 * All functions follow rules belowed, if not point out specially.
 * return value:
 * 0 : ok
 * <0: ERROR_TYPE 
 */

/*
 * construct a new network connection.
 * return value:
 * >0 : a fd that user can write data into it.
 */
int open_network(const char *url, int port, NETWORK_TYPE type);

/*
 * start to transfer a file.
 */ 
int send_start(int fd, const char *filename);

/*
 * finish to transfer a file.
 */
int send_end(int fd);

int send_data(int fd, const char *buf, long long size);

/*
 * close network connection.
 */
int close_network(int fd);
#endif
