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

class Client
{
    public:

        // creation d'un client a chaque nouvelle connexion
        //Client();
        Client(int fd);
        Client(Client const & cpy);
        //~Client();

        int getClientFd(void);

    private:

        // Ne doit pas etre instancie oar copie ou assignation
        Client();
        //Client(Client const & cpy);
        Client &    operator=(Client const & rhs);

        int _clientfd;

};

#endif