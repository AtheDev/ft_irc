/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:01:39 by adupuy            #+#    #+#             */
/*   Updated: 2021/12/10 16:01:42 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client(int fd): _clientfd(fd) {}

Client::Client(Client const & cpy): _clientfd(cpy._clientfd) {}

int     Client::getClientFd(void) { return _clientfd; }