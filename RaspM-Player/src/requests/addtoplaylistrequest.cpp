#include "addtoplaylistrequest.h"

AddToPlaylistRequest::AddToPlaylistRequest()
{

}

AddToPlaylistRequest::AddToPlaylistRequest(std::weak_ptr<Client> p_client, const std::string &p_url): client(p_client), url(p_url)
{

}

AddToPlaylistRequest::AddToPlaylistRequest(const AddToPlaylistRequest &other): client(other.client), url(other.url)
{

}
