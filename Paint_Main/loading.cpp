#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<gl/glut.h>

void displ();

int win;	

void Load_Window()
{
		
  
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutInitWindowPosition(310,310);
     glutInitWindowSize(300, 100);
     	
     win = glutCreateWindow("LOADING");
     glutDisplayFunc(displ);	
    
     	  
  
    /***************COOOOOOOL!! from the forum*************************/
	//HWND hThisWnd = FindWindow( "GLUT", "LOADING" );
	//if( hThisWnd )
	//{
	//	LONG lStyle = GetWindowLong( hThisWnd, GWL_STYLE );
	//	SetWindowLong( hThisWnd, GWL_STYLE, lStyle & 
	//		(~(WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_SYSMENU ) ) );
	//}
    /******************Remove Close,Min option*************************/
 	
     glutMainLoop();	
	

}


void displ()
{
	
  extern int w;	
		
  glClearColor(0.75, 0.75, 0.75, 0.0);	
  glClear(GL_COLOR_BUFFER_BIT);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,100,0.0,100);  	
  
  glFlush();

  /*Draw the small area where the help info is displayed*/
	{
		float colorRed   = 0.4588;
		float colorGreen = 0.6190;
		float colorBlue  = 0.8247;
		int x1 = 0, y1 = 0, x2 = 100, y2 = 100;
		
		//glColor3f(0.3921,0.6313,0.9091);Initally used color -> a blue shade
		
		for(; y1 != y2 ;){
			glColor3f( colorRed += 0.02 ,  colorGreen += 0.02 , colorBlue += 0.02);
			glBegin(GL_LINES);
		  	 glVertex2i(x1,y1);
		   	 glVertex2i(x2,y1++);
		  	glEnd();
			glFlush();
			//Sleep(100);
		
		}
	}

	/* This segment prints the "load.." message 
	{
     	  void *font = GLUT_BITMAP_HELVETICA_18;
	  char Load_Info[100] = "LOADING..PLEASE WAIT :)";
	  int i;
	
	  glColor3f(0.3921,0.6313,0.9091);
	  glRasterPos2f(20,50);
	  for(i = 0; i < (signed)strlen(Load_Info); i++){
		  glutBitmapCharacter(font , Load_Info[i]);
		  glFlush();
	 
	  }
	  Sleep(100);	 
	}*/		  

	 
	glutSetWindow(w);
}


void Draw_Load_Box(int x)
{

	extern int Win_Width,Win_Height;


	glViewport(0.0,0.0,Win_Width,Win_Height);
	/*Draw the small area where the help info is displayed*/
	{
		float colorRed   = 0.4588;
		float colorGreen = 0.6190;
		float colorBlue  = 0.8247;
		int x1 = 250, y1 = 300, x2 = 550, y2 = 360;
		
		//glColor3f(0.3921,0.6313,0.9091);Initally used color -> a blue shade
		
		for(; y1 != y2 ;){
			glColor3f( colorRed += 0.009 ,  colorGreen += 0.009 , colorBlue += 0.009);
			glBegin(GL_LINES);
		  	 glVertex2i(x1,y1);
		   	 glVertex2i(x2,y1++);
		  	glEnd();
			glFlush();
			//Sleep(100);
		
		}
	}

	/* This segment prints the "load.." message */
	{
	  char Load_Info[100];	
		
	  if( x == 1)
		strcpy(Load_Info ,"LOADING..PLEASE WAIT");
	  else 
		strcpy(Load_Info , "         DONE!!");/*To centre it in the display*/

      void *font = GLUT_BITMAP_HELVETICA_18;
	  
	  int i;
	
	  glColor3f(0.3921,0.6313,0.9091);
	  glRasterPos2f(300,330);
	  for(i = 0; i < (signed)strlen(Load_Info); i++){
		  glutBitmapCharacter(font , Load_Info[i]);
		  glFlush();
	 
	  }
	  Sleep(400);	 
	}		
}


void Stop()
{
	 Window_Done = 1;
	 glutDestroyWindow(win);
}