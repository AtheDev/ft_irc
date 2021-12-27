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


/*
int     poll(struct pollfd *fds, nfds_t nfds, int timeout);

fds : tableau de struct pollfd
nfds : nombre d'element du tableau fds
timeout : definit le temps pendant lequel poll() doit attendre que le fd soit pret.
        -> Si negatif alors delai infini

Si aucun evenement attendu ni erreur ne s'est produit,
poll()boque jusqu'a ce que l'un des evenement se produise.

VALEUR RENVOYEE:
    Renvoie une valeur positive representant le nombre de struct ayant un champ revents non nul.
    C'est-a-dire le nombre de struct pour lesquels un evenement attendu ou erreur s'est produit.
    Si null : signifie qu'il y a depassement du timeout
    Si -1 : echec 

struct pollfd {
    int     fd;         fd pour un fichier ouvert :
                    si negatif  => events est ignore et revent renvoie 0.
    short   events;     On remplit avec les evenements que l'on souhaite attendre.
    short   revents;    Remplit par le noyau avec les evenements qui se sont effectivement produits,
                        d'un des types demandes par events.
}
POLLIN : il y a des donnees en attente de lecture
POLLUP : le correspondant a ferrme la connexion(uniquement en sortie)
*/


#include "client.hpp"

Client::Client(int fd): _clientfd(fd) {}

Client::~Client() {
    if (_clientfd != 0)
        close(_clientfd);
}

int     Client::getClientFd(void) const { return _clientfd; }

void    Client::setClientFd(int fd) { _clientfd = fd; }

void    Client::setPollFdClient(void) {

    _pollFdClient.fd = _clientfd;
    _pollFdClient.events = POLLIN | POLLHUP;
    _pollFdClient.revents = 0;
}

struct pollfd   Client::getPollFdClient(void) const {

    return _pollFdClient;
}