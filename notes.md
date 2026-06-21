# Classes

- Game - controls and directs the game loop, holds all of the objects together
  - Timer - keeps track of the passage of time
  - Actor - can move around the map, has an inventory (Container), a location
    - ActorPlayer - has Parser behaviour and is controlled by the user
    - ActorNPC - controlled by the game
      - Parser - interprets commands from the ActorPlayer
  - Container - holds Objects
  - Map - holds the Rooms in a data structure and the behaviour for moving between rooms
    - Room - holds exits, objects (Container), Doors
      - Door - can exist in 2 rooms simultaneously. Can be locked or unlocked from either side, and can have a different description from either side.
  - Object
    - Prop
    - Treasure
    - Key
    - Device