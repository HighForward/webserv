#ifndef WEBSERV_SERVERMANAGER_HPP
#define WEBSERV_SERVERMANAGER_HPP

#include <iostream>
#include <exception>
#include "../config/Config.hpp"
#include "../client//Client.hpp"
#include "../queries/Response.hpp"
#include "Server.hpp"
#include <list>
#include <stack>
#include <map>

#include <pthread.h>

class ServerManager
{
    public:
        typedef std::list<Server*>::iterator it_t;

        ServerManager();
        ~ServerManager();
        ServerManager(const ServerManager &copy);
        ServerManager &operator=(const ServerManager &copy);

        int setup_sockets(Config &conf);
        int setup_fd();
        int run_servers(Utils::server_state_t serverState);
        void set_global_config(Config &conf);
        ServerConfig getBestServer(Client *client);

        void disconnectClient(Client *client);

        class SetupSocketError : public std::exception
        {
            public:
                virtual const char* what() const throw()
                {
                    return ("Error encountered while creating servers sockets");
                }
        };

        class AcceptClientError : public std::exception
        {
            public:
                virtual const char* what() const throw()
                {
                    return ("Error encountered while accepting clients connexion");
                }
        };

    private:

        fd_set read_pool;
        fd_set write_pool;
        fd_set read_backup;
        fd_set write_backup;

        Config configGeneral;

        std::list<int> fd_av;

        std::list<Server*> servers;
        std::list<Client*> clients;
};

#endif
