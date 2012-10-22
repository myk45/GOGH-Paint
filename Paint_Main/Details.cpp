#include<windows.h>
#include<gl/glut.h>
#include<string.h>

#define ON  1
#define OFF 2

int Right_Boxes;
char old_text[100];
int x_old1,y_old1,x_old2,y_old2;/*For Holding the vertices of the preevious box*/

void Draw_Info_Bar(int x1,int y1,int x2,int y2,int width,int mode)
{
	extern int theme;
	
	/*In this function, mode 1 is for the 3d effect and mode 2 is when its over the box*/
	if(mode == ON)
	{	
		
		if(Right_Boxes == 0){
			/*The white lines toward the left*/
			glColor3f(1.0,1.0,1.0);
			glLineWidth(3);
			glBegin(GL_LINES);
			  glVertex2i(x1, y1);
			  glVertex2i(x1, y2);
			glEnd();
		    glFlush();
			
			/*Line on the top of the icon*/

			glLineWidth(3);
			if(theme == 1){
				glColor3f(0.875,0.875,0.875);
			}

			else if(theme == 2)
				glColor3f(1.0,1.0,1.0);

			else
				glColor3f(0.3843,0.4078,0.5019);

			glBegin(GL_LINES);
			  glVertex2i(x1-1,y2+2);
			  glVertex2i(x2+1,y2+2);
		    glEnd();
		    glFlush();

			/*The dark gray line onto the right*/
			glColor3f(0.5215,0.5294,0.5490);
			glLineWidth(3);
			glBegin(GL_LINES);
			  glVertex2i(x2, y2);
			  glVertex2i(x2, y1);
			glEnd();
		    glFlush();
			glBegin(GL_LINES);
			  glVertex2i(x1,y1);
			  glVertex2i(x2,y1);
		    glEnd();
		    glFlush();
		}
		else{
			/*The white lines toward the left*/
			glColor3f(0.5215,0.5294,0.5490);
			//glColor3f(1.0,1.0,1.0);
			glLineWidth(3);
			glBegin(GL_LINES);
			  glVertex2i(x1, y1);
			  glVertex2i(x1, y2);
			glEnd();
		    glFlush();
			

			if(theme == 1)
				glColor3f(0.875,0.875,0.875);
			
			else if(theme == 2)
				glColor3f(1.0,1.0,1.0);

			else
				glColor3f(0.3843,0.4078,0.5019);
	
			glLineWidth(3);	
			glBegin(GL_LINES);
			  glVertex2i(x1-1,y2+2);
			  glVertex2i(x2+1,y2+2);
		    glEnd();
		    glFlush();

			/*The white line onto the right*/
			glColor3f(1.0,1.0,1.0);			
			glLineWidth(3);
			glBegin(GL_LINES);
			  glVertex2i(x2, y2);
			  glVertex2i(x2, y1);
			glEnd();
		    glFlush();

			glColor3f(0.5215,0.5294,0.5490);
			glBegin(GL_LINES);
			  glVertex2i(x1,y1);
			  glVertex2i(x2,y1);
		    glEnd();
		    glFlush();
		 }
	}

	else{
		/*This is when the box is selected ie the mouse cursor is over the box*/		
		
		glColor3f(0.0,0.0,1.0);	
		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
			glVertex2i(x1,y1-2);
			glVertex2i(x1,y2+1);
			glVertex2i(x2,y2+1);
			glVertex2i(x2,y1-2);
		glEnd();
		glFlush();
	}


}



void Text_Display(int x,int y,char text[])
{

	void *font =  GLUT_BITMAP_HELVETICA_18;

	/*Set the raster position*/
	glRasterPos2f(x-10,y);

	for(int i=0;i<(signed)strlen(text);i++){
		glutBitmapCharacter(font,text[i]);
	}
}

