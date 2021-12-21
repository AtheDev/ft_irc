/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:30:48 by adupuy            #+#    #+#             */
/*   Updated: 2021/12/20 11:30:52 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "client.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "./ircserv <port> <password>" << std::endl;
        return 1;
    }
    try {

        Server server(static_cast<std::string>(av[1]), static_cast<std::string>(av[2]));
    }
    catch (Server::ErrorGetAddrInfoException & e) {
        std::cout << e.what() << std::endl;
    }
    catch (Server::ErrorSocketException & e) {
        std::cout << e.what() << std::endl;
    }
    catch (Server::ErrorSetSockOptException & e) {
        std::cout << e.what() << std::endl;
    }
    catch (Server::ErrorBindException & e) {
        std::cout << e.what() << std::endl;
    }
    catch (Server::ErrorListenException & e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}