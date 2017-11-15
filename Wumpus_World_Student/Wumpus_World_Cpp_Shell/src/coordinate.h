#ifndef COORDINATE_H
#define COORDINATE_H
class coordinate
{
	public:
		unsigned int X, Y, hDistance;
		char direction;
		bool breeze, stench, visited, pit, wumpus;
		coordinate() : X(0), Y(0), direction('U'), breeze(false), stench(false), visited(false), hDistance(0), pit(false), wumpus(false) {}
		coordinate(unsigned int x, unsigned int y, char dir, bool b, bool s, bool v)
			: X(x), Y(y), direction(dir), breeze(b), stench(s), visited(v), hDistance(x+y), pit(false), wumpus(false) {}
		coordinate(const coordinate& c)
		{
			if(this != &c) {
				this->X = c.X;
				this->Y = c.Y;
				direction = c.direction;
				this->breeze = c.breeze;
				this->stench = c.stench;
				this->visited = c.visited;
				this->pit = c.pit;
				this->wumpus = c.wumpus;
				this->hDistance = c.hDistance;
			}
		}
		coordinate& operator= (const coordinate& c)
		{
			if(this != &c) {
				this->X = c.X;
				this->Y = c.Y;
				direction = c.direction;
				this->breeze = c.breeze;
				this->stench = c.stench;
				this->visited = c.visited;
				this->pit = c.pit;
				this->wumpus = c.wumpus;
				this->hDistance = c.hDistance;
			}
			return *this;
		}
		bool operator== (const coordinate& c) const
		{
			return (this->X == c.X && this->Y == c.Y);
		}
		bool operator!= (const coordinate& c) const
		{
			return !(this->X == c.X && this->Y == c.Y);
		}
		coordinate& operator+= (const coordinate& c)
		{
			this->X += c.X;
			this->Y += c.Y;
		}
		coordinate& operator-= (const coordinate& c)
		{
			if(this->X >= c.X && this->Y >= c.Y)
				this->X -= c.X, this->Y -= c.Y;
			return *this;
		}
		void printCoordinate()
		{
			std::cout << "(X, Y): (" << X << ", " << Y << ")  hDistance: " << hDistance << std::endl;
		}
};
#endif
