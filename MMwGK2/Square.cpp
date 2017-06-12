#include <GL/freeglut.h>
#include <vector>
#include "Point.cpp"

class Square
{
public:
	explicit Square::Square(GLfloat n[4][3])
	{
		points = std::vector<Point>();
		for (auto i = 0; i < 4; i++)
		{
			points.push_back(Point(n[i][0], n[i][1], n[i][2]));
		}
	}

	void Square::Draw() const
	{
		glTranslatef(translateX, translateY, translateZ);
		glRotatef(rotateX, 1.0, 0, 0);
		glRotatef(rotateY, 0, 1.0, 0);
		glRotatef(rotateZ, 0, 0, 1.0);

		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		points.at(0).Draw();
		glTexCoord2f(0.0, 1.0);
		points.at(1).Draw();
		glTexCoord2f(1.0, 1.0);
		points.at(2).Draw();
		glTexCoord2f(1.0, 0.0);
		points.at(3).Draw();

		glEnd();
	}

	GLfloat translateX = 0;
	GLfloat translateY = 0;
	GLfloat translateZ = 0;
	GLfloat rotateX = 0;
	GLfloat rotateY = 0;
	GLfloat rotateZ = 0;

	std::vector<Point> points;
};
