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

#ifndef MINESERVER_NETWORK_PROTOCOL_H
#define MINESERVER_NETWORK_PROTOCOL_H

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <mineserver/byteorder.h>

namespace Mineserver
{
  class Network_Message;

  /// converts between Network_Message and actual byte arrays
  class Network_Protocol
  {
  public:
    typedef boost::shared_ptr<Mineserver::Network_Protocol> pointer_t;

    enum {
      STATE_GOOD,
      STATE_STOP,
      STATE_ERROR
    };

    /** resolve a recieved byte array into a Network_Message
     * \param bytes  byte array
     * \param message  network message
     * \returns one of the states STATE_GOOD, STATE_STOP or STATE_ERROR
     */
    virtual int parse(std::vector<uint8_t>& bytes, Mineserver::Network_Message** message) = 0;

    /** assemble a byte array from a Network_Message
     * \param bytes  byte array
     * \param message  netowork message
     * \returns one of the states STATE_GOOD, STATE_STOP or STATE_ERROR
     */
    virtual int compose(std::vector<uint8_t>& bytes, const Mineserver::Network_Message& message) = 0;
  };
}

#endif
