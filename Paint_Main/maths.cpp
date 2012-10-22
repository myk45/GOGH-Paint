#include<windows.h>
#include<stdio.h>
#include<math.h>
#include<gl/glut.h>


void Open_Bitmap(char *);


char Slides[10][100] = {".\\Slides\\slide1.bmp",
						".\\Slides\\slide2.bmp",
						".\\Slides\\slide3.bmp",
						".\\Slides\\slide4.bmp",
						".\\Slides\\slide5.bmp",
						".\\Slides\\slide6.bmp",
						".\\Slides\\slide7.bmp",
						".\\Slides\\slide8.bmp",
						".\\Slides\\slide9.bmp",
						".\\Slides\\slide10.bmp",};

#define K (3.14/180)

int num,
	Win_Code1,
	first = 1;

extern int BITMAP_MODE,Window_Done;



void Show_Curve();

void Plot_Log()
{
	glColor3f(1.0,0.0,0.0);
	glLineWidth(3);
	float num1 = 0;
	glBegin(GL_LINE_STRIP);
	for(num = 1 ; num < 500 ; num += 2)
			glVertex2f(num1+=0.007 , log((double)num));
	glEnd();
	glFlush();
}


void Plot_Sine()

{
	
	float num1 = 0;

	glColor3f(1.0,0.0,0.0);

	glPointSize(2);
	
	glBegin(GL_LINE_STRIP);
	for(num = 0 ; num < 360 ; num += 2){
				
			glVertex2f(num1+=0.007 , sin(num*K));
			
			
	}		
	glEnd();
	glFlush();
	
}


void Plot_Cosine()
{
	glLineWidth(3);
	float num1 = 0;
	glBegin(GL_LINE_STRIP);
	for(num = 0 ; num < 360 ; num += 2)
			glVertex2f(num1+=0.007 , cos(num*K));
	glEnd();
	glFlush();
}


void Plot_Tan()
{
	glLineWidth(3);
	float num1 = 0;
	glBegin(GL_LINE_STRIP);
	for(num = 0 ; num < 360 ; num += 2)
			glVertex2f(num1+=0.007 , tan(num*K));
	glEnd();
	glFlush();
}

void SlideShow()
{
	int i;
	
	

	for(i=0 ; i < 10; i++){
		glViewport(0 , 0 , 700 , 700);
		Open_Bitmap(Slides[i]);
		Sleep(2500);
	}

}
	


void disp()
{	
	if( first == 1 )
	{
		glClearColor(0.0,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,2,-1,1);

		switch(BITMAP_MODE)
		{
			case 1:Plot_Log();	
				 break;
			case 2:Plot_Sine();
			 break;
			case 3:Plot_Cosine();
				  break;
			case 4:Plot_Tan();			  
				  break;
			case 5:SlideShow();
				   break;	
		}
		first = 0;
	}
}



void Curve_Mouse(int b,int s,int x,int y)
{
	if( b == GLUT_LEFT_BUTTON && s == GLUT_DOWN )
	{
		glutDestroyWindow(Win_Code1);
		BITMAP_MODE = 0;
		first 	    = 1;
		Window_Done = 1;
	}	
}	

void Create_Curve_Window()
{
	 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutInitWindowPosition(0,0);
	 glutInitWindowSize(700,700);
     	
	 Win_Code1 = glutCreateWindow("CURVE");     
     glutDisplayFunc(disp);	
	 glutMouseFunc(Curve_Mouse);
     glutMainLoop();	
	

}