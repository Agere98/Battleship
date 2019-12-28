#pragma once
#include <vector>

namespace BattleshipServer {

	/*
	An interface for a Battleship game board
	*/
	class Board {

	public:
		// Ship orientation
		enum Orientation { VERTICAL, HORIZONTAL };
		// Ship state
		enum ShipState { UNDEFINED, UNDAMAGED, DAMAGED, SUNK };

		// Returns a vector of ship sizes by index
		virtual std::vector<int> getShipSizes() = 0;
		// Gets the width of this board
		virtual int getWidth() = 0;
		// Gets the height of this board
		virtual int getHeight() = 0;
		// Tries to place a ship at specified position and orientation, returns true on success and false otherwise
		virtual bool placeShip(int x, int y, int shipIndex, Orientation shipOrientation) = 0;
		// Gets the index of a ship covering a specified position, returns -1 if no ship is there
		virtual int getShip(int x, int y) = 0;
		// Gets the current state of a ship
		virtual ShipState getShipState(int shipIndex) = 0;
		// Damages a ship with a specified index
		virtual int hit(int x, int y) = 0;
		// Sets all tiles on this board to empty
		virtual void clear() = 0;
		virtual ~Board() = default;
	};
}
