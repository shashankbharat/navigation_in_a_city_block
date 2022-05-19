#include<GL/glut.h>
#include<GL/gl.h>
#include<string.h>
#include<iostream.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<windows.h>
#include "imageloader.h"

static GLdouble viewer[]= {5.0, 3.0, -6.0}; //Camera eye
static GLdouble focus[]= {5.0,3.0,-10.0}; //Camera focus
static GLint x=0,m=0,x1=0,t1=0,z1=0; // keyboard camera and axis function variables

//**********Convert bmp to pixels and return id*******

GLuint loadTexture(Image* image) 
{
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture




	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
	 0,                            //0 for now
	 GL_RGB,                       //Format OpenGL uses for image
	 image->width, image->height,  //Width and height
	 0,                            //The border of the image
	 GL_RGB,              //GL_RGB, because pixels are stored in RGB format
	GL_UNSIGNED_BYTE,     //GL_UNSIGNED_BYTE, because pixels are stored as unsigned numbers
	 image->pixels);               //The actual pixel data
	return textureId;           //Returns the id of the texture
}

//Texture id declarations
GLuint _textureId,_textureId2,_textureId3,_textureId4,_textureId5,_textureId6,_textureId14;
GLuint _textureId7,_textureId8,_textureId9,_textureId10,_textureId11,_textureId12,_textureId13;

//Road white strips
void strip()
{
 glColor3f(1,1,1);//STRIP COLOR
	for(int i=-2;i>-260;i--)
	{	
		i=i-10;
	 glBegin(GL_POLYGON);  //STRIP CODE ROAD 1
		glVertex3f(4.7,0.1,i);
	              glVertex3f(5.3,0.1,i);

		glVertex3f(5.3,0.1,i-4);
		glVertex3f(4.7,0.1,i-4);
	 glEnd();

	 glBegin(GL_POLYGON);//STRIP CODE ROAD 3
		glVertex3f(144.7,0.1,i);
	              glVertex3f(145.3,0.1,i);
		glVertex3f(145.3,0.1,i-4);
		glVertex3f(144.7,0.1,i-4);
	 glEnd();
	}

	for(i=5;i<135;i++)
	{	
		i=i+10;
	 glBegin(GL_POLYGON); //STRIP CODE ROAD 2
		glVertex3f(i,0.1,-295.3);
	              glVertex3f(i,0.1,-294.7);
		glVertex3f(i+4,0.1,-294.7);
		glVertex3f(i+4,0.1,-295.3);
	 glEnd();

	 glBegin(GL_POLYGON);//STRIP CODE ROAD 4
		glVertex3f(i,0.1,-5.3);
	              glVertex3f(i,0.1,-4.7);

		glVertex3f(i+4,0.1,-4.7);	
  	              glVertex3f(i+4,0.1,-5.3);
	 glEnd();
	}
}	
	

//Roads construction
void roads()
{
   glColor3f(0.4,0.4,0.4);//ROAD COLOR
    glBegin(GL_QUADS); //ROAD 1
	  glNormal3f(0,1,0);
	  glVertex3f(0,0,-300); 
	  glVertex3f(0,0,0);
	  glVertex3f(10,0,-10);
	  glVertex3f(10,0,-290);
      
	  glNormal3f(0,1,0);
	  glVertex3f(0,0,-300); //ROAD 2
	  glVertex3f(10,0,-290);
	  glVertex3f(140,0,-290);
                 glVertex3f(150,0,-300);
	  
	  

  glNormal3f(0,1,0);
     glVertex3f(140,0,-290);//ROAD 3 
     glVertex3f(150,0,-300);	 
     glVertex3f(150,0,0);
     glVertex3f(140,0,-10);
	  
              glNormal3f(0,1,0);
      glVertex3f(140,0,-10);//ROAD 4
      glVertex3f(150,0,0);
      glVertex3f(0,0,0);
      glVertex3f(10,0,-10);	  
    glEnd();
}

//Footpath translation and scaling matrices
static GLint fptx[] = {11,-1,139,151,75,75,75,75};
static GLint fptz[] = {-150,-150,-150,-150,-289,-301,-11,1};
static GLfloat fpsx[] = {1,1,1,1,65,75,65,75};
static GLfloat fpsz[] = {140,152,140,152,1,1,1,1};

//Footpath construction
void footpath()
{
  glColor3f(.2,.2,.2);


	for(int i=0;i<8;i++)
	{  
	   glPushMatrix();
       glTranslatef(fptx[i],0,fptz[i]);
       glScalef(fpsx[i],.3,fpsz[i]);
	   glNormal3f(0,1,1);
       glutSolidCube(2.0f);
       glPopMatrix();
	} 
}

