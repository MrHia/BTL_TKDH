#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <windows.h>
#include <iostream>

using  namespace std;
GLfloat light_ambientO[]={1.0,0.5,0.0,1.0};
GLfloat light_diffuseO[]={1.0,0.5,0.0,1.0};
 
GLfloat light_ambientG[]={0.0,0.5,0.0,1.0};
GLfloat light_diffuseG[]={0.0,1.0,0.0,1.0};
static int day= 0;
GLfloat x1 = 0;
GLfloat y1 = 0;
GLfloat y2 =-11;
GLfloat x2 =0;
//sphere radius
GLdouble rsize = 1.0;
// Step size in x and y directions 

// (number of pixels to move each time)
GLfloat xstep = 0.1f;
GLfloat ystep = 0.1f;
// Keep track of windows changing width and height
GLfloat windowWidth;
GLfloat windowHeight;
GLfloat Heightratio;
GLfloat Widthratio,R;
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambientO);
 		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuseO);
		glColor3f(1.0,0.0,1.0);
//		glRotatef(0,0,0,1);	// bu?c2: xoay nó nghiêng 45 d? (ngu?c kim d?ng h?)
		glScalef(5,1,1);		// bu?c3: kéo dan h´nh l?p phuong ?y, t?o thành m?t ph?ng, có góc nghiêng 45
		glTranslatef(x2,y2,0);

//		glTranslatef(x2,-11,0);
		glutSolidCube(1.0);		// bu?c1: t?o 1 h´nh kh?i l?p phuong 
	glPopMatrix();
							//v? qu? bóng và s? chuy?n d?ng
	glPushMatrix();
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambientG);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuseG); 
		glColor3f(0.0,0.0,1.0);
		glTranslatef(x1,y1,0);										// bu?c2: dua qu? bóng lên d?nh m?t ph?ng nghiêng
//		glTranslatef( (GLfloat) day/40 , (GLfloat) day/40 , 0);		// bu?c3: t?o chuy?n d?ng, phép t?nh ti?n tru?c
		glRotatef (((GLfloat) day)*(-1), 0, 0, 1);					// -----  sau dó m?i th?c hi?n phép quay
		glutSolidSphere(rsize, 20, 15);									// bu?c1: t?o mô h´nh qu? bóng
		glPopMatrix();
	glutSwapBuffers();
}
void keyboard (unsigned char key, int x, int y)
{
	cout<<"x2 = "<<x2<<endl<<"y2 = "<<y2<<endl<<"R = "<<R<<endl;
	switch (key) {
		case 'd': // (>)
			if (x2<2.0*Widthratio)
			x2 = x2 +0.1;
			glutPostRedisplay();
			break;
		case 'a': // (>)
			if (x2>-2.0*Widthratio)
			x2 = x2 -0.1;
			glutPostRedisplay();
			break;
		case 'y': // (>)
			
//			glutTimerFunc(130,TimerFunction, 0);
			break;
		default:
			break;
	}

}
void TimerFunction(int value)
    {
        if(y1<=y2+2.0 && x1>=x2*5.55 && x1<=((x2+1)*5.55) )
			{
				ystep = -ystep;
				xstep = -xstep;
			}
		else{
			// Reverse direction when you reach left or right edge
	        if(x1 > (10*Widthratio) || x1 < -(10*Widthratio))
	                xstep = -xstep;


	        // Reverse direction when you reach top or bottom edge
	        if(y1 > (10*Heightratio))
	                ystep = -ystep;
		}
        
		
//		cout<<"x2 = "<<x2<<endl<<"y2 = "<<y2<<endl;
//		cout<<"x1 = "<<x1<<endl<<"y1 = "<<y1<<endl;
        // Check bounds.  This is incase the window is made
        // smaller and the rectangle is outside the new
//        // clipping volume
//        if(x1 > 10-rsize)
//                xstep = -xstep;
//
//
//        if(y1 > 10-rsize) 
//                xstep = -xstep;


        // Actually move the square
        x1 += xstep;
        y1 += ystep;
		cout<<"\nystep = "<<ystep;
		cout<<"\nxstep = "<<xstep;
		cout<<"\nx2 = "<<x2*5;
		cout<<"\nx22 = "<<(x2+1)*5;
		cout<<"\nx1 = "<<x1;
		cout<<"\ny1 = "<<y1;
		cout<<"\ny2 = "<<y2<<endl;
        // Redraw the scene with new coordinates
    	glutPostRedisplay();
    	if(y1>-10){
			glutTimerFunc(13,TimerFunction, 1);
		}
		else glutTimerFunc(10000000,TimerFunction, 1000000);
}
void reshape (int w, int h)
{
	windowHeight = h;
	windowWidth = w;
	Heightratio =windowHeight/400;
   	Widthratio =windowWidth/400;
	if(h == 0)
            h = 1;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
//	cout<<w<<endl<<h<<endl<<windowWidth<<endl<<windowHeight<<endl;
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
//	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);	
	glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);

	R = (GLfloat) w/(GLfloat) h;
	cout<<"R= "<<R<<endl;
//	 		cout<<"\nwidth : "<<windowWidth;
//	 		cout<<"\nHeight : "<<windowHeight;
//	 		cout<<"\n Width / Height = "<< windowWidth / windowHeight;
//	 		cout<<"\n  Height/Width  = "<<  windowHeight/windowWidth ;
//			cout<<"\nx = "<<x2;
//			
//			cout<<"\ny = "<<y2;
//		if (w <= h) 
//	                {
//	                windowHeight = 250.0f*h/w;
//	                windowWidth = 250.0f;
//	                }
//	    	else 
//	                {
//	                windowWidth = 250.0f*w/h;
//	                windowHeight = 250.0f;
//	                }
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0, 0, 20, 0.0, 0.0, 0.0, 0, 1, 0);  // nh´n ngang t? tr?c Z.
//	gluLookAt (0, -1, 20, 0.0, 0.0, 0.0, 0, 1, 0);
//	gluLookAt (0, 10, 10, 0.0, 0.0, 0.0, 0, 1, 0); // di?m nh´n khác: A(0,10,10), hu?ng d?u theo Oy, nh´n v? g?c t?a d?

}
//void ChangeSize(GLsizei w, GLsizei h)
//        {
//        // Prevent a divide by zero
//        if(h == 0)
//                h = 1;
//        // Set Viewport to window dimensions
//    	glViewport(0, 0, w, h);
//        // Reset coordinate system
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        // Keep the square square, this time, save calculated
//        // width and height for later use
//        if (w <= h) 
//                {
//                windowHeight = 250.0f*h/w;
//                windowWidth = 250.0f;
//                }
//    	else 
//                {
//                windowWidth = 250.0f*w/h;
//                windowHeight = 250.0f;
//                }
//        // Set the clipping volume
//        //glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);
//
//
//       	glMatrixMode(GL_MODELVIEW);
////        glLoadIdentity();
//        }
void init(void) 
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor (1.0, 1.0, 1.0, 0.0);
	 
	 
	 
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	// glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	// glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
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
	glutTimerFunc(33, TimerFunction,20);
	
//	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}


