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

#ifndef MINESERVER_POSITION_H
#define MINESERVER_POSITION_H

namespace Mineserver {

  /** general 3D position container
   * \tparam X x coordinates type
   * \tparam Y y coordinates type
   * \tparam Z z coordinates type
   */
  template<typename X, typename Y, typename Z>
  struct PositionEx
  {
    X x; ///< x coordinate
    Y y; ///< y coordinate
    Z z; ///< z coordinate

    /** initializing constructor. copies all 3 parameters to intern variables.
     * \param _x x coordinate
     * \param _y y coordinate
     * \param _z z coordinate
     */
    PositionEx(X _x, Y _y, Z _z) : x(_x),y(_y),z(_z) {}

    /// default constructor
    PositionEx() : x(0),y(0),z(0) {}

    /// copy constructor
    PositionEx(const PositionEx<X, Y, Z>& other) : x(other.x),y(other.y),z(other.z) {}

    /** compares two PositionExes
     * \param other second operand
     * \returns true, if all coordinates match, otherwise false
     */
    Mineserver::PositionEx<X, Y, Z>& operator=(const Mineserver::PositionEx<X, Y, Z>& other)
    {
      if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
      }

      return *this;
    }
  };

  /** 3D position container, where all coordinate types are the same.
   * \tparam T coordinate types
   */
  template<typename T>
  struct Position : public PositionEx<T, T, T> {
    Position(T _x, T _y, T _z) : PositionEx<T, T, T>(_x, _y, _z) {}
    Position() : PositionEx<T, T, T>() {}
    Position(const Position<T>& other) : PositionEx<T, T, T>(other) {}
  };
};

#endif
