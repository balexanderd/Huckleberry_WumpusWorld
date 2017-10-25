#ifndef COORDINATE_H
#define COORDINATE_H
class coordinate
{
	public:
		unsigned int X, Y;
		char direction;
		bool breeze, stench;
		coordinate(unsigned x, unsigned y, char dir, bool b, bool s) : X(x), Y(y), direction(dir), breeze(b), stench(s) {}
		coordinate& operator= (const coordinate& c)
		{
			if(this != &c) {
				this->X = c.X;
				this->Y = c.Y;
				direction = c.direction;
				this->breeze = c.breeze;
				this->stench = c.stench;
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
};
#endif
