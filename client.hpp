/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:38:26 by adupuy            #+#    #+#             */
/*   Updated: 2021/12/10 14:38:32 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <unistd.h>
#include <poll.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>

class Client
{
    public:

        Client(int fd);
        ~Client();

        int             getClientFd(void) const;
        void            setClientFd(int fd);

        void            setPollFdClient(void);
        struct pollfd   getPollFdClient(void) const;


    private:

        // Ne doit pas etre instancie par copie ou assignation ou par defaut
        Client();
        Client(Client const & cpy);
        Client &    operator=(Client const & rhs);
        
        int             _clientfd;
        struct pollfd   _pollFdClient;

};

#endif