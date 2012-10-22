#include<gl/glut.h>



void Draw_Arcs(int x,int y)
{

	extern int X,Y,Flag;
	
	if(Flag == 0)
	{
		X = x;
		Y = y;
		Flag  = 1;
	}

	else
	{			
		glBegin(GL_LINES);
		 glVertex2i(X,480-Y);
		 glVertex2i(x,480-y);
		glEnd();
		glFlush();
		X = x;
		Y = y;
	}

	
}
