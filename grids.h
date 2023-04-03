int IsOnGrid(int, int); // Check if ship is already on grid

int PlaceShip(int, int, int, int, int); // Place ship

void DrawGrid(int); // Print all values in ship grid

void DrawHitGrid(int); // Print all values in hit grid

void RandomPlace(int, int); // Place ship at random

void ClearGrid(int); // Reset entire grid

void RandomPlaceAll(int); // Place all ships at random

int IsInsideGrid(int, int);

int Hit(int, int, int); // Hit a space, 0=Miss 1=Hit

int HitRandom(int); // Hits a random, unhit space

int SmartHit(int);

int IsSunk(int, int); // Check if ship has been sunk

int AllSunk(int); // Returns 1 if all ships on grid are sunk