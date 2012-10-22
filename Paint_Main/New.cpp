#include <string.h>
#include <GL/glut.h>
#include<stdio.h>
#include"File.cpp"


void Display(void)
{
  glClearColor(0.0,0.0,0.0,0.0);	
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(0.0,300,0.0,300);  	
  glFlush();
  
}

void Mous(int b,int s,int x,int y)
{
	if(b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
		File_Operations();	
}

int main(int argc,char **argv)
{
	
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("GLUT bitmap font example");
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glutDisplayFunc(Display);
  glutMouseFunc(Mous);
  glutMainLoop();	

  return 0;
}
