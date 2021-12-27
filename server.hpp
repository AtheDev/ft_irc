/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:49:38 by adupuy            #+#    #+#             */
/*   Updated: 2021/12/10 15:50:10 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <poll.h>
#include <signal.h>
#include <netdb.h>
#include "client.hpp"
#include "message.hpp"

#define BACKLOG 10
#define BUF_SIZE 500

class Client;
void	handler_signal(int num);

class   Server
{
    public:

        Server(std::string port, std::string password);
        ~Server();

        void    run(void);
        void    addClient(void);
        void    messageHandling(int fd);
        void    sendMessage(Message *msg);
        //void    sendMessage(char * buf, ssize_t nread);

        class ErrorGetAddrInfoException : public std::exception {
            public:
                virtual const char *    what() const throw();
        };

        class ErrorSocketException : public std::exception {
            public:
                virtual const char *    what() const throw();
        };

        class ErrorSetSockOptException : public std::exception {
            public:
                virtual const char *    what() const throw();
        };

        class ErrorBindException : public std::exception {
            public:
                virtual const char *    what() const throw();
        };

        class ErrorListenException : public std::exception {
            public:
                virtual const char *    what() const throw();
        };

        class ErrorSignalException : public std::exception {
            public:
                virtual const char *    what() const throw();
        };

        class ErrorPollException : public std::exception {
            public:
                virtual const char *    what() const throw();
        };

    private:

        std::string                 _serverName;

        struct addrinfo             _hints;
        struct addrinfo *           _result;
        
        int                         _socketfd;
        struct pollfd               _pollfdServer;

        std::string                 _port;
        std::string                 _password;

        std::vector<Client*>        _arrayClient;
        std::vector<struct pollfd>  _arrayPollFd;

        struct sockaddr_in          _sockAddr;
        socklen_t                   _sizeSockAddrIn;

        // Ne doit pas etre instancie par copie ou assignation ou par defaut
        Server();
        Server(Server const & cpy);
        Server &    operator=(Server const & rhs);

};

#endif

/*
    Chaque client se distingue des autres clients par un
surnom d'une longueur maximale de neuf (9) caractères.

    En plus du pseudonyme, tous les serveurs doivent avoir les
informations suivantes sur tous les clients :
    - le vrai nom de l'hôte sur lequel le client s'exécute
    - le nom d'utilisateur du client sur cet hôte
    - le serveur auquel le client est connecté
*/