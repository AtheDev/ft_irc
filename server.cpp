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

Server::Server(std::string port, std::string password): _serverName("The Best IRC"), _port(port), _password(password), _sizeSockAddrIn(sizeof(struct sockaddr_in)) {
    std::cout << "\033[0;34m" << "Server opened" << "\033[0m" << std::endl;

    memset(&_hints, 0, sizeof(struct addrinfo));
    _hints.ai_flags = AI_PASSIVE;
    _hints.ai_family = AF_UNSPEC;
    _hints.ai_socktype = SOCK_STREAM;
    _hints.ai_protocol = 0;

    if (getaddrinfo(0, _port.c_str(), &_hints, &_result) != 0)
        throw Server::ErrorGetAddrInfoException();

    if ((_socketfd = socket(_result->ai_family, _result->ai_socktype, _result->ai_protocol)) == -1) // obtention d'un descripteur de socket
        throw Server::ErrorSocketException();

    /*int yes = 1;
    if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) // delete option
        throw Server::ErrorSetSockOptException();
    */
    if (bind(_socketfd, _result->ai_addr, _result->ai_addrlen) == -1) // associe le sockfd a un port sur la machine local
        throw Server::ErrorBindException();

    if (listen(_socketfd, BACKLOG) == -1) // attend la connexion
        throw Server::ErrorListenException();
    
    _pollfdServer.fd = _socketfd;
    _pollfdServer.events = POLLIN;
    _pollfdServer.revents = 0;
    _arrayPollFd.push_back(_pollfdServer);
}

Server::~Server() {
    std::cout << std::endl << "\033[0;34m" << "Server closed" << "\033[0m" << std::endl;

    close(_socketfd);
    freeaddrinfo(_result);
}

void            Server::run(void) {

    int ret;

    while (1)
    {
	    signal(SIGINT, handler_signal);
	    signal(SIGQUIT, handler_signal);

        if ((ret = poll(&(*_arrayPollFd.begin()), _arrayPollFd.size(), -1) == -1))
            throw ErrorPollException();

        std::vector<struct pollfd>::iterator it = _arrayPollFd.begin();
        for (; it != _arrayPollFd.end(); it++)
        {
            if (it->revents == POLLIN && it->fd == _socketfd)
                addClient();
            else if (it->revents == POLLHUP && it->fd != _socketfd)
                std::cout << "DECONEXION DU CLIENT" << std::endl;
            else if (it->revents == POLLIN && it->fd != _socketfd)
            {
                std::cout << "*********** CLIENT ENVOIE UN MESSAGE ***************" << std::endl;
                messageHandling(it->fd);
                /*char buf[BUF_SIZE];
                ssize_t nread;
                memset(buf, 0, BUF_SIZE);
                nread = recv(it->fd, buf, BUF_SIZE, 0);*/
                //sendMessage(buf, nread);
            }                   
        }
        //REINITIALISER LES POLLFD
        _arrayPollFd.clear();
        _arrayPollFd.push_back(_pollfdServer);
        for (size_t j = 0; j < _arrayClient.size(); j++)
            _arrayPollFd.push_back(_arrayClient[j]->getPollFdClient());
    }
    for (size_t j = 0; j < _arrayClient.size(); j++)
        close(_arrayClient[j]->getClientFd());
}

void            Server::addClient(void) {

    int newFd;
    if ((newFd = accept(_socketfd, (struct sockaddr *)& _sockAddr, &_sizeSockAddrIn)) == -1)
    {
        std::cout << "\033[0;31m" << "Error accept()" << "\033[0m" << std::endl; 
    }
    else
    {
        std::cout << "\033[0;32m" << "Success accept() => New Client" << "\033[0m" << std::endl;
        Client * newClient = new Client(newFd);
        fcntl(newFd, F_SETFL, O_NONBLOCK);
        newClient->setPollFdClient();
        _arrayClient.push_back(newClient);
    }
}

void            Server::messageHandling(int fd) {

    Message * newMesage = new Message();
    ssize_t nread = recv(fd, newMesage->_buf, BUF_SIZE, 0);
    newMesage->setNread(nread);

    sendMessage(newMesage);
    delete newMesage;
}

void            Server::sendMessage(Message * msg) {

    std::vector<Client *>::iterator it = _arrayClient.begin();
    for (; it != _arrayClient.end(); it++)
        if (send((*it)->getClientFd(), msg->_buf, msg->getNread(), 0) != msg->getNread())
                std::cout << "Error sending response\n" << std::endl;
}

/*void            Server::sendMessage(char *buf, ssize_t nread) {

    std::vector<Client *>::iterator it = _arrayClient.begin();
    for (; it != _arrayClient.end(); it++)
        if (send((*it)->getClientFd(), buf, nread, 0) != nread)
                std::cout << "Error sending response\n" << std::endl;
}*/

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

const char *    Server::ErrorSignalException::what() const throw() {

    return ("Exception : signal stop server");
}

const char *    Server::ErrorPollException::what() const throw() {

    return ("Exception : error poll()");
}