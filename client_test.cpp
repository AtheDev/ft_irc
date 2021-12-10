#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#define BUF_SIZE 500

int
main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s/*, j*/;
    //size_t len;
    ssize_t nread/*, len_ret*/;
    char buf[BUF_SIZE];
    std::string buf2;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully connect(2).
       If socket(2) (or connect(2)) fails, we (close the socket
       and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */

        close(sfd);
    }

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);           /* No longer needed */

    /* Send remaining command-line arguments as separate
       datagrams, and read responses from server */
    while (1)
    {
        /*for (j = 3; j < argc; j++) {
            len = strlen(argv[j]) + 1;
                    // +1 for terminating null byte
            len_ret = (ssize_t)len;
            if (len + 1 > BUF_SIZE) {
                fprintf(stderr,
                        "Ignoring long message in argument %d\n", j);
                continue;
            }

            if (write(sfd, argv[j], len) != len_ret) {
                fprintf(stderr, "partial/failed write\n");
                exit(EXIT_FAILURE);
            }

            nread = read(sfd, buf, BUF_SIZE);
            if (nread == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            printf("Received %ld bytes: %s\n", (long) nread, buf);
        }*/
        std::getline(std::cin, buf2);
        if ((buf2.size() + 1) > BUF_SIZE)
        {
            std::cerr << "Error: message too long" << std::endl;
            continue ;
        }
        if (send(sfd, buf2.c_str(), buf2.size(), 0) != (ssize_t)buf2.size())
        {
            std::cerr << "Error: CLIENT send()" << std::endl;
            exit(EXIT_FAILURE);
        }
        if ((nread = recv(sfd, buf, BUF_SIZE, 0)) == -1)
        {
            std::cerr << "Error: CLIENT recv()" << std::endl;
            exit(EXIT_FAILURE);
        }
        printf("Received %ld bytes: %s\n", (long) nread, buf);
    }
    exit(EXIT_SUCCESS);
}