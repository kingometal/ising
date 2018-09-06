#include <GL/glut.h>

GLfloat gfPosX = 0.0;
GLfloat gfDeltaX = .0001;


void Draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
                glVertex3f(gfPosX, 0.25, 0.0);
                glVertex3f(1.0 - gfPosX, 0.75,0.0);
	glEnd();
	glFlush();

	// ---------
	// animation
	gfPosX += gfDeltaX;
        if (gfPosX >= 1.0 || gfPosX <= 0.0) {
                gfDeltaX = -gfDeltaX;
        }
        glutPostRedisplay();
	// ---------
	
	// 
	
	//  glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
	//  width, and height is the size of your buffer you want to copy.
	//  format is is the format (how color components ate stored) you want to store the data in the video memory. It depends on how you initialized you application, if you set it to GL_RGBA, then format is GL_RGBA.
	//  type is what kind of data you want openGL to read. GL_UNSIGNED_CHAR if your image contains unsigned byte values to represent red, green and blue (maybe alpha too) values float 0 to 255, or GL_FLOAT if it's floats from 0 to 1.
	//  *pixels is a pointer to where you store your data to be copied.
}

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("myWindow");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}
