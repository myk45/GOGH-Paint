#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<windows.h>
#include<gl/glut.h>

#define C (3.14/180)

int obj;/*Specifies if it is dog or man 1=>man 2=> dog*/

int dir;/*Specifies the direction of movement of the object*/
 

int vpx=50,vpy=50,W=50,V=1,COUNT,MOVES[100],dircn,obj_mode;




void Draw_Rect(int x1,int y1,int x2,int y2)
{

	glBegin(GL_LINE_LOOP);   
	  glVertex2i(x1,y1);	   
	  glVertex2i(x1,y2);     
      	  glVertex2i(x2,y2);    
	  glVertex2i(x2,y1);    
	glEnd();
	glFlush();
}

void Draw_Lines(int x1,int y1,int x2,int y2)
{
	glLineWidth(5);	

	glBegin(GL_LINES);   
	  glVertex2i(x1,y1);	   
	  glVertex2i(x2,y2);     
    	glEnd();
	glFlush();

}

void Draw_Circle(int centreX,int centreY,int rad)
{
	float x,y,t;

	glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
	{
		t = i*C;
		x = rad*sin(t);
		y = rad*cos(t);
		glVertex2i(x+centreX,y+centreY);
	}
	glEnd();
	glFlush();
}

void Draw_Dog()
{
	
	if(V == 1)
	{	
		/*Body Part*/
		Draw_Rect(100,100,300,200);

		/*Face Part*/
		Draw_Circle(325,280,50);
		Draw_Circle(310,280,10);
		Draw_Circle(350,280,10);

		/*Neck Part*/
		Draw_Lines(300,200,320,230);

		/*Legs Part*/
		Draw_Lines(120,100,120,60);
		Draw_Lines(250,100,250,60);

		/*Tail Part*/
		Draw_Lines(100,150,80,100);

	 
     	V = 2;
					
	}
   else if(V == 2)
	{
	    /*Body Part*/
	 	Draw_Rect(100,100,300,200);

		/*Face Part*/
		Draw_Circle(320,280,50);
		Draw_Lines(305,280,310,280);
		Draw_Lines(340,280,360,280);
		
		/*Neck Part*/
		Draw_Lines(300,200,320,230);

		/*Legs Part*/
		Draw_Lines(120,100,100,60);
		Draw_Lines(120,100,140,60);
		Draw_Lines(250,100,230,60);
		Draw_Lines(250,100,270,60);

		/*Tail Part*/
		Draw_Lines(100,150,80,200);

		V = 1;
	}	
 	
}

void Draw_Man()
{


	 if(V == 1)
	 {
		/*Body Part */
		/*Head Finished*/	
		Draw_Circle(250,250,50);
		
		/*Line*/	
		Draw_Lines(250,200,250,100);

		/*Left Hand*/
		Draw_Lines(250,150,225,125);

		/*Right Hand*/
		Draw_Lines(250,150,275,125);
	
		/*Left Leg*/
		Draw_Lines(250,100,225,75);
	
		/*Right Leg*/
		Draw_Lines(250,100,275,75);


		/*Face Part*/
		Draw_Circle(220,275,10);
		Draw_Circle(280,275,10);
		Draw_Circle(250,225,10);
		
     	V = 2;
	}

	else if(V == 2)
	{
		/*Draw Head*/
		Draw_Circle(250,250,50);
		
		/*Line*/
		Draw_Lines(250,200,250,75);
		
		/*Face Part*/
		Draw_Circle(220,275,10);
		Draw_Circle(280,275,10);

		/*Legs Part*/
		Draw_Lines(245,225,255,225);

		V = 1;


	}

}






