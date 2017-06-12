#include <GL/freeglut.h>
#include <vector>
#include "Triangle.cpp"

GLfloat posX = 100, posY = 100, posZ = 0;
GLfloat rotation = 0, deviation = 0;

void MyInit(void)
{
	glClearColor(0.9, 0.9, 0.9, 0.1);
	glViewport(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, posX * 2, 0, posY * 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display(void)
{
	GLfloat colors[6][4] = {
		{0,0,1,1}, // blue
		{0,1,0,1}, // green
		{1,0,0,1}, // red
		{1,0.5,0,1}, // orange
		{1,1,0,1},  // yellow
		{0.6,0,1,1} // purple
	};
	std::vector<std::vector<GLfloat>> triangles;
	GLfloat a = 10, a1 = 3, a2 = 90;
	auto trianglesRows = 3, trianglesCols = 3;
	auto translateConst = 4;

	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto i = 0; i < trianglesRows; i++)
	{
		for (auto j = 0; j < trianglesCols - i; j++)
		{
			triangles.push_back({ a * i, a * j, a });
		}
	}
	for (auto l = 0; l < translateConst; l++)
	{
		for (auto k = 0; k < triangles.size(); k++)
		{
			glPushMatrix();

			glTranslatef(posX, posY, posZ);

			glRotatef(rotation / a1 + (l * a2), 0, 0, 1);

			glTranslatef(deviation, deviation, posZ);
			glTranslatef(triangles.at(k)[0] + translateConst, triangles.at(k)[1] + translateConst, posZ);
			glRotatef(-rotation, 0, 0, 1);
			glTranslatef(-triangles.at(k)[0] - translateConst, -triangles.at(k)[1] - translateConst, posZ);

			Triangle(triangles.at(k), colors[k]).Draw();

			glPopMatrix();
		}
	}

	glutSwapBuffers();
	glFlush();
}

void Keyboard(unsigned char key, int x, int y)
{
	GLfloat move_unit = 10, rotate_unit = 0.1;

	switch (key)
	{
	case 'a':
		deviation += rotate_unit;
		rotation += move_unit;
		break;
	case 'd':
		deviation -= rotate_unit;
		rotation -= move_unit;
		break;
	case 'c':
		deviation = 0;
		rotation = 0;
		break;
	default: break;
	}

	glutPostRedisplay();
}

void SpecialInput(int key, int x, int y)
{
	unsigned char keyboard_key = NULL;
	switch (key)
	{
	case 100:
		keyboard_key = 'a';
		break;
	case 102:
		keyboard_key = 'd';
		break;
	default: break;
	}
	Keyboard(keyboard_key, x, y);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Trójkąty");

	MyInit();
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialInput);

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glutMainLoop();
	return 0;
}
