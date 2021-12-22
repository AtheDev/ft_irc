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
#include "client.hpp"


#define BACKLOG 10

class Client;

class   Server
{
    public:

        //Server();
        Server(std::string port, std::string password);
        //Server(Server const & cpy) {}
        //Server &    operator=(Server const & rhs){}
        ~Server();

        void    run(void);

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

    private:

        struct addrinfo             _hints;
        struct addrinfo *           _result;
        
        int                         _socketfd;
        struct pollfd               _pollfdServer;

        std::string                 _port;
        std::string                 _password;

        std::vector<Client>         _arrayClient;
        int                         _nbClient;

        std::vector<struct pollfd>  _arrayPollFd;
        int                         _nbPollFd;
        
        socklen_t                   _sizeSockAddrIn;
        
};

#endif