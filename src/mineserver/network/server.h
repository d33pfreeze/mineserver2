/*
  Copyright (c) 2011, The Mineserver Project
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the The Mineserver Project nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef MINESERVER_NETWORK_SERVER_H
#define MINESERVER_NETWORK_SERVER_H

#include <string>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include <mineserver/game.h>
#include <mineserver/network/client.h>

namespace Mineserver
{
  /// server accepting clients
  class Network_Server : public boost::enable_shared_from_this<Mineserver::Network_Server>
  {
  private:
    Mineserver::Game::pointer_t m_game;
    Mineserver::Network_Protocol::pointer_t m_protocol;
    boost::asio::ip::tcp::acceptor m_socket;

  public:
    typedef boost::shared_ptr<Mineserver::Network_Server> pointer_t;

    /** creates a server object. Server will listen on port 25565.
     * \param game  game the server belongs to
     * \param protocol  protocol the server will communicate with
     * \param service  asio wrapper around listening socket
     */
    Network_Server(Mineserver::Game::pointer_t game, Mineserver::Network_Protocol::pointer_t protocol, boost::asio::io_service* service) : m_game(game),m_protocol(protocol),m_socket(*service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 25565))
    {
      startAccept();
    }

  private:
    void startAccept();
    void handleAccept(Mineserver::Network_Client::pointer_t client, const boost::system::error_code& error);
  };
}

#endif
