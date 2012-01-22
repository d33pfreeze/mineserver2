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

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <mineserver/position.h>

#include <mineserver/world/chunk.h>
#include <mineserver/world/generator.h>

namespace Mineserver
{
  typedef Position<double> WorldPosition;

  typedef PositionEx<int32_t, int16_t, int32_t> WorldBlockPosition;

  /// represents an ingame world
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

    static const GameMode defaultGameMode = survival; ///< default for game mode property
    static const Dimension defaultDimension = overWorld; ///< default for dimenion property
    static const Difficulty defaultDifficulty = easy; ///< default for difficulty property
    static const uint8_t defaultWorldHeight = 127; ///< default for height property

  private:
    chunkList_t m_chunks;
    generatorList_t m_generators;

    long m_worldSeed;
    GameMode m_gameMode;
    Dimension m_dimension;
    Difficulty m_difficulty;
    uint8_t m_worldHeight;
    Mineserver::WorldPosition m_spawnPosition;

  public:
    /// sets all properties to their default values
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
    }

    /** determines whether a given chunk exists
     * \param x  x coordinate of chunk
     * \param y  y coordinate of chunk
     * \returns  true, if given chunk exists, otherwise false
     * \see generateChunk
     */
    bool hasChunk(uint32_t x, uint32_t z)
    {
      return m_chunks.find(std::make_pair(x,z)) != m_chunks.end();
    }

    /** looks up World_Chunk::pointer_t object for given coordinates.
     * Consider using generateChunk(), it solves the following issue for you:
     * If the chunk does not exist, it will be created, but probably in an unusable state.
     * Always check the result of hasChunk().
     * \see generateChunk
     * \see hasChunk
     * \param x  x coordinate
     * \param y  y coordinate
     * \returns  found World_Chunk::pointer_t
     */
    Mineserver::World_Chunk::pointer_t getChunk(uint32_t x, uint32_t z)
    {
      return m_chunks[std::make_pair(x,z)];
    }

    /** sets chunk. does not set up chunk s internal x and z values.
     * \param x  x coordinate
     * \param z  z coordinato
     * \param chunk  shared pointer to chunk
     * \see generateChunk
     */
    void setChunk(uint32_t x, uint32_t z, Mineserver::World_Chunk::pointer_t chunk)
    {
      m_chunks[std::make_pair(x,z)] = chunk;
    }

    /** sets up usable World_Chunk objects. non-existent chunks will be generated correctly
     *  and returned. if there is a chunk already it is returned.
     * \param x  x coordinates of chunk
     * \param z  z coordinates of chunk
     * \returns  proper World_Chunk for chunk x/z
     */
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

    /** adds a world generato to generator list.
     * \param generator  generator to add
     */
    void addGenerator(Mineserver::World_Generator::pointer_t generator)
    {
      m_generators.push_back(generator);
    }

    /// getter for worlds seed
    long getWorldSeed() { return m_worldSeed; }
    /// setter for worlds seed
    void setWorldSeed(long worldSeed) { m_worldSeed = worldSeed; }

    /// getter for worlds game mode
    bool getGameMode() { return m_gameMode; }
    /// setter for worlds game mode
    void setGameMode(GameMode gameMode) { m_gameMode = gameMode; }

    /// getter for worlds dimension
    int getDimension() { return m_dimension; }
    /// setter for worlds dimension
    void setDimension(Dimension dimension) { m_dimension = dimension; }

    /// getter for worlds difficulty
    int getDifficulty() { return m_difficulty; }
    /// setter for worlds difficulty
    void setDifficulty(Difficulty difficulty) { m_difficulty = difficulty; }

    /// getter for worlds height
    uint8_t getWorldHeight() { return m_worldHeight; }
    /// setter for worlds height
    void setWorldHeight(uint8_t worldHeight) { m_worldHeight = worldHeight; }

    /// setter for worlds spawn point
    void setSpawnPosition(const Mineserver::WorldPosition& position) { m_spawnPosition = position; }
    /// getter for worlds spawn point
    const Mineserver::WorldPosition& getSpawnPosition() { return m_spawnPosition; }
  };
}

#endif
