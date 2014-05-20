#include <math.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define GL_PI 3.1415f
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

void display(void)
{
    GLubyte fire[] = {0x00, 0x00, 0x07};
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_POLYGON_STIPPLE);
    glPolygonStipple(fire);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
        glVertex2f(-20.0f, 50.0f);
        glVertex2f(20.0f, 50.0f);
        glVertex2f(50.0f, 20.0f);
        glVertex2f(50.0f, -20.0f);
        glVertex2f(20.0f, -50.0f);
        glVertex2f(-20.0f, -50.0f);
        glVertex2f(-50.0f, -20.0f);
        glVertex2f(-50.0f, 20.0f);
    glEnd();
    glutSwapBuffers();
}

void display4(void)
{
    GLfloat x, y, angle;
    int iPivot = 1;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_BACK, GL_LINE);
    //glPolygonMode(GL_BACK, GL_FILL);
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 75.0f);
    for(angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 8.0f))
    {
        x = 50.0f * sin(angle);
        y = 50.0f * cos(angle);

        if((iPivot % 2) == 0)
            glColor3f(0.0f, 1.0f, 0.0f);
        else
            glColor3f(1.0f, 0.0f, 0.0f);
        iPivot++;
        glVertex2f(x, y);
    }
    glEnd();
    glFrontFace(GL_CCW);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        for(angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 8.0f))
        {
            x = 50.0f * sin(angle);
            y = 50.0f * cos(angle);
            
            if((iPivot % 2) == 0)
                glColor3f(0.0f, 1.0f, 0.0f);
            else
                glColor3f(1.0f, 0.0f, 0.0f);

            iPivot++;
            glVertex2f(x, y);
        }
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void display3(void)
{
    GLfloat y;
    GLint factor = 1;
    GLushort pattern = 0x0555;
    glEnable(GL_LINE_STIPPLE);
    for(y = -90.0f; y < 90.0f; y += 20.0f)
    {
        glLineStipple(factor, pattern);
        glBegin(GL_LINES);
            glVertex2f(-80.0f, y);
            glVertex2f(80.0f, y);
        glEnd();
        factor++;
    }
    glutSwapBuffers();
}

void display2(void)
{
    GLfloat y;
    GLfloat fCurrSize; 
    GLfloat fSizes[2];
    GLfloat step;

    glGetFloatv(GL_LINE_WIDTH_RANGE, fSizes);
    glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &step);
    
    fCurrSize = fSizes[0];
    for(y = -90.0f; y < 90.0f; y += 20.0f)
    {
        glLineWidth(fCurrSize);
        glBegin(GL_LINES);
            glVertex2f(-80.0f, y);
            glVertex2f(80.0f, y);
        glEnd();
        fCurrSize += step;
    }
    glutSwapBuffers();
}

void display1(void)
{
    GLfloat x, y, z, angle;
    GLfloat sizes[2];
    GLfloat step;
    GLfloat curSize;
    GLfloat xRot = 90.0f;
    GLfloat yRot = 0.0f;

    glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
    
    curSize = sizes[0];

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    //glBegin(GL_LINES);
    z = -50.0f;
    glColor3f(0.5f, 0.5f, 0.5f);
    for(angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += 0.1f)
    {
        x = 50.0f * sin(angle);
        y = 50.0f * cos(angle);
        glPointSize(5);
        curSize += step;
        //glBegin(GL_POINTS);
        glVertex3f(x, y, z);
        //glEnd();
        z += 0.5f;
    }
    glEnd();
    glPopMatrix(); 
//    glRotatef(45, 1.0f, 0.0f, 0.0f);
 //   glRotatef(45, 0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
        glColor3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(100.0f, 0.0f, 0.0f);

        glColor3f(0.7f, 0.5f, 0.5f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 100.f, 0.0f);

        glColor3f(0.5f, 0.5f, 0.8f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

/*    glBegin(GL_LINES);
        z = 0.0f;
        for(angle = 0.0f; angle <= GL_PI; angle += (GL_PI / 20.0f))
        {
            x = 50.0f * sin(angle);
            y = 50.0f * cos(angle);
            glVertex3f(x, y, z);
            x = 50.0f * sin(angle + GL_PI);
            y = 50.0f * cos(angle + GL_PI);
            glVertex3f(x, y, z);
        }
    glEnd();
*/
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(50.0f, 50.0f, 0.0f);
        glVertex3f(50.0f, 100.0f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

void initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);
    glFrontFace(GL_CCW);
}

void reshape(int w, int h)
{
    GLfloat nRange = 100.0f;
    if( w == 0)
        w = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w <= h)
        glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
    else
        glOrtho(-nRange * h / w, nRange * h / w, -nRange, nRange, -nRange, nRange);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("test");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    initializeGL();
    glutMainLoop();

    return 0;
}
