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

#ifndef MINESERVER_GAME_PLAYER_H
#define MINESERVER_GAME_PLAYER_H

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <mineserver/position.h>

namespace Mineserver
{
  /** players physical proprties wihtin their world.
   * In detail: Position, stance, pitch, yaw and onGround info for a player.
   */
  struct Game_PlayerPosition : public Position<double>
  {
    double stance; ///< bounding box modifier
    float pitch; ///< absolute rotation on the Y axis (left-right)
    float yaw; ///< absolute rotation on the X axis (up-down)
    bool onGround; ///< is player on ground?

    /// copy constructor
    Game_PlayerPosition(double _x, double _y, double _z, double _stance, float _pitch, float _yaw, bool _onGround) : Position<double>(_x, _y, _z),stance(_stance),pitch(_pitch),yaw(_yaw),onGround(_onGround) {}
    /// simpler constructor. sets omitted propertios to 0
    Game_PlayerPosition(double _x, double _y, double _z) : Position<double>(_x, _y, _z),stance(0),pitch(0),yaw(0),onGround(0) {}
    /// default constructor. seto all properties to 0
    Game_PlayerPosition() : Position<double>(),stance(0),pitch(0),yaw(0),onGround(0) {}

    /** copy given Game_PlayerPosition to this struct.
     * \param other  struct to copy
     * \returns  this struct
     */
    Mineserver::Game_PlayerPosition& operator= (const Mineserver::Game_PlayerPosition& other)
    {
      if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        stance = other.stance;
        pitch = other.pitch;
        yaw = other.yaw;
        onGround = other.onGround;
      }

      return *this;
    }
  };

  /// an ingame Player
  class Game_Player : public boost::enable_shared_from_this<Mineserver::Game_Player>
  {
  public:
    typedef boost::shared_ptr<Mineserver::Game_Player> pointer_t;

  private:
    std::string m_name;
    int32_t m_eid;
    Mineserver::Game_PlayerPosition m_position;

  public:
    /// getter for name property
    const std::string& getName() { return m_name; }
    /// setter for name property
    void setName(const std::string& name) { m_name.assign(name); }
    /// getter for entity ID
    int32_t getEid() { return m_eid; }
    /// setter for entity ID
    void setEid(int32_t eid) { m_eid = eid; }
    /// getter for position property
    Mineserver::Game_PlayerPosition& getPosition() { return m_position; }
    /// setter for position property
    void setPosition(Mineserver::Game_PlayerPosition pos) { m_position = pos; }

    /** executed one per tick for every player. I guess.
     * \todo I'm not really sure, what exacty is meant to be done in this method.
     *       Someone should clarify this.
     */
    void run();

    /** executed, when the server is shut down. I guess.
     * \todo I'm not really sure, what exacty is meant to be done in this method.
     *       Someone should clarify this.
     */
    void shutdown();
  };
}

#endif