//Lamp-post construction
void lposts()
{	  
 for(int i=-15;i>-300;i=i-30)
 {	
    glPushMatrix();//ROAD 3 RIGHT
	glColor3f(.4,.4,.4);
	glTranslatef(139,4,i);
	glScalef(.3,8,.3);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(139,8.25,i);
	glColor3f(.3,.3,0.5);

	glutWireCube(1.0f);
	glColor4f(0.6f, 0.6f, 0.6f, 0.2f);
	glutWireSphere(0.25,25,25);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0f);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutSolidCube(1.0f);
    glPopMatrix();
	glDisable(GL_BLEND);
   glPushMatrix();//ROAD 3 Left
	glColor3f(.4,.4,.4);
	glTranslatef(151,4,i+20);
	glScalef(.3,8,.3);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(151,8.25,i+20);
	glColor3f(.3,.3,0.5);
	glutWireCube(1.0f);
	glColor4f(0.6f, 0.6f, 0.6f, 0.2f);
	glutWireSphere(0.25,25,25);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0f);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 	glutSolidCube(1.0f);

    glPopMatrix();
	glDisable(GL_BLEND);  
 if(i!=-105)
	{ 
glPushMatrix();//ROAD 1 RIGHT
	glColor3f(.4,.4,.4);
	glTranslatef(11,4,i);
	glScalef(.3,8,.3);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(11,8.,i);
	glColor3f(.3,.3,0.5);
	glutWireCube(1.0f);
	glColor4f(0.6f, 0.6f, 0.6f, 0.2f);
	glutWireSphere(0.25,25,25);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0f);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 	glutSolidCube(1.0f);
    glPopMatrix();
	glDisable(GL_BLEND);
}
	


if(i!=-135&&i!=-105)
{
    glPushMatrix();//ROAD 1 LEFT
	glColor3f(.4,.4,.4);
	glTranslatef(-1,4,i+20);
	glScalef(.3,8,.3);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1,8.,i+20);
	glColor3f(.3,.3,0.5);
	glutWireCube(1.0f);
	glColor4f(0.6f, 0.6f, 0.6f, 0.2f);
	glutWireSphere(0.25,25,25);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0f);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutSolidCube(1.0f);
    glPopMatrix();
    glDisable(GL_BLEND);
    }	//END if   
}           //END FOR




 for(i=0;i<150;i=i+30)
 {
	glPushMatrix();
	glColor3f(.4,.4,.4);//ROAD 4 LEFT
	glTranslatef(i,4,1);
	glScalef(.3,8,.3);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(i,8.,1);
               glColor3f(.3,.3,0.5);
	glutWireCube(1.0f);
	glColor4f(0.6f, 0.6f, 0.6f, 0.2f);
	glutWireSphere(0.25,25,25);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0f);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 	
    glutSolidCube(1.0f);
    glPopMatrix();
    glDisable(GL_BLEND);	
 if(i!=0)
 { 
	glPushMatrix();
	glColor3f(.4,.4,.4);
	glTranslatef(i,4,-11);//ROAD 4 RIGHT

	glScalef(.3,8,.3);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(i,8.,-11);
	glColor3f(.3,.3,0.5);
	glutWireCube(1.0f);
	glColor4f(0.6f, 0.6f, 0.6f, 0.2f);
	glutWireSphere(0.25,25,25);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0f);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutSolidCube(1.0f);
    glPopMatrix();
    glDisable(GL_BLEND);
 }    
    glPushMatrix();
	glColor3f(.4,.4,.4);
	glTranslatef(i,4,-301);//ROAD 3 LEFT
	glScalef(.3,8,.3);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(i,8.,-301);
	glColor3f(.3,.3,0.5);

	glutWireCube(1.0f);
	glColor4f(0.6f, 0.6f, 0.6f, 0.2f);
	glutWireSphere(0.25,25,25);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0f);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutSolidCube(1.0f);
    glPopMatrix();
    glDisable(GL_BLEND);	
 if(i!=0)
 {
	glPushMatrix();
	glColor3f(.4,.4,.4);
	glTranslatef(i,4,-289);//ROAD 3 RIGHT
	glScalef(.3,8,.3);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(i,8.,-289);
	glColor3f(.3,.3,0.5);
	glutWireCube(1.0f);
	glColor4f(0.6f, 0.6f, 0.6f, 0.2f);
	glutWireSphere(0.25,25,25);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0f);


    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutSolidCube(1.0f);
    glPopMatrix();
    glDisable(GL_BLEND);
       }
   }
}  

