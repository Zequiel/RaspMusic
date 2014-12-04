#ifndef ADDTOPLAYLISTREQUEST_H
#define ADDTOPLAYLISTREQUEST_H
#include <memory>
#include <QObject>

class Client;
struct AddToPlaylistRequest
{
    AddToPlaylistRequest();
    AddToPlaylistRequest(std::weak_ptr<Client> client, const std::string &url);
    AddToPlaylistRequest(const AddToPlaylistRequest& other);
    const std::weak_ptr<Client> client;
    const std::string url;
};

#endif // ADDTOPLAYLISTREQUEST_H
