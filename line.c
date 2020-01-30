#include <GL/glut.h>
#include <stdio.h>


// int x1, y1, x2, y2;

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
gluOrtho2D(-100,100,-100,100);
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

void drawRings(int cx,int cy,float r){

	float r2 = r/5;

	drawCircle(cx,cy,r);
	glFlush();
	drawCircle(cx,cy,r2);
	glFlush();
}
void drawSpokes(int cx,int cy,float r){

	float r2 = r/5;

	drawLine(r2,r,0,0);
	glFlush();

	drawLine(-r2,-r,0,0);
	glFlush();

	drawLine(0,0,r2,r);
	glFlush();

	drawLine(0,0,-r2,-r);
	glFlush();

	/*---------------------*/
	
	drawLine((r2)*0.7,r*0.7,(r2)*0.7,r*0.7);
	glFlush();

	drawLine(-(r2)*0.7,-r*0.7,(r2)*0.7,r*0.7);
	glFlush();

	drawLine(-(r2)*0.7,-r*0.7,-(r2)*0.7,-r*0.7);
	glFlush();

	drawLine((r2)*0.7,r*0.7,-(r2)*0.7,-r*0.7);
	glFlush();

}
void drawSurface(int cx,int cy,float r){
	drawLine(-80,80,-50,-50);
	glFlush();
}

void myDisplay() {
		  glClear(GL_COLOR_BUFFER_BIT); 
		  glColor3f(1.0, 0.0, 0.0);


	int cx,cy;
	float r;

	//set the values of x1,y1 & x2,y2 here
	cx =0;
	cy =0;
	r =50;

	drawRings(cx,cy,r);
	drawSpokes(cx,cy,r);
	drawSurface(cx,cy,r);

	
	
}

void main(int argc, char **argv) {

	// printf( "Enter (x1, y1, x2, y2)\n");
	// scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bresenham's Circle Drawing");
	myInit();
	glutDisplayFunc(myDisplay);
	 
glutIdleFunc(display); // Tell GLUT to use the method "display" as our idle method as well  
  
glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping  
	glutMainLoop();
}