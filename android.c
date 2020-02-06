#include <GL/glut.h>
#include <stdio.h>

float yRotationAngle = 0.08f;
static float r;
// int x1, y1, x2, y2;
GLfloat t = 0.0f;
GLfloat s = 0.0f;


void myInit() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glPointSize(3.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,800,0,800);
}
void draw_line(int x, int y) {
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void draw_pixel(int cx,int cy,int x, int y) {
  glBegin(GL_POINTS);
  
  glVertex2i(cx+x, cy+y);
  glVertex2i(cx+x, cy-y);
  
  glVertex2i(cx-x, cy+y);
  glVertex2i(cx-x, cy-y);

  glVertex2i(cx+y, cy+x);
  glVertex2i(cx+y, cy-x);
  
  glVertex2i(cx-y, cy+x);
  glVertex2i(cx-y, cy-x);
  
  glEnd();
}

void draw_h_pixel(int cx,int cy,int x, int y) {
  glBegin(GL_POINTS);
  
  glVertex2i(cx+x, cy+y);
//  glVertex2i(cx+x, cy-y);
  
  glVertex2i(cx-x, cy+y);
  //glVertex2i(cx-x, cy-y);

  glVertex2i(cx+y, cy+x);
  //glVertex2i(cx+y, cy-x);
  
  glVertex2i(cx-y, cy+x);
  //glVertex2i(cx-y, cy-x);
  
  glEnd();
}

void drawLine(int x1, int x2, int y1, int y2) {
  int dx, dy, i, e;
  int incx, incy, inc1, inc2;
  int x,y;

  dx = x2-x1;
  dy = y2-y1;

  if (dx < 0) dx = -dx;
  if (dy < 0) dy = -dy;
  incx = 1;
  if (x2 < x1) incx = -1;
  incy = 1;
  if (y2 < y1) incy = -1;
  x = x1; y = y1;
  if (dx > dy) {
    draw_line(x, y);
    e = 2 * dy-dx;
    inc1 = 2*(dy-dx);
    inc2 = 2*dy;
    for (i=0; i<dx; i++) {
      if (e >= 0) {
        y += incy;
        e += inc1;
      }
      else
        e += inc2;
      x += incx;
      draw_line(x, y);
    }

  } else {
    draw_line(x, y);
    e = 2*dx-dy;
    inc1 = 2*(dx-dy);
    inc2 = 2*dx;
    for (i=0; i<dy; i++) {
      if (e >= 0) {
        x += incx;
        e += inc1;
      }
      else
        e += inc2;
      y += incy;
      draw_line(x, y);
    }
  }
}

void drawCircle(int cx,int cy,float r){
  int x=0,y=r,d=3-2*r;

  draw_pixel(cx,cy,x,y);

  while(x<=y){
    if(d<=0){
      d = d + 4*x + 6;
    }else{
      d = d + 4*x - 4*y + 10;
      y = y-1;
    }
    x=x+1;
    draw_pixel(cx,cy,x,y);
  }
}

void drawSemiCircle(int cx,int cy,float r){
  int x=0,y=r,d=3-2*r;

  draw_h_pixel(cx,cy,x,y);

  while(x<=y){
    if(d<=0){
      d = d + 4*x + 6;
    }else{
      d = d + 4*x - 4*y + 10;
      y = y-1;
    }
    x=x+1;
    draw_h_pixel(cx,cy,x,y);
  }
}

void drawHead(){
    drawSemiCircle(400,500,75);
    drawLine(325,475,500,500);
}

void drawEyes(){
    drawCircle(365,530,15);
    drawCircle(435,530,15);

}

void drawAntenna(){
    //r
    drawLine(437,475,560,600);
    //l
    drawLine(362,335,560,600);
}

void drawBody(){
    drawLine(325,475,490,490);
    drawLine(325,325,490,340);
    drawLine(475,475,490,340);
    drawLine(325,360,340,340);
    drawLine(385,415,340,340);
    drawLine(440,475,340,340);

    //llegs
    drawLine(360,360,340,290);
    drawLine(385,385,340,290);
    drawLine(360,385,290,290);

    //rleg
    drawLine(415,415,340,290);
    drawLine(440,440,340,290);
    drawLine(415,440,290,290);

}

void drawRhand(){
    drawLine(485,510,490,490);
    drawLine(485,510,340,340);
    drawLine(485,485,490,340);
    drawLine(510,510,490,340);
}

void drawLhand(){
    drawLine(315,290,490,490);
    drawLine(315,290,340,340);
    drawLine(315,315,490,340);
    drawLine(290,290,490,340);
}

void keyboard(unsigned char key, int x, int y)
{
  //-------- spin --------
  switch(key){
    case 'r' :  
                  glClear(GL_COLOR_BUFFER_BIT); 
                drawHead();

                //eyes
                drawEyes();

                //antenna
                drawAntenna();

                //body
                drawBody();
              
                glPushMatrix();
               
                glRotatef(yRotationAngle, 0.0f, 0.0f, 1.0f);
                yRotationAngle=yRotationAngle+0.5f;
               // glTranslatef(0.0f,0.0f,-40.0f);
                    //head
                  

                    //right hand
                    drawRhand();

                    //left hand
                    drawLhand();
                    
                   
                glPopMatrix();
                 glFlush();
              break;
    case 's' : 
                  glClear(GL_COLOR_BUFFER_BIT); 
                //head
                  yRotationAngle=0.0f;
                  s=0.0f;
                  t=0.0f;
                drawHead();

                //eyes
                drawEyes();

                //antenna
                drawAntenna();

                //body
                drawBody();

                //right hand
                drawRhand();

                //left hand
                drawLhand();
                
                glFlush();
              break;
    case 'i' :  glClear(GL_COLOR_BUFFER_BIT);  
                s=s+0.5f;
                glPushMatrix();
                 glScalef(s, s, 1.0);
               
                    //head
                    drawHead();

                    //eyes
                    drawEyes();

                    //antenna
                    drawAntenna();

                    //body
                    drawBody();

                    //right hand
                    drawRhand();

                    //left hand
                    drawLhand();
                    
                    glFlush();
                glPopMatrix();
              break;
    case 'd' :glClear(GL_COLOR_BUFFER_BIT);  
                s=s-0.5f;
                glPushMatrix();
                 glScalef(s, s, 1.0);
               
                    //head
                    drawHead();

                    //eyes
                    drawEyes();

                    //antenna
                    drawAntenna();

                    //body
                    drawBody();

                    //right hand
                    drawRhand();

                    //left hand
                    drawLhand();
                    
                    glFlush();
                glPopMatrix();
              
              break;
    case 't' :   glClear(GL_COLOR_BUFFER_BIT);  
                t=t+0.5f;
                glPushMatrix();
                 glTranslatef(t, 0.0, 0.0);
               
                    //head
                    drawHead();

                    //eyes
                    drawEyes();

                    //antenna
                    drawAntenna();

                    //body
                    drawBody();

                    //right hand
                    drawRhand();

                    //left hand
                    drawLhand();
                    
                    glFlush();
                glPopMatrix();
              break;
    case 'h' :  glClear(GL_COLOR_BUFFER_BIT);  
                t=t-0.5f;
                glPushMatrix();
                 glTranslatef(t, 0.0, 0.0);
               
                    //head
                    drawHead();

                    //eyes
                    drawEyes();

                    //antenna
                    drawAntenna();

                    //body
                    drawBody();

                    //right hand
                    drawRhand();

                    //left hand
                    drawLhand();
                    
                    glFlush();
                glPopMatrix();
              break;          
    case 'c' :
              glClear(GL_COLOR_BUFFER_BIT);
              glFlush();
              break;
    case 'e' : exit(0);  
              break;
  }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT); 
    glColor3f(0.4, 0.9, 0.2);
    int cx,cy;
    float r;

    //set the values of x1,y1 & x2,y2 here
    cx =0;
    cy =0;
    r =40;

    //head
    drawHead();

    //eyes
    drawEyes();

    //antenna
    drawAntenna();

    //body
    drawBody();

    //right hand
    drawRhand();

    //left hand
    drawLhand();
    
    glFlush();
}

void main(int argc, char **argv) {

  // printf( "Enter (x1, y1, x2, y2)\n");
  // scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(700, 700);
  glutInitWindowPosition(50, 0);
  glutCreateWindow("Bresenham's Circle Drawing");
  myInit();
  glutDisplayFunc(myDisplay);
  glutKeyboardFunc(keyboard);
   
  //glutIdleFunc(myDisplay);// Tell GLUT to use the method "display" as our idle method as well  
  
  // glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping  
  glutMainLoop();
}