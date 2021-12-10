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

class   Server
{
    public:

        Server();
        //Server(/*parameters*/);
        //Server(Server const & cpy) {}
        //Server &    operator=(Server const & rhs){}
        ~Server();

    private:

        struct addrinfo     hints;
        
        int                 _socketfd;
        

};

#endif