#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstring> // pour void * memset(void *ptr, int value, size_t num);
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>
#include <vector>

#include "client.hpp"
#include "server.hpp"


#define PORT "6667"
#define BACKLOG 10
#define IP "127.0.0.1"

#define BUF_SIZE 500


int main(/*int ac, char **av*/)
{
    int                 sockfd, new_fd = -1, s;
    //struct sockaddr_in  my_addr;
    struct sockaddr_in  their_addr;

    //struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    socklen_t size;
    ssize_t nread;
    char buf[BUF_SIZE];

    struct addrinfo hints;
    struct addrinfo *result, *rp;

    int yes = 1;

    std::vector<Client> arrayClient;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;    /* Indique que getaddrinfo doit renvoyer les adresses de socket de n'importe quelle famille d'adresse (par exemple IPv4 ou IPv6) */
    hints.ai_socktype = SOCK_STREAM; /* Permet d'ouvrir une socket UDP +++ATTENTION+++ changer en SOCK_STREAM pour une socket TCP */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Indique que getaddrinfo peu renvoyer des adresses de n'importe quel type */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    if ((s = getaddrinfo(NULL, PORT, &hints, &result)) != 0)
    {
        std::cout << "Error getaddrinfo()" << std::endl;
        exit(EXIT_FAILURE);
    }
    rp = result;
    if ((sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1) // obtention d'un descripteur de socket
    {
        std::cout << "Error socket()" << std::endl;
        return (EXIT_FAILURE);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        std::cout << "Error setsockopt()" << std::endl;
        close(sockfd);
        return (EXIT_FAILURE);
    }
    if (bind(sockfd, rp->ai_addr, rp->ai_addrlen) == -1) // associe un le sockfd a un port sur la machine local
    {
        perror("bind");
        std::cout << "Error bind()" << std::endl;
        close(sockfd);
        return (EXIT_FAILURE);
    }
    freeaddrinfo(result);
    if (listen(sockfd, BACKLOG) == -1) // attend la connexion
    {
        std::cout << "Error listen()" << std::endl;
        close(sockfd);
        return (EXIT_FAILURE);
    }
    /*size = sizeof(struct sockaddr_in);
    if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &size)) == -1)
    // gere la connexion et cree un nouveau fd a utiliser sur cette connexion unique.
    // les appels a send() et recv() utiliseront le new_fd
    {
        std::cout << "Error accept()" << std::endl;
        close(sockfd);
        return (EXIT_FAILURE);
    }*/
    std::cout << "OK jusqu'ici !!" << std::endl;
    //send(new_fd, "COUCOU", 7, 0);
    // ATTENTION si on est en attente de plusieurs connexions bien garder le sockfd ouvert pour permettre d'autres connexions entrantes

    //fcntl(new_fd, F_SETFL, O_NONBLOCK);
    for (;;) {
        size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &size)) == -1)
        // gere la connexion et cree un nouveau fd a utiliser sur cette connexion unique.
        // les appels a send() et recv() utiliseront le new_fd
        {
            std::cout << "Error accept()" << std::endl;
            close(sockfd);
            return (EXIT_FAILURE);
        }
        arrayClient.push_back(Client(new_fd));
   // fcntl(new_fd, F_SETFL, O_NONBLOCK);
        peer_addr_len = sizeof(struct sockaddr_storage);
        nread = recv(new_fd, buf, BUF_SIZE, 0);
        if (nread == -1)
            continue;               
    //std::cout << "Message recu : " << buf << std::endl;
        //char host[NI_MAXHOST], service[NI_MAXSERV];

        /*s = getnameinfo((struct sockaddr *) &peer_addr,
                        peer_addr_len, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICSERV);
       if (s == 0)
            printf("Received %ld bytes from %s:%s\n",
                    (long) nread, host, service);
        else
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
*/
        if (send(new_fd, buf, nread, 0) != nread)
            fprintf(stderr, "Error sending response\n");
        
    //send(new_fd, "COUCOU", 7, 0);
    }

    close(sockfd);
    close(new_fd);
}