#include "Client_TCP.hpp"


Client_TCP::Client_TCP()
{
    this->host = NULL;
    errno = 0;
}

Client_TCP::~Client_TCP()
{
}

Client_TCP::Client_TCP(const Client_TCP &copy)
{
    *this = copy;
}

Client_TCP &Client_TCP::operator=(const Client_TCP &copy)
{
    if (this != &copy)
    {

    }
    return (*this);
}
void Client_TCP::connectToServer(std::string &host_ip, int port)
{
    struct clientItem* item = new struct clientItem();
    this->clientList.push_back(item);
    item->socket = socket(AF_INET , SOCK_STREAM , 0);
    item->serv_h = gethostbyname(host_ip.c_str());

    if (item->serv_h == NULL)
    {
        std::cout << "gethostbyname error: " << strerror(errno) << std::endl;
        exit(0);
    }

    item->serv_addr.sin_addr.s_addr = inet_addr(host_ip.c_str());
    item->serv_addr.sin_family = AF_INET;
    item->serv_addr.sin_port = htons(port);

    if (connect(item->socket, (struct sockaddr*)&item->serv_addr, sizeof(item->serv_addr)) < 0)
    {
        std::cout << "connect error: " << strerror(errno) << std::endl;
        exit(0);
    }
    std::cout << "Connected to: " << inet_ntoa(item->serv_addr.sin_addr) << ":" << ntohs(item->serv_addr.sin_port) << std::endl;
}
void Client_TCP::sendHeader()
{
    std::queue<std::string> headers;
    std::string request;

    headers.push("POST /directory/youpi.bla HTTP/1.1\r\n");
    headers.push("Transfer-Encoding: chunked\r\n");
    headers.push("\r\n");

    while (!headers.empty())
    {
        request += headers.front();
        headers.pop();
    }

    send(this->clientList.begin().operator*()->socket, request.c_str(), request.size(), 0);
}

void Client_TCP::sendChunkedData()
{
    std::list<std::string> chunks;
    std::string chunk_str;


//    chunks.push_back("YO JE SUIS UN PREMIER CHUNK");
//    chunks.push_back("YO JE SUIS UN DEUXIEME CHUNK");
//    chunks.push_back("YO JE SUIS UNE PUTE");
//    chunks.push_back("YO JE SUIS UN HETEROEXUEL ASPIRANT HELICOPTERE D'ATTAQUE");
//    chunks.push_back("YO JE SUIS UN louis ^^");
//    chunks.push_back("YO JE SUIS UN tim ^^");
//    chunks.push_back("YO");

    size_t i = 8000;
    std::string chunk_tmp;

    while (i > 0)
    {
        chunk_tmp.append("X");
        i--;
    }

    for (i = 0; i < 100; i++)
        chunks.push_back(chunk_tmp);

    std::list<std::string>::iterator it = chunks.begin();
    while (it != chunks.end())
    {
        int size_chunck = (*it).size();

        std::stringstream convert;
        convert << std::hex << size_chunck;
        std::string size_hex = convert.str();

        chunk_str += (size_hex + "\r\n");
        chunk_str += ((*it) + "\r\n");
        it++;
        if (it == chunks.end())
            chunk_str += "0\r\n\r\n";
        usleep(100000);
//        chunk_str.clear();
    }
    send(this->clientList.begin().operator*()->socket, chunk_str.c_str(), chunk_str.size(), 0);

}


int main()
{
    Client_TCP client;
    std::string host_ip = "127.0.0.1";
    int port = 5000;
    int nb_client = 1;

    while (nb_client--)
    {
        client.connectToServer(host_ip, port);
        usleep(1);
    }

    client.sendHeader();
    client.sendChunkedData();

    sleep(20);

    char buffer[100000] = { 0 };
    int valread = read(client.clientList.begin().operator*()->socket , buffer, 100000);
    std::cout << "---------- RESPONSE ----------" << std::endl;
    buffer[valread] = '\0';
    std::cout << buffer << std::endl;
    std::cout << "------------ END. ------------" << std::endl;

    std::string input;
    std::cout << "Press anykey to close connexion\n";
    std::getline(std::cin, input);

}