//Navigation parameters initialization
static GLint u=0,an=0,r1=0,r2=0,r3=0,r4=0,d=0;
void display()
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
  glFrontFace(GL_CCW);
  glFlush();  
  glLoadIdentity();	
	//Left and right rotation
	   if(m==1)
	   { x+=5%(360);m=0;   }
	   if(m==2)
	   { x-=5%(360);m=0;  }
	   glRotatef(x,x1,t1,z1);


	//Up rotation
	if(u==1)
	{
 	    u=0;an+=3%(360);
	         if(r1==1)glRotatef(an,-1,0,0);
	         if(r2==1)glRotatef(an,0,0,-1);
	         if(r3==1)glRotatef(an,1,0,0);
	         if(r4==1)glRotatef(an,0,0,1);
	}	
	//Down rotation
	if(d==1)
{
       d=0;an-=3%(360);
	         if(r1==1)glRotatef(an,-1,0,0);
	         if(r2==1)glRotatef(an,0,0,-1);
	         if(r3==1)glRotatef(an,1,0,0);
	         if(r4==1)glRotatef(an,0,0,1);
	 }
	//Set camera
	gluLookAt(viewer[0],viewer[1],viewer[2], focus[0],focus[1],focus[2], 0.0, 1.0, 0.0);	
	//Tunnel Shadow
	glBegin(GL_QUADS);
	 glColor3f(0,0,0);
	 glVertex3f(0,0.01,-110);
	 glVertex3f(10,0.01,-110);

	 glColor3f(.4,.4,.4);
	 glVertex3f(10,0.01,-120);
	 glVertex3f(0,0.01,-120);     
	 glColor3f(0,0,0);
	 glVertex3f(0,0.01,-90);
	 glVertex3f(10,0.01,-90);	 
	 glVertex3f(10,0.01,-110);
	 glVertex3f(0,0.01,-110);
	 glColor3f(0,0,0);
	 glVertex3f(0,0.01,-90);
	 glVertex3f(10,0.01,-90);
	 glColor3f(.4,.4,.4);
	 glVertex3f(10,0.01,-80);
	 glVertex3f(0,0.01,-80);
	 glEnd();    	
	//Draw lamp-posts	       
	lposts();
	//Draw foot-paths
              footpath();    
	//Draw roads
	roads();	     	
	//Draw white strips	   
	strip();   
	


	//Begin Texturing
    glEnable(GL_TEXTURE_2D); 
	//Playgorund texturing  
   glBindTexture(GL_TEXTURE_2D, _textureId2);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glColor3f(0.5,0.5,0.5);//Playground base color
	for(int i=-12;i>=-219;i=i-69)
	{
		for(int j=12;j<=108;j=j+32)
		{
		glBegin(GL_QUADS);
		glNormal3f(0,1,0);	     		  
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(j,0.1,i);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(j,0.1,i-69);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(j+32,0.1,i-69);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(j+32,0.1,i);
	glEnd();
		}
	}
   //***************TOP TUNNEL WALL*****************
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	glColor3f(0.2,0.2,0.2); //TOP TUNNEL WALL COLOR

	glBegin(GL_QUADS);	
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.7,9.99,-80);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.7,9.99,-120.1);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(10.1,9.99,-120.1);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(10.1,9.99,-80);
	glEnd();
   //************LEFT TUNNEL WALL***************
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	glColor3f(0.2,0.2,0.2);//LEFT TUNNEL WALL COLOR
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);	
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(0.01f, 0.0f, -79.8f);
	  glTexCoord2f(1.0f, 0.0f);glVertex3f(0.01f, 0.0f, -120.1f);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(0.01f, 10.0f, -120.1f); 
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(0.01f, 10.0f, -79.8f); 
	glEnd();
	//**********RIGHT TUNNEL WALL*******************
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.2,0.2,0.2);//RIGHT TUNNEL WALL COLOR
	glBegin(GL_QUADS);
	glNormal3f(-1,0,0);
	
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(10,0,-120.1);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(10,0,-79.9);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(10,10,-79.9);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(10,10,-120.1);
	glEnd();
	//************LFET TUNNEL BLOCK***************
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	glColor3f(1.0,1.0,1.0);//LEFT TUNNEL BLOCK COLOR
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);	
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -0.4f, -79.9f);
	  glTexCoord2f(1.0f, 0.0f);glVertex3f(-0.0f, -0.4f, -79.9f);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 12.0f, -79.9f); 
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 12.0f, -79.9f); 
	glEnd();
	//**********RIGHT TUNNEL BLOCK*******************
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0,1.0,1.0);//RIGHT TUNNEL BLOCK COLOR
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	

	  glTexCoord2f(0.0f, 0.0f); glVertex3f(10,-0.4,-79.9);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(12,-0.4,-79.9);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(12,12,-79.9);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(10,12,-79.9);
	glEnd();
	//**********TOP TUNNEL BLOCK*******************
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0,1.0,1.0);//TOP TUNNEL BLOCK COLOR
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);	
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2,9.9,-79.9);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(-2,12,-79.9);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(10,12,-79.9);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(10,9.9,-79.9);
	glEnd();	
	//************REAR LFET TUNNEL BLOCK***************
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	glColor3f(1.0,1.0,1.0);//REAR LEFT TUNNEL BLOCK COLOR
	glBegin(GL_QUADS);
	glNormal3f(0,0,-1);
	

	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -0.4f, -120.1f);
	  glTexCoord2f(1.0f, 0.0f);glVertex3f(-0.0f, -0.4f, -120.1f);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 12.0f, -120.1f); 
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 12.0f, -120.1f); 
	glEnd();
	//**********REAR RIGHT TUNNEL BLOCK*******************
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0,1.0,1.0);//REAR RIGHT TUNNEL BLOCK COLOR
	glBegin(GL_QUADS);
	glNormal3f(0,0,-1);	
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(10,-0.4, -120.1);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(12,-0.4,-120.1);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(12,12,-120.1);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(10,12,-120.1);
	glEnd();
	//**********REAR TOP TUNNEL BLOCK*******************
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0,1.0,1.0);//REAR TOP TUNNEL BLOCK COLOR
	glBegin(GL_QUADS);
	glNormal3f(0,0,-1);
	

	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2,10,-120.1);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(-2,12,-120.1);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(10,12,-120.1);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(10,10,-120.1);
	glEnd();
	//**********OUTSIDE RIGHT TUNNEL WALL*******************
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0,1.0,1.0);//OUTSIDE RIGHT TUNNEL WALL COLOR
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);	
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(11.99,-0.5,-120.1);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(11.99,-0.5,-79.9);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(11.99,12,-79.9);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(11.99,12,-120.1);
	glEnd();
	//**********BUILD 1 TEXTURE*******************
   glBindTexture(GL_TEXTURE_2D, _textureId3);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0,1.0,1.0);//BUILD 1 WALL COLOR
	glBegin(GL_QUADS);		
	glNormal3f(1,0,0);
	
	
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2,0,2);//ROAD 1 BUILDING 1
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(-2,0,-40);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(-2,20,-40);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-2,20,2);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(80,0,-302);//ROAD 2 BUILDING 3
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(110,0,-302);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(110,45,-302);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(80,45,-302);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(80,0,-302);//ROAD 2 BUILDING 3 ADDED LEFT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(80,0,-322);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(80,45,-322);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(80,45,-302);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(110,0,-302);//ROAD 2 BUILDING 3 ADDED RIGHT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(110,0,-322);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(110,45,-322);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(110,45,-302);
	  glNormal3f(-1,0,0);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(152,0,2);//ROAD 3 BUILDING 7
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(152,0,-40);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(152,20,-40);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(152,20,2); 
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(80,0,2);//ROAD 4 BUILDING 2
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(110,0,2);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(110,45,2);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(80,45,2);

	  glTexCoord2f(0.0f, 0.0f); glVertex3f(110,0,2);//ROAD 4 BUILDING 2 ADDED LEFT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(110,0,22);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(110,45,22);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(110,45,2);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(80,0,2);//ROAD 4 BUILDING 2 ADDED RIGHT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(80,0,22);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(80,45,22);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(80,45,2);	  	  	  
	  glEnd();	
			//**********BUILD 2 TEXTURE*******************
   glBindTexture(GL_TEXTURE_2D, _textureId4);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(.3,.3,.3);//BUILDING 2 WALL COLOR
	glBegin(GL_QUADS);	
	glNormal3f(1,0,0);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.02,0,-40);//ROAD 1 BUILDING 2
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.02,0,-80);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.02,45,-80);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.02,45,-40);   
	  glTexCoord2f(0.0f, 0.0f);glVertex3f(-2,0,-40);//ROAD 1 BUILDING 2 ADDED LEFT SIDE
	  glTexCoord2f(1.0f, 0.0f);glVertex3f(-20,0,-40);
	  glTexCoord2f(1.0f, 1.0f);glVertex3f(-20,45,-40);
	  glTexCoord2f(0.0f, 1.0f);glVertex3f(-2,45,-40);


	  glTexCoord2f(0.0f, 0.0f);glVertex3f(-2,0,-80);//ROAD 1 BUILDING 2 ADDED RIGHT SIDE
	  glTexCoord2f(1.0f, 0.0f);glVertex3f(-20,0,-80);
	  glTexCoord2f(1.0f, 1.0f);glVertex3f(-20,45,-80);
	  glTexCoord2f(0.0f, 1.0f);glVertex3f(-2,45,-80);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(30,0,-302);//ROAD 2 BUILDING 2
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(80,0,-302);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(80,20,-302);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(30,20,-302);    	  	  	  	    
	  glNormal3f(-1,0,0);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(152.02,0,-40);//ROAD 3 BUILDING 6
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(152.02,0,-80);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(152.02,45,-80);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(152.02,45,-40);	
	  glTexCoord2f(0.0f, 0.0f);glVertex3f(152,0,-40);//ROAD 3 BUILDING 6 ADDED SIDE
	  glTexCoord2f(1.0f, 0.0f);glVertex3f(172,0,-40);
	  glTexCoord2f(1.0f, 1.0f);glVertex3f(172,45,-40);
	  glTexCoord2f(0.0f, 1.0f);glVertex3f(152,45,-40);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(30,0,2);//ROAD 4 BUILDING 3
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(80,0,2);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(80,20,2);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(30,20,2);  		  
	  glEnd();
				//**********BUILD 3 TEXTURE*******************
   glBindTexture(GL_TEXTURE_2D, _textureId5);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.4,0.4,0.4);//BUILDING 3 WALL COLOR
	glBegin(GL_QUADS);	
	glNormal3f(1,0,0);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(152,0,-78);//ROAD 3 BUILDING 4
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(152,0,-110);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(152,80,-110);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(152,80,-78);	   
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(152,0,-78);//ROAD 3 BUILDING 4 ADDED RIGHT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(172,0,-78);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(172,80,-78);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(152,80,-78);      
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(152,0,-110);//ROAD 3 BUILDING 4 ADDED LEFT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(172,0,-110);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(172,80,-110);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(152,80,-110); 	  	  
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2,0,-302);//ROAD 2 BUILDING 1
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(30,0,-302);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(30,50,-302);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-2,50,-302);  	    
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(30,0,-302);//ROAD 2 BUILDING 1 ADDED RIGHT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(30,0,-322);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(30,50,-322);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(30,50,-302);  	    
	  glEnd();
	  //************BUILD 8 TEXTURE******************
	  glBindTexture(GL_TEXTURE_2D, _textureId11);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	  glColor3f(0.4,0.4,0.4);//BUILD 8 WALL COLOR
	  glBegin(GL_QUADS);  
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2,0,2);//ROAD 4 BUILDING 4
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(30,0,2);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(30,50,2);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-2,50,2);  	    
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(30,0,2);//ROAD 4 BUILDING 4 ADDED LEFT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(30,0,22);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(30,50,22);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(30,50,2);  	    
	  glEnd();
		//**********BUILD 4 TEXTURE*******************    
   glBindTexture(GL_TEXTURE_2D, _textureId6);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.4,0.4,0.4);//BUILD 4 WALL COLOR
	glBegin(GL_QUADS);	
	glNormal3f(1,0,0); 
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.02,0,-110);//ROAD 1 BUILDING 3
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.02,0,-170);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.02,25,-170);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.02,25,-110);
	  
	  glTexCoord2f(0.0f, 0.0f);glVertex3f(-2,0,-110);//ROAD 1 BUILDING 3 ADDED LEFT SIDE
	  glTexCoord2f(1.0f, 0.0f);glVertex3f(-20,0,-110);
	  glTexCoord2f(1.0f, 1.0f);glVertex3f(-20,25,-110);
	  glTexCoord2f(0.0f, 1.0f);glVertex3f(-2,25,-110);
	  glTexCoord2f(0.0f, 0.0f);glVertex3f(110,0,-302);//ROAD 2 BUILDING 4
	  glTexCoord2f(1.0f, 0.0f);glVertex3f(152,0,-302);
	  glTexCoord2f(1.0f, 1.0f);glVertex3f(152,30,-302);
	  glTexCoord2f(0.0f, 1.0f);glVertex3f(110,30,-302);
	  glTexCoord2f(0.0f, 0.0f);glVertex3f(110,0,2);//ROAD 4 BUILDING 1
	  glTexCoord2f(1.0f, 0.0f);glVertex3f(152,0,2);
	  glTexCoord2f(1.0f, 1.0f);glVertex3f(152,30,2);
	  glTexCoord2f(0.0f, 1.0f);glVertex3f(110,30,2);	  
   glNormal3f(-1,0,0);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(152.02,0,-110);//ROAD 3 BUILDING 4
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(152.02,0,-170);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(152.02,45,-170);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(152.02,45,-110);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(152.02,0,-170);//ROAD 3 BUILDING 4 ADDED LEFT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(172,0,-170);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(172,45,-170);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(152.02,45,-170);
	glEnd();




			//**********BUILD 5 TEXTURE*******************
   glBindTexture(GL_TEXTURE_2D, _textureId8);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0,1.0,1.0);//BUILD 5 WALL COLOR
	glBegin(GL_QUADS);		
	glNormal3f(1,0,0);  	   
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2,0,-170);//ROAD 1 BUILDING 4
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(-2,0,-210);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(-2,40,-210);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-2,40,-170);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2,0,-170);//ROAD 1 BUILDING 4 ADDED LEFT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(-20,0,-170);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(-20,40,-170);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-2,40,-170); 
	  glNormal3f(-1,0,0);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(152,0,-170);//ROAD 3 BUILDING 3
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(152,0,-210);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(152,40,-210);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(152,40,-170);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(152,0,-210);//ROAD 3 BUILDING 3 ADDED LEFT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(172,0,-210);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(172,40,-210);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(152,40,-210);
	  glEnd();

	  //**********BUILD 6 TEXTURE*******************
   glBindTexture(GL_TEXTURE_2D, _textureId9);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0,1.0,1.0);//BUILD 6 WALL COLOR
	glBegin(GL_QUADS);		
	glNormal3f(1,0,0);     	  
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2,0,-210);//ROAD 1 BUILDING 6
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(-2,0,-260);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(-2,20,-260);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-2,20,-210);	   
	  glNormal3f(-1,0,0);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(152,0,-210);//ROAD 3 BUILDING 2
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(152,0,-260);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(152,20,-260);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(152,20,-210);
    glEnd();
		//**********BUILD 7 TEXTURE*******************
   glBindTexture(GL_TEXTURE_2D, _textureId10);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   	  
	glColor3f(1.0,1.0,1.0);//BUILDING 7 WALL COLOR
	glBegin(GL_QUADS);		
	glNormal3f(1,0,0);    	  


	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2,0,-260);//ROAD 1 BUILDING 7
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(-2,0,-302);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(-2,60,-302);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-2,60,-260);	 	  
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-2,0,-260);//ROAD 1 BUILDING 7 ADDED LEFT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(-20,0,-260);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(-20,60,-260);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-2,60,-260);   	  
	  glNormal3f(-1,0,0);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(152,0,-260);//ROAD 3 BUILDING 1
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(152,0,-302);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(152,40,-302);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(152,40,-260);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(152,0,-260);//ROAD 3 BUILDING 1 ADDED RIGHT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(172,0,-260);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(172,40,-260);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(152,40,-260);
	  glEnd();		    	  	  
			//**********SKY DESIGN*******************
   glBindTexture(GL_TEXTURE_2D, _textureId7);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0,1.0,1.0);//SKY COLOR
	glBegin(GL_QUADS);
	glNormal3f(0,-1,0);
	   
	 glTexCoord2f(0.0f, 0.0f); glVertex3f(-3000,700,-3800);//SKY ADDED TOP SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(2500,700,-3800);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(2500,700,3000);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-3000,700,3000);       
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-3000,900,-3400);//SKY ADDED FRONT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(2500,900,-3400);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(2500,-900,-3400);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-300,-900,-3400);
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(2500,-800,-3800);//SKY ADDED RIGHT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(2500,800,-3800);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(2500,800,3000);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(2500,-800,3000); 
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-3000,-800,3000);//SKY ADDED BACK SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(2700,-800,3000);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(2700,800,3000);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-3000,800,3000); 
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-3000,800,-3800);//SKY ADDED LEFT SIDE
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(-3000,-800,-3800);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(-3000,-800,3000);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(-3000,800,3000);
	glEnd();
	//********SPHERE TEXTURING******************
  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);


  glBindTexture(GL_TEXTURE_2D, _textureId7);
  glPushMatrix();
  glColor3f(1,1,1);
  glTranslatef(75,0,-150);
  glEnable(GL_TEXTURE_GEN_S);		// Enable Texture Coord Generation For S 
  glEnable(GL_TEXTURE_GEN_T);	
  glutSolidSphere(275.0f,45,45);
  glDisable(GL_TEXTURE_GEN_S);		// Enable Texture Coord Generation For S 
  glDisable(GL_TEXTURE_GEN_T);	
  glPopMatrix();
