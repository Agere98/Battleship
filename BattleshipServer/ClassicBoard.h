#pragma once
#include <Board.h>

namespace BattleshipServer {

	class ClassicBoard : public Board {

	private:
		int width;
		int height;

	protected:
		std::vector<std::vector<int>> board;
		std::vector<int> shipSizes;
		std::vector<int> shipHitpoints;

		virtual void createBoard();

	public:
		// Creates an empty board
		ClassicBoard(int width = 10, int height = 10);
		// Returns a vector of ship sizes by index
		virtual std::vector<int> getShipSizes() override;
		// Gets the width of this board
		virtual int getWidth() override;
		// Gets the height of this board
		virtual int getHeight() override;
		// Tries to place a ship at specified position and orientation, returns true on success and false otherwise
		virtual bool placeShip(int x, int y, int shipIndex, Orientation shipOrientation) override;
		// Gets the index of a ship covering a specified position, returns -1 if no ship is there
		virtual int getShip(int x, int y) override;
		// Gets the current state of a ship
		virtual ShipState getShipState(int shipIndex) override;
		// Damages a ship with a specified index
		virtual int hit(int x, int y) override;
		// Get total hitpoints of all ships on this board
		virtual int getHitpoints() override;
		// Sets all tiles on this board to empty
		virtual void clear() override;
	};
}
