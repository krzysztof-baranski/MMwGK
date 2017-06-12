#include <GL/freeglut.h>
#include <iostream>
#include "Texturable.cpp"
#define PI 3.14159265358979323846

class Spring : public Texturable
{
public:
	explicit Spring::Spring(GLfloat x, GLfloat y, GLfloat z, GLuint texture) : Texturable(texture), w_move(0), x(x), y(y), z(z)
	{
		glEnable(GL_TEXTURE_2D);
		sphereObject = gluNewQuadric();
		gluQuadricDrawStyle(sphereObject, GLU_FILL);
		gluQuadricTexture(sphereObject, texture);
		gluQuadricNormals(sphereObject, GLU_SMOOTH);
	}

	void Spring::Draw(GLfloat move)
	{
		auto t = 0;
		auto sin_t = sin(t);
		auto cos_t = cos(t);
		auto move2 = move;

		if (move >= 0) {
			w_move = move / (100 * PI);
		} else {
			w_move = -1 * move / (100 * PI);
		}

		Texturable::Draw();

		glPushMatrix();
		glTranslatef(x, y, z);
		//glRotatef(90, 0, 1, 0);

		for (GLfloat t = 0; t < 10 * PI; t += precise)
		{
			// prosty pionowy odcinek na pocz�tku spr�yny
			if (t < PI)
			{
				glPushMatrix();
				glTranslatef(0, -t + move, 0);
				gluSphere(sphereObject, 1, 20, 10);
				glPopMatrix();
			}
			//

			auto sinT = sin(t);
			auto cosT = cos(t);

			glPushMatrix();
			glTranslatef(cosT * (3.f + cos_t), 0.6f * t + sin_t + move2, sinT * (3.f + cos_t));
			gluSphere(sphereObject, 1, 10, 10);
			glPopMatrix();

			glPushMatrix();
			// poziomy odcinek na pocz�tku spr�yny
			if (t < (1.3 * PI))
			{
				glTranslatef(t, 18.9f, 0);
				gluSphere(sphereObject, 1, 10, 10);
			}
			glPopMatrix();

			glPushMatrix();
			// prosty poziomy odcinek na koncu
			if (t < 1.2 * PI)
			{
				glTranslatef(t, move, 0);
				gluSphere(sphereObject, 1, 10, 10);
			}
			glPopMatrix();

			glPushMatrix();
			// rysuj prosty odcinek na ko�cu spr�yny
			if (t > (6 * PI) && t < (7 * PI))
			{
				glTranslatef(0, t, 0);
				gluSphere(sphereObject, 1, 10, 10);
			}
			glPopMatrix();

			if (move > 0)
				move2 -= w_move;
			else if (move < 0)
				move2 += w_move;
		};

		glPopMatrix();
	}

	const GLfloat precise = 0.1f;
	GLUquadric* sphereObject;
	GLfloat x;
	GLfloat y;
	GLfloat z;

	GLfloat w_move;
};
