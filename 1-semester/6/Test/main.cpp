#include <GL/glut.h>

#include <stdlib.h>
#include <bits/stdc++.h>


float red[6]={0.4,0.1,0.4,0.4,0.4},green[6]={1,0.1,1,1,1},blue[6]={1,0.1,1,1,1};
int currentPos=1;
char path[4][100]={"start C:\\Users\\osoka\\Desktop\\Универ\\1_семестр\\Прога\\Лабы\\4\\Analizer\\Analizer.cbp",
"start C:\\Users\\osoka\\Desktop\\Универ\\1_семестр\\Прога\\Лабы\\1\\mOD\\mOD.cbp",
"start C:\\Users\\osoka\\Desktop\\Универ\\1_семестр\\Прога\\Лабы\\2\\sqr\\sqr.cbp",
"start C:\\Users\\osoka\\Desktop\\Универ\\1_семестр\\Прога\\Лабы\\3\\Analizer\\Analizer.cbp"};

char str1[6]={"Lab 1"};
char str2[6]={"Lab 2"};
char str3[6]={"Lab 3"};
char str4[6]={"Lab 4"};



void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(red[1],green[1],blue[1]);
	glRectf(-0.9,0.9,0.9,0.55);
    glColor3f(1, 0, 1);
	glRasterPos2f(-0.3,0.64);

    for (int i=0;i<sizeof(str1);i++)
    {
        glutBitmapCharacter ( GLUT_BITMAP_TIMES_ROMAN_24,str1[i] );
    }
    glColor3f(red[2],green[2],blue[2]);
	glRectf(-0.9,0.45,0.9,0.05);
	glColor3f(1, 0, 1);
	glRasterPos2f(-0.3, 0.16);

    for (int i=0;i<sizeof(str2);i++)
    {
        glutBitmapCharacter ( GLUT_BITMAP_TIMES_ROMAN_24,str2[i] );
    }
    glColor3f(red[3],green[3],blue[3]);
	glRectf(-0.9,-0.05,0.9,-0.45);
	glColor3f(1, 0, 1);
	glRasterPos2f(-0.3, -0.34);

    for (int i=0;i<sizeof(str3);i++)
    {
        glutBitmapCharacter ( GLUT_BITMAP_TIMES_ROMAN_24,str3[i] );
    }
    glColor3f(red[0],green[0],blue[0]);
	glRectf(-0.9,-0.55,0.9,-0.9);
	glColor3f(1, 0, 1);
	glRasterPos2f(-0.3,-0.8);

    for (int i=0;i<sizeof(str4);i++)
    {
        glutBitmapCharacter ( GLUT_BITMAP_TIMES_ROMAN_24,str4[i] );
    }


    glutSwapBuffers();
}

void keySpecial(int key, int x, int y)
{

	switch(key) {
		case GLUT_KEY_UP:
            std::swap(red[(currentPos-1)%4] ,red[currentPos]);
            std::swap(green[(currentPos-1)%4] , green[currentPos]);
            std::swap(blue[(currentPos-1)%4] , blue[currentPos]);
            currentPos=(currentPos-1)%4; break;
		case GLUT_KEY_DOWN:
            std::swap(red[(currentPos+1)%4] ,red[currentPos]);
            std::swap(green[(currentPos+1)%4] , green[currentPos]);
            std::swap(blue[(currentPos+1)%4] , blue[currentPos]);
            currentPos=(currentPos+1)%4; break;
        case GLUT_KEY_RIGHT:
            system(path[currentPos]); break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(200,200);
	glutCreateWindow("Just Window");
    glClearColor(1.0,0.37,0.28,1.0);


	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutSpecialFunc(keySpecial);

	glutMainLoop();

	return 1;
}
