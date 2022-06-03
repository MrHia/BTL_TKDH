#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using  namespace std;

GLfloat light_ambientO[]={1.0,0.5,0.0,1.0};
GLfloat light_diffuseO[]={1.0,0.5,0.0,1.0}; 
GLfloat light_ambientG[]={0.0,0.5,0.0,1.0};
GLfloat light_diffuseG[]={0.0,1.0,0.0,1.0};
int goc =0;
GLfloat x1 = 0.15*(rand() % (10 - 1 + 1) + 1);
GLfloat y1 = 0.15*(rand() % (10 - 1 + 1) + 1);
GLfloat xstep = 0.01f;
GLfloat ystep = 0.01f;
GLfloat xstepc = 0.01f;
GLfloat ystepc = 0.01f;
GLfloat limitleft = -1.5;
GLfloat limitright = 1.5;
GLfloat limitbuttom = -1.5;
GLfloat limittop = 1.5;
GLfloat x2 = 0;
GLfloat y2 = -1.5;
GLfloat halflength = 0.05;
void init(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
 	GLfloat mat_shininess[] = { 50.0 };
 	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
 	glClearColor (1.0, 1.0, 1.0, 1.0);
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	// glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	// glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	 glEnable(GL_LIGHTING);
	 glEnable(GL_LIGHT0);
	 glEnable(GL_DEPTH_TEST);
}
void display(void)
{
 	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	glPushMatrix();
	 	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambientO);
	 	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuseO);
	 	//glRotatef(goc,1,1,0);
		glTranslatef(x1,y1,0.0);
	 	glutSolidSphere (0.1,20,16);
	glPopMatrix();
	glPushMatrix();
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambientG);
 		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuseG);
		glColor3f(1.0,0.0,1.0);
		glScalef(5,1,1);
		glTranslatef(x2,y2,0);
		glutSolidCube(0.1);
	glPopMatrix();
	glutSwapBuffers();
	 glFlush ();
	}
	
void keyboard (unsigned char key, int x, int y)
{

	switch (key) {
		case 'd': // (>)
			if(x2<limitright/6){
				x2 = x2 +xstepc;
				glutPostRedisplay();
			}
			
			break;
		case 'a': // (>)
			if(x2>limitleft/6){
				x2 = x2 -xstepc;
				glutPostRedisplay();
			}
		default:
			break;
	}
	cout<< x2<<endl;

}
void TimerFunction(int value)
    {
    	if(x2<=0){
    		halflength = -0.05;
		}else halflength = 0.05;
        if(y1<=y2+0.1 && x1>=x2*6 && x1<=((x2-halflength)*6)||y1<=y2 &&  x1>=x2*6 && x1<=((x2-halflength)*6) )
			{
				ystep = -ystep;
			}
		else{
			// Reverse direction when you reach left or right edge
	        if(x1 > limitright-0.1 || x1 < limitleft+0.1)
	                xstep = -xstep;
	        // Reverse direction when you reach top or bottom edge
	        if(y1 > limittop -0.1)
	                ystep = -ystep;
		}
		x1 += xstep;
        y1 += ystep;
    	glutPostRedisplay();
//    	if(y1>-10){
//			
//		}
//		else glutTimerFunc(10000000,TimerFunction, 1000000);
		y2=limitbuttom+0.05;
		glutTimerFunc(10,TimerFunction, 0);
		cout<<x2*6<<endl<<(x2-halflength)*6<<endl;
}
	
void reshape (int w, int h){

	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	 if (w <= h){
	 	glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
		limitbuttom =  -1.5*(GLfloat)h/(GLfloat)w;
		limittop = 1.5*(GLfloat)h/(GLfloat)w;
	 }
	 else{
	 	glOrtho (-1.5*(GLfloat)w/(GLfloat)h,1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	 	limitleft = -1.5*(GLfloat)w/(GLfloat)h;
		limitright = 1.5*(GLfloat)w/(GLfloat)h;	
	 }
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char** argv)
	{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (400, 400);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(33, TimerFunction, 20);
	glutMainLoop();
	return 0;
}

