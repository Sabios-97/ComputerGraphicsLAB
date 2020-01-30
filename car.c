#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

int X, Y, iR, oR;
GLfloat angleL = 0.0f;
GLfloat angleR = 0.0f;
int max_speedL = 320 - 140;
int min_speedL = -320 + 80;
int max_speedR = 320 - 240;
int min_speedR = -320 + 180;
GLfloat speedL = 0.0f;
GLfloat speedR = 100.0f;
int i;
int directionL = 1;
int directionR = 0;
int flagL = 0;
int flagR = 0;

void draw_circle(int r)
{

    glBegin(GL_POINTS);
    int x = 0, y = r;
    int p = 3 - 2 * r;
    while (x < y)
    {
        x++;
        if (p < 0)
            p = p + 4 * x + 6;
        else
        {
            p = p + 4 * (x - y) + 10;
            y--;
        }

        glVertex2i(x + X, y + Y);
        glVertex2i(y + X, x + Y);
        glVertex2i(x + X, -y + Y);
        glVertex2i(y + X, -x + Y);
        glVertex2i(-x + X, -y + Y);
        glVertex2i(-y + X, -x + Y);
        glVertex2i(-x + X, y + Y);
        glVertex2i(-y + X, x + Y);
    }
}
void idle()
{
    glutPostRedisplay();
}

void draw_line(int x1, int y1, int x2, int y2)
{
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();

    // int dx = x2 - x1;
    // int dy = y2 - y1;

    // int stepx = 1, stepy = 1;

    // int fraction = 0, fraction_increment = 0;

    // if (dy < 0)
    // {
    //     dy = -dy;
    //     stepy = -1;
    // }
    // if (dx < 0)
    // {
    //     dx = -dx;
    //     stepx = -1;
    // }

    // glBegin(GL_POINTS);

    // if (dx >= dy)
    // {
    //     fraction = 2 * dy - dx;
    //     fraction_increment = 2 * dy;
    //     while (x1 <= x2)
    //     {
    //         x1 += stepx;
    //         if (fraction >= 0)
    //         {
    //             y1 += stepy;
    //             fraction -= 2 * dx;
    //         }

    //         fraction += fraction_increment;
    //         glVertex2i(x1, y1);
    //     }
    // }
    // else
    // {
    //     fraction = 2 * dx - dy;
    //     fraction_increment = 2 * dx;
    //     while (y1 <= y2)
    //     {
    //         if (fraction >= 0)
    //         {
    //             x1 += stepx;
    //             fraction -= 2 * dy;
    //         }
    //         fraction += fraction_increment;
    //         glVertex2i(x1, y1);
    //     }
    // }

    // glEnd();
    glBegin(GL_POINTS);

    glEnd();
}

void circle()
{

    glPushMatrix();
    directionL = (speedL < max_speedR) ? 1 : -1;
    if (directionL == 1 && flagL == 0)
    {
        glTranslatef(speedL, 0.0, 0.0);
        speedL = speedL + 0.01;
        if (speedL >= max_speedR)
        {
            flagL = 1;
        }
    }
    else
    {
        directionL = -1;
        glTranslatef(speedL, 0.0, 0.0);
        speedL = speedL - 0.01;
        if (speedL <= min_speedL)
        {
            flagL = 0;
        }
    }
    glRotatef(angleL, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // left wheel
    X = 0;
    Y = 0;
    iR = 10;
    draw_circle(iR);
    glEnd();
    X = 0;
    Y = 0;
    oR = 40;
    draw_circle(oR);
    glEnd();
    glBegin(GL_POINTS);

    for (i = 10; i <= 40; i++)
    {
        glVertex2i(i, 0);
        glVertex2i(0, i);
        glVertex2i(-i, 0);
        glVertex2i(0, -i);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    directionR = (speedR < max_speedL) ? 1 : -1;
    if (directionR == 1 && flagR == 0)
    {
        glTranslatef(speedR + 100, 0.0, 0.0);
        speedR = speedR + 0.01;
        if (speedR >= max_speedL)
        {
            flagR = 1;
        }
    }
    else
    {
        directionR = -1;
        glTranslatef(speedR + 100, 0.0, 0.0);
        speedR = speedR - 0.01;
        if (speedR <= min_speedR)
        {
            flagR = 0;
        }
    }
    glRotatef(angleR, 0, 0, 1);

    // right wheel
    X = 0;
    Y = 0;
    iR = 10;
    draw_circle(iR);
    glEnd();
    X = 0;
    Y = 0;
    oR = 40;
    draw_circle(oR);
    glEnd();
    glBegin(GL_POINTS);

    for (i = 10; i <= 40; i++)
    {
        glVertex2i(i, 0);
        glVertex2i(0, i);
        glVertex2i(-i, 0);
        glVertex2i(0, -i);
    }
    glEnd();

    glPopMatrix();

    angleL += (-directionL) * 0.02;
    angleR += (-directionR) * 0.02;

    // glBegin(GL_POINTS);
    // for (i = 40; i <= 60; i++)
    //     glVertex2i(i, 0);
    // glEnd();

    glBegin(GL_POINTS);
    for (i = -320; i <= 320; i++)
        glVertex2i(i, -40);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 640);
    glutCreateWindow("Car Wheel");
    gluOrtho2D(-320, 320, -320, 320);
    glutIdleFunc(idle);
    glutDisplayFunc(circle);
    glutMainLoop();
}