//*****************************PARK DESIGN***************
  glBindTexture(GL_TEXTURE_2D, _textureId12); //BUSH 1
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glColor3f(1.0,1.0,1.0);
  glBegin(GL_QUADS);
  glNormal3f(0,-1,0);	   
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(65,1.5,-160);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(85,1.5,-160);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(85,1.5,-140);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(65,1.5,-140);       
                 glTexCoord2f(0.0f, 0.0f); glVertex3f(65,1.5,-160);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(65,-2,-160);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(65,-2,-140);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(65,1.5,-140); 

	  glTexCoord2f(0.0f, 0.0f); glVertex3f(65,1.5,-140);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(65,-2,-140);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(85,-2,-140);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(85,1.5,-140); 
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(85,1.5,-140);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(85,-2,-140);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(85,-2,-160);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(85,1.5,-160); 
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(65,1.5,-160);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(65,-2,-160);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(85,-2,-160);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(85,1.5,-160);
     glEnd();
   glBindTexture(GL_TEXTURE_2D, _textureId13);//BUSH 2
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUADS);
	glNormal3f(0,-1,0);	   
	 glTexCoord2f(0.0f, 0.0f); glVertex3f(70,3,-155);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(80,3,-155);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(80,3,-145);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(70,3,-145);       
      glTexCoord2f(0.0f, 0.0f); glVertex3f(70,3,-155);
      glTexCoord2f(1.0f, 0.0f); glVertex3f(70,1,-155);

	  glTexCoord2f(1.0f, 1.0f); glVertex3f(70,1,-145);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(70,3,-145); 
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(70,3,-145);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(70,1,-145);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(80,1,-145);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(80,3,-145); 
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(80,3,-145);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(80,1,-145);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(80,1,-155);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(80,3,-155); 
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(70,3,-155);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(70,1,-155);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(80,1,-155);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(80,3,-155);
       glEnd();
  glBindTexture(GL_TEXTURE_2D, _textureId14);//STONE PYRAMID
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUADS);
	glNormal3f(0,-1,0); 
      //*************LEFT FACE************
                 glTexCoord2f(0.0f, 0.0f); glVertex3f(75,10,-150);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(71,2,-154);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(71,2,-146);
	
                 glTexCoord2f(0.0f, 1.0f); glVertex3f(75,10,-150); 
	  //*************FRONT FACE************
 	  glTexCoord2f(0.0f, 0.0f); glVertex3f(75,10,-150);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(71,2,-146);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(79,2,-146);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(75,10,-150); 	  
	  //*************RIGHT FACE************
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(75,10,-150);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(79,2,-146);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(79,2,-154);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(75,10,-150); 
	  //*************OPPOSITE FACE************
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(75,10,-150);
	  glTexCoord2f(1.0f, 0.0f); glVertex3f(71,2,-154);
	  glTexCoord2f(1.0f, 1.0f); glVertex3f(79,2,-154);
	  glTexCoord2f(0.0f, 1.0f); glVertex3f(75,10,-150);
	  glEnd();	
     glDisable(GL_TEXTURE_2D);	   
		 glutSwapBuffers();    
		 glFlush();  
}
void keys(unsigned char key, int x, int y)
{
/* Use x, X, y, Y, z, and Z keys to move viewer */


	if(key == 'x') {viewer[0]-= 1.0;focus[0]-=1.0;}
	if(key == 'X') {viewer[0]+= 1.0;focus[0]+=1.0;}
	if(key == 'y') {viewer[1]-= 1.0;focus[1]-=1.0;}
	if(key == 'Y') {viewer[1]+= 1.0;focus[1]+=1.0;}
	if(key == 'z') {viewer[2]-= 1.0;focus[2]-=1.0;}
	if(key == 'Z') {viewer[2]+= 1.0;focus[2]+=1.0;}    
	if(key == 'u') {u=1;m=4;}
	if(key == 'd') {m=3;d=1;};
	if(key == 'l') {m=2;t1=1;x1=0;}
	if(key == 'r') {m=1;t1=1;x1=0;}
               if(key == 27) exit(0);
    display();
}
//ARROW KEYS SPECIFICATION
void k(int key,int x,int y)
{   if(key == GLUT_KEY_LEFT) {;m=2;t1=1;x1=0;}
	if(key == GLUT_KEY_RIGHT) {m=1;t1=1;x1=0;}
	if(key == GLUT_KEY_UP) 
	{   if(viewer[2]>-295&&viewer[0]<6)//ROAD 1
			{viewer[2]-= 1.0;focus[2]-=1.0;r1=1;r2=0;r3=0;r4=0;}
	   else 
		   if(viewer[2]==-295&&viewer[0]<145)//ROAD 2
			{viewer[0]+=1.0;focus[0]+=1.0;r2=1;r1=0;r3=0;r4=0;}
       else


	       if(viewer[2]>=-295&&viewer[2]<-5&&viewer[0]==145)//ROad 3
		   {viewer[2]+=1.0;focus[2]+=1.0;r3=1;r1=0;r2=0;r4=0;}
       else
		   if(viewer[2]>=-5&&viewer[0]<=145)//ROAD 4
		   {viewer[0]-=1.0;focus[0]-=1.0;r4=1;r1=0;r2=0;r3=0;} 
		   an=0;
	}
	if(key == GLUT_KEY_DOWN) 
	{   if(viewer[2]>=-295&&viewer[0]<=5&&viewer[2]<-5)
			{viewer[2]+= 1.0;focus[2]+=1.0;}
	   else 
		   if(viewer[2]==-295&&viewer[0]<=145&&viewer[0]>5)
			{viewer[0]-=1.0;focus[0]-=1.0;}
       else
	       if(viewer[2]>=-295&&viewer[2]<=-5&&viewer[0]==145)
		   {viewer[2]-=1.0;focus[2]-=1.0;}
       else
		   if(viewer[2]>=-5&&viewer[0]<=145)
		   {viewer[0]+=1.0;focus[0]+=1.0;} 
	}
	 display();
}
void myinit(int h,int w)
{
 

glViewport(0,0,h,w);
 glClearColor (0.3, 0.3, 0.5, 1.0 );
 glClear (GL_COLOR_BUFFER_BIT);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(40,(GLfloat)h/(GLfloat)w,1,600); 
 glEnable(GL_LIGHTING);
 GLfloat ambientLight1[] = { 1.f, 1.f, 1.f, 1.0f };
 glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight1);
 glEnable(GL_LIGHT0);
 GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };//LIGHT 1
 GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
 glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
 glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
 GLfloat lightPos[] = { 75.f, 40.f, -150.0f, 1.0f };//LIGHT 1 POSITION
 glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
 glEnable(GL_COLOR_MATERIAL);
 glMatrixMode(GL_MODELVIEW);
