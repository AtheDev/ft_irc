/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:01:20 by adupuy            #+#    #+#             */
/*   Updated: 2021/12/10 16:01:25 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server(std::string port, std::string password): _port(port), _password(password) {
    std::cout << "Server opened" << std::endl;
    std::cout << "port : " << _port << std::endl << "password : " << _password << std::endl;

    memset(&_hints, 0, sizeof(struct addrinfo));
    _hints.ai_flags = AI_PASSIVE;
    _hints.ai_family = AF_UNSPEC;
    _hints.ai_socktype = SOCK_STREAM;
    _hints.ai_protocol = 0;

    if (getaddrinfo(0, _port.c_str(), &_hints, &_result) != 0)
        throw Server::ErrorGetAddrInfoException();

    if ((_socketfd = socket(_result->ai_family, _result->ai_socktype, _result->ai_protocol)) == -1) // obtention d'un descripteur de socket
        throw Server::ErrorSocketException();

    int yes = 1;
    if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        throw Server::ErrorSetSockOptException();

    if (bind(_socketfd, _result->ai_addr, _result->ai_addrlen) == -1) // associe le sockfd a un port sur la machine local
        throw Server::ErrorBindException();

    if (listen(_socketfd, BACKLOG) == -1) // attend la connexion
        throw Server::ErrorListenException();
}

Server::~Server() {
    std::cout << "Server closed" << std::endl;
    close(_socketfd);
    freeaddrinfo(_result);
}

const char *    Server::ErrorGetAddrInfoException::what() const throw() {

    return ("Exception : error getaddrinfo()");
}

const char *    Server::ErrorSocketException::what() const throw() {

    return ("Exception : error socket()");
}

const char *    Server::ErrorSetSockOptException::what() const throw() {

    return ("Exception : error setsockopt()");
}

const char *    Server::ErrorBindException::what() const throw() {

    return ("Exception : error bind()");
}

const char *    Server::ErrorListenException::what() const throw() {

    return ("Exception : error listen()");
}