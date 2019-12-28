#include "ClassicBoard.h"
#include <stdexcept>

namespace BattleshipServer {

	void ClassicBoard::createBoard() {
		board = std::vector<std::vector<int>>(
			getHeight(), std::vector<int>(
				getWidth(), -1
				)
			);
		shipSizes = std::vector<int>{ 5, 4, 3, 3, 2 };
		shipHitpoints = std::vector<int>(shipSizes.size(), -1);
	}

	ClassicBoard::ClassicBoard(int width, int height) {
		this->width = width;
		this->height = height;
		createBoard();
	}

	std::vector<int> ClassicBoard::getShipSizes() {
		return shipSizes;
	}

	int ClassicBoard::getWidth() {
		return width;
	}

	int ClassicBoard::getHeight() {
		return height;
	}

	bool ClassicBoard::placeShip(int x, int y, int shipIndex, Orientation shipOrientation) {
		if (x < 0 || x >= getWidth() || y < 0 || y >= getHeight()) {
			throw std::out_of_range("Position is out of range");
		}
		if (shipIndex < 0 || shipIndex >(int)shipSizes.size()) {
			throw std::out_of_range("Ship index is out of range");
		}
		if (getShipState(shipIndex) != ShipState::UNDEFINED) {
			return false;
		}
		int size = getShipSizes()[shipIndex];
		int posX = x, posY = y;
		int& l = (shipOrientation == Orientation::VERTICAL) ? posY : posX;
		// Check if required tiles are empty and within bounds
		for (int i = 0; i < size; i++) {
			if (posX >= getWidth() || posY >= getHeight() || getShip(posX, posY) != -1) {
				return false;
			}
			l++;
		}
		// Place the ship on board
		for (int i = 0; i < size; i++) {
			l--;
			board[posX][posY] = shipIndex;
		}
		shipHitpoints[shipIndex] = size;
		return true;
	}

	int ClassicBoard::getShip(int x, int y) {
		if (x < 0 || x >= getWidth() || y < 0 || y >= getHeight()) {
			throw std::out_of_range("Position is out of range");
		}
		return board[x][y];
	}

	Board::ShipState ClassicBoard::getShipState(int shipIndex) {
		if (shipIndex < 0 || shipIndex >(int)shipSizes.size()) {
			throw std::out_of_range("Ship index is out of range");
		}
		int s = shipSizes[shipIndex];
		switch (shipHitpoints[shipIndex]) {
		case -1:
			return ShipState::UNDEFINED;
		case 0:
			return ShipState::SUNK;
		default:
			if (shipHitpoints[shipIndex] == shipSizes[shipIndex]) {
				return ShipState::UNDAMAGED;
			}
			else {
				return ShipState::DAMAGED;
			}
		}
	}

	void ClassicBoard::hit(int shipIndex) {
		if (shipIndex < 0 || shipIndex >(int)shipSizes.size()) {
			throw std::out_of_range("Ship index is out of range");
		}
		if (shipHitpoints[shipIndex] > 0) {
			shipHitpoints[shipIndex]--;
		}
	}

	void ClassicBoard::clear() {
		createBoard();
	}
}
