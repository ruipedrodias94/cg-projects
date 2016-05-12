/* ===================================================================================
    Departamento Eng. Informatica - FCTUC
    Computacao Grafica - 2015/16
    ................................................... PMartins/JArrais
    Trabalho 1 - George Nelson's Asterisk Clock (codigo incompleto)

    Completar as zonas assinaladas com comentarios TODO
======================================================================================= */


//.................................................... Bibliotecas necessarias
#include <stdlib.h>
#include <time.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//.................................................... Variaveis

GLint   msecDelay=20;                   //definicao do timer (frequencia de actualizacao em milissegundos)

struct tm *current_time; //tempo actual
GLint hour, minute, second; //horas, minutos e segundos actuais




//-----------------------------------------------------------------------------------
//  Init (definicoes iniciais: cor de fundo/cor para apagar, limites do mundo,
//                             tipo de interpolacao de cor, etc )
//-----------------------------------------------------------------------------------
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);   //....  Cor para apagar (branco)
    gluOrtho2D(-400, 400, -400, 400);       //....  Definicao sistema coordenadas/ area de desenho
    glShadeModel(GL_FLAT);              //....  Interpolacao de cor com base na cor dos vertices

}



//-----------------------------------------------------------------------------------
//  drawRectangle (desenha um rectangulo preenchido a preto)
//-----------------------------------------------------------------------------------
void drawRectangle()
{

    glColor3f(0.0,0.0,0.0);

    glRotatef(30,0,0,1);

    glBegin(GL_POLYGON); //Neste caso, poderia ser GL_QUADS em vez de GL_POLYGON
        glVertex2f(-30,300);
        glVertex2f(30,300);
        glVertex2f(30,-300);
        glVertex2f(-30,-300);
    glEnd();
}



//-----------------------------------------------------------------------------------
//  drawAsterisk (desenha a base do relogio (asterisco) a partir do drawRectangle)
//-----------------------------------------------------------------------------------
void drawAsterisk()
{
    int i;
   //TODO: desenhar o asterisco a partir da funcao drawRectangle
    glPushMatrix();
    for (i = 0; i <=6; i++)
    {
        drawRectangle();
    }
    glPopMatrix();

}


//-----------------------------------------------------------------------------------
//  drawHoursHand (desenha o ponteiro das horas a marcar 12 horas )
//-----------------------------------------------------------------------------------
void drawHoursHand()
{

    GLfloat angle = 0.5* (60 * hour +minute);
    glPushMatrix();
    glColor3f(0.96,0.96,0.96);
    glRotatef(-angle,0.0,0.0,1);
    glBegin(GL_POLYGON); //Neste caso, poderia ser GL_QUADS em vez de GL_POLYGON
        glVertex2f(-13, -20);
        glVertex2f(13, -20 );
        glVertex2f(4, 130);
        glVertex2f(-4, 130);
    glEnd();
    glPopMatrix();
}


//-----------------------------------------------------------------------------------
//  drawMinsHand (desenha o ponteiro dos minutos a marcar 0 minutos )
//-----------------------------------------------------------------------------------
void drawMinsHand()
{

    GLint angle = (360/60) * minute;

    glPushMatrix();

    glColor3f(0.96,0.96,0.96);

    glRotatef(-angle,0.0,0.0,1);

    glBegin(GL_POLYGON); //Neste caso, poderia ser GL_QUADS em vez de GL_POLYGON
        glVertex2f(-13, -20);
        glVertex2f(13, -20 );
        glVertex2f(4, 140);
        glVertex2f(-4, 140);
    glEnd();

    glBegin(GL_POLYGON); //Neste caso, poderia ser GL_TRIANGLES em vez de GL_POLYGON
        glVertex2f(-50, 140);
        glVertex2f(50, 140);
        glVertex2f(0, 190 );
    glEnd();

    glPopMatrix();

}




//------------------------------------------------------------------------------------
//  drawSecsHand (desenha o ponteiro dos segundos a marcar 0 segundos )
//-----------------------------------------------------------------------------------
void drawSecsHand()
{
    GLint angle = (360/60)*second;

    glPushMatrix();

    glColor3f(1.0,0.0,0.0);

    glRotatef(-angle, 0.0, 0.0, 1);

    glBegin(GL_POLYGON); //Neste caso, poderia ser GL_QUADS em vez de GL_POLYGON
        glVertex2f(-12, -20);
        glVertex2f(12, -20 );
        glVertex2f(3, 140);
        glVertex2f(-3, 140);
    glEnd();
    glPopMatrix();
}



//----------------------------------------------------------------------------------------
//  getTime (permite obter os horas, minutos e segundos, a partir do relógio do sistema)
//---------------------------------------------------------------------------------------
void getTime()
{


    time_t timer = time(0);
    current_time = localtime(&timer);
    hour = current_time->tm_hour;
    minute = current_time->tm_min;
    second = current_time->tm_sec;

}

void keyboard(unsigned char key, int x, int y)
{

    switch (key){

    case 27:                    //tecla ESCAPE
        exit(0);
        break;
    }
}


//----------------------------------------------------------------------------------------
//  draw (funcao callback de desenho (principal)/desenho da cena)
//----------------------------------------------------------------------------------------
void draw(void)
{
    //TODO: desenhar os ponteiros das horas, minutos e segundos
    //      NOTA:     a cada instante que a cena e' desenhada, os
    //                ponteiros devem indicar o tempo dado
    //                pelo relogio do sistema


    glClear(GL_COLOR_BUFFER_BIT);           //....  Apaga ecra


    getTime();

    drawAsterisk();

    drawHoursHand();

    drawMinsHand();

    drawSecsHand();

    glutSwapBuffers();             //.. actualiza ecra
}


//----------------------------------------------------------------------------------------
//timer (temporizador/funcao de callback)
//----------------------------------------------------------------------------------------
void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(msecDelay,timer, 1);
}


//-----------------------------------------------------------------------------------
//MAIN
//-----------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     glutInit(&argc, argv);                         //===1:Inicia janela
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //Double mode (duplo buffer), modelo RBG
     glutInitWindowSize(600,500);                   //dimensoes (pixeis)
     glutInitWindowPosition(200,100);               //localizacao da janela
     glutCreateWindow("George Nelson's Asterisk Clock");//criacao da janela

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     init();                                    //===2:Inicia estado/parametros

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                    //===3:Registo de callbacks
     glutDisplayFunc(draw);                         //desenho
     glutKeyboardFunc(keyboard);                    //eventos teclado
     glutTimerFunc(msecDelay,timer, 1);             //temporizador
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     glutMainLoop();                                //===4:Inicia processamento


    return 0;
}
