#include <GL/freeglut.h>
#include <vector>
#include <memory>
#include "Texturable.cpp"
#include "Square.cpp"

class Cube: public Texturable
{
public:
	Cube::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat n, GLuint texure) : Texturable(texure)
	{
		squares = std::make_unique<std::vector<Square>>();
		GLfloat nMargin = 10;
		// back
		squares->push_back(Square(new GLfloat[4][3]{
			{x - n - nMargin,y - n,z - n},
			{x + n + nMargin,y - n,z - n},
			{x + n + nMargin,y + n,z - n},
			{x - n - nMargin,y + n,z - n}
		}));
		// front
		squares->push_back(Square(new GLfloat[4][3]{
			{x - n - nMargin,y - n,z + n},
			{x + n + nMargin,y - n,z + n},
			{x + n + nMargin,y + n,z + n},
			{x - n - nMargin,y + n,z + n}
		}));
		// left
		squares->push_back(Square(new GLfloat[4][3]{
			{x - n - nMargin,y - n,z - n},
			{x - n - nMargin,y + n,z - n},
			{x - n - nMargin,y + n,z + n},
			{x - n - nMargin,y - n,z + n}
		}));
		// right
		squares->push_back(Square(new GLfloat[4][3]{
			{x + n + nMargin,y - n,z - n},
			{x + n + nMargin,y + n,z - n},
			{x + n + nMargin,y + n,z + n},
			{x + n + nMargin,y - n,z + n}
		}));
		// bottom
		squares->push_back(Square(new GLfloat[4][3]{
			{x - n - nMargin,y - n,z - n},
			{x + n + nMargin,y - n,z - n},
			{x + n + nMargin,y - n,z + n},
			{x - n - nMargin,y - n,z + n}
		}));
		// top
		squares->push_back(Square(new GLfloat[4][3]{
			{x - n - nMargin,y + n,z + n},
			{x - n - nMargin,y + n,z - n},
			{x + n + nMargin,y + n,z - n},
			{x + n + nMargin,y + n,z + n}
		}));
	}

	void Cube::Draw() const
	{
		glPushMatrix();
		Texturable::Draw();
		for (auto square : *squares)
		{
			square.Draw();
		}
		glPopMatrix();
	}

	std::unique_ptr<std::vector<Square>> squares;
};
