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

#ifndef MINESERVER_WORLD_H
#define MINESERVER_WORLD_H

#include <utility>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <mineserver/position.h>

#include <mineserver/world/chunk.h>
#include <mineserver/world/generator.h>

namespace Mineserver
{
  typedef Position<double> WorldPosition;

  typedef PositionEx<int32_t, int16_t, int32_t> WorldBlockPosition;

  struct World
  {
  public:
    typedef boost::shared_ptr<Mineserver::World> pointer_t;
    typedef std::map<std::pair<uint32_t,uint32_t>, Mineserver::World_Chunk::pointer_t> chunkList_t;
    typedef std::vector<Mineserver::World_Generator::pointer_t> generatorList_t;

    // Jailout2000: Are enums okay to use here?
    // If these enums stay, plugins will need access to them. (TODO)
    enum GameMode
    {
      survival = 0, creative = 1
    };
    enum Dimension
    {
      nether = -1, overWorld = 0, theEnd = 1
    };
    enum Difficulty
    {
      peaceful = 0, easy = 1, normal = 2, hard = 3
    };

    static const GameMode defaultGameMode = survival;
    static const Dimension defaultDimension = overWorld;
    static const Difficulty defaultDifficulty = easy;
    static const uint8_t defaultWorldHeight = 127;

  private:
    chunkList_t m_chunks;
    generatorList_t m_generators;

    long m_worldSeed;
    GameMode m_gameMode;
    Dimension m_dimension;
    Difficulty m_difficulty;
    uint8_t m_worldHeight;
    Mineserver::WorldPosition m_spawnPosition;
    std::string m_levelType;

  public:
    World()
    {
      // TODO: Randomize the seed, or change all of these to their configured equivalents.
      //
      m_worldSeed = 1337;
      m_gameMode = defaultGameMode;
      m_dimension = defaultDimension;
      m_difficulty = defaultDifficulty;
      m_worldHeight = defaultWorldHeight;
      m_spawnPosition = Mineserver::WorldPosition(0,62,0);
      m_levelType = "DEFAULT";
    }

    bool hasChunk(uint32_t x, uint32_t z)
    {
      return m_chunks.find(std::make_pair(x,z)) != m_chunks.end();
    }

    Mineserver::World_Chunk::pointer_t getChunk(uint32_t x, uint32_t z)
    {
      return m_chunks[std::make_pair(x,z)];
    }

    void setChunk(uint32_t x, uint32_t z, Mineserver::World_Chunk::pointer_t chunk)
    {
      m_chunks[std::make_pair(x,z)] = chunk;
    }

    Mineserver::World_Chunk::pointer_t generateChunk(uint32_t x, uint32_t z)
    {
      if (!hasChunk(x, z)) {
        Mineserver::World_Chunk::pointer_t chunk = boost::make_shared<Mineserver::World_Chunk>();

        chunk->x = x;
        chunk->z = z;

        for (generatorList_t::const_iterator it = m_generators.begin(); it != m_generators.end(); ++it) {
          (*it)->processChunk(chunk);
        }

        setChunk(x, z, chunk);
      }

      return getChunk(x, z);
    }
    
    void addGenerator(Mineserver::World_Generator::pointer_t generator)
    {
      m_generators.push_back(generator);
    }

    long getWorldSeed() { return m_worldSeed; }
    void setWorldSeed(long worldSeed) { m_worldSeed = worldSeed; }
    
    std::string getLevelType() { return m_levelType; }
    void setLevelType(std::string levelType) { m_levelType = levelType; }

    bool getGameMode() { return m_gameMode; }
    void setGameMode(GameMode gameMode) { m_gameMode = gameMode; }

    int getDimension() { return m_dimension; }
    void setDimension(Dimension dimension) { m_dimension = dimension; }

    int getDifficulty() { return m_difficulty; }
    void setDifficulty(Difficulty difficulty) { m_difficulty = difficulty; }

    uint8_t getWorldHeight() { return m_worldHeight; }
    void setWorldHeight(uint8_t worldHeight) { m_worldHeight = worldHeight; }

    void setSpawnPosition(const Mineserver::WorldPosition& position) { m_spawnPosition = position; }
    const Mineserver::WorldPosition& getSpawnPosition() { return m_spawnPosition; }
  };
}

#endif