//**********TEXTURE IMAGES*****************
Image* image = loadBMP("BrickWall1.bmp");
_textureId = loadTexture(image);
delete image;
Image* image2 = loadBMP("grass2.bmp");
_textureId2 = loadTexture(image2);
delete image2;

Image* image3 = loadBMP("build1.bmp");
_textureId3 = loadTexture(image3);
delete image3;
Image* image4 = loadBMP("build2.bmp");
_textureId4 = loadTexture(image4);
delete image4;
Image* image5 = loadBMP("build3.bmp");
_textureId5 = loadTexture(image5);
delete image5;
Image* image6 = loadBMP("build4.bmp");
_textureId6 = loadTexture(image6);
delete image6;
Image* image7 = loadBMP("image--sky2.bmp");
_textureId7 = loadTexture(image7);
delete image7;
Image* image8 = loadBMP("build5.bmp");
_textureId8 = loadTexture(image8);
delete image8;
Image* image9 = loadBMP("build6.bmp");
_textureId9 = loadTexture(image9);
delete image9;
Image* image10 = loadBMP("build7.bmp");
_textureId10 = loadTexture(image10);
delete image10;


Image* image11 = loadBMP("build8.bmp");
_textureId11 = loadTexture(image11);
delete image11;
Image* image12 = loadBMP("bush1.bmp");
_textureId12 = loadTexture(image12);
delete image12;
Image* image13 = loadBMP("bush2.bmp");
_textureId13 = loadTexture(image13);
delete image13;
Image* image14 = loadBMP("stone.bmp");
_textureId14 = loadTexture(image14);
delete image14;
}


void main(int argc,char ** argv)
{
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
 glutInitWindowSize(600,600);
 glutInitWindowPosition(100,100);
 glutCreateWindow("PROJECT");
 glutReshapeFunc(myinit);
 glutKeyboardFunc(keys);
 glutSpecialFunc(k);

 glutDisplayFunc(display);  
 glEnable(GL_DEPTH_TEST); 
 glutMainLoop();
}