void Print_Details(SUB_MODE s)
{
	/*Array for printing details related to the mode*/
	char Details[100];
	extern int Cur_Text_Flag;
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//void *font =  GLUT_BITMAP_9_BY_15;
	//void *font =  GLUT_BITMAP_TIMES_ROMAN_24; 
	void *font_type = GLUT_BITMAP_HELVETICA_18;
	int x = 500;
	
	/*For clearing the old selected option ie 'de-highlighting' it*/ 
	glColor3f(0.875,0.875,0.875);
	Right_Boxes = 0;
	//Draw_Info_Bar(x_old1,y_old1,x_old2,y_old2,3,ON);			

	//glColor3f(0.0,0.0,0.0);
	//Draw_Info_Bar(s.vertices[0][0],s.vertices[0][1],s.vertices[1][0],s.vertices[1][1],2,OFF);

	x_old1 = s.vertices[0][0];
	y_old1 = s.vertices[0][1];
	x_old2 = s.vertices[1][0];
	y_old2 = s.vertices[1][1];

	if(s.mode == Cur_Text_Flag)
		return;

    Cur_Text_Flag = s.mode;
	switch(s.mode)
	{
	  case 1:strcpy(Details,"Click and drag the mouse to draw a Line");
			 break;
	  case 2:strcpy(Details,"Click and drag the mouse to draw a Rectangle");
			 break;
	  case 3:strcpy(Details,"Click on two places to draw a Circle");
			 break;
	  case 4:strcpy(Details,"Click and drag the mouse for Free Draw");
			 break;
	  case 5:strcpy(Details,"Click to draw lines.Create a polygon with Middle click");
			 break;
	  case 6:strcpy(Details,"Click and drag the mouse for Erasor");
			 break;
	  case 7:strcpy(Details,"Click and drag the mouse for Spray");
			 break;
	  case 8:strcpy(Details,"Click inside the drawing area and type in your Text");
			 break;
	  case 9:strcpy(Details,"Click on two places for creating Spiral");
		 	 break;
	  case 10:strcpy(Details,"Click and drag for getting Bubbles");
			  break;	
	  case 11:strcpy(Details,"Click inside the drawing for templates");
			 break;
	  case 12:strcpy(Details,"Pick a color from the drawing area");
			 break;  
	  case 13:strcpy(Details,"Draw a shape and press 'R' to rotate the shape");
			 break;
	  case 14:strcpy(Details,"Draw a shape and press 'E' to scale the shape");
			 break;
	  case 15:strcpy(Details,"Click and drag to mix colors");
		 	 break;
	  case 16:strcpy(Details,"Click on two places,copy image and pres 'J' to paste image");
			  break;	
	  case 17:strcpy(Details,"Click inside the drawing area to rotate image");
			 break;
	  case 18:strcpy(Details,"Click to get Points");
			 break;  
	  case 19:strcpy(Details,"Click on two places to get colored rectangles");
			 break;
	  case 20:strcpy(Details,"Click on two places to get an elllipse");
			 break;	
	}
	

	/*Draw the small area where the help info is displayed*/
	{
		extern int Win_Width;
		float colorRed   = 0.4588;
		float colorGreen = 0.6190;
		float colorBlue  = 0.8247;
		int x1 = 0, y1 = 0, x2 = Win_Width, y2 = 25;
		
		//glColor3f(0.3921,0.6313,0.9091);Initally used color -> a blue shade
		
		for(; y1 != y2 ;){
			glColor3f( colorRed += 0.02 ,  colorGreen += 0.02 , colorBlue += 0.02);
			glBegin(GL_LINES);
		  	 glVertex2i(x1,y1);
		   	glVertex2i(x2,y1++);
		  	 glEnd();
			glFlush();
			
		
		}
	}
	/*This above toolbar is generated as a mumber of lines woth different colors*/
	/*For drawing the box around the inormation display*/
	//Draw_Info_Bar(0,0,640,20,2,2);	
	glViewport(0,0,800,600);


	/*NO NEED FOR OLD TEXT.JUST DRAW THE BOX AGAIN*/
	/*For Overwriting with background color(clear) 
	glColor3f(0.7294,0.8,0.9137);
	Text_Display(200,0,old_text);
	glFlush();*/
	
	/*Try Opening a Flashy icon or button so that the user sees the help display*/
	glViewport(150,0,23,23);
	Open_Bitmap(".\\bit\\bulb.bmp");
	glViewport(0,0,800,600);
	
	glColor3f(0.0,0.0,1.0);
	Text_Display(200,5,Details);
	glFlush();
	
	strcpy(old_text,Details);
	
	

}	


void Draw_Highlighted_Boxes(int n,int size)
{
	int i;
	int x1 = 5,y1 = 132;
	int x2,y2;		

	for(i = 0 ; i < n; i++){
		x2 = x1 + size;
		y2 = y1 + size;
	
		/*Mode 1 for the 3d effect*/
		Draw_Info_Bar(x1,y1,x2,y2,3,1);

		y1 += size + 5;

		if(y1 >= 525){
			x1 = 760;
			y1 = 130;
			Right_Boxes = 1;
		}	
	}
	
}
