/* ===================================================================================
 Departamento Eng. Informatica - FCTUC
 Computacao Grafica - 2015/16
 ................................................... PMartins/JArrais
 Trabalho 2 - Combate Final (codigo incompleto)
 
 Completar as zonas assinaladas com comentarios TODO
 ======================================================================================= */

//.................................................... Bibliotecas necessarias............

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

 

GLfloat LARANJA[] = {1,0.5,0,0};


 //Variáveis Globais
 GLdouble w = 800;
 GLdouble h = 600;


/*Função de inicialização*/
 void init(void){
 	glClearColor(0,0,0,1);
 	gluOrtho2D(-400, 400, -400, 400);       //....  Definicao sistema coordenadas/ area de desenho
    glShadeModel(GL_FLAT);              //....  Interpolacao de cor com base na cor dos vertices
 }

 /*Desenha objecto*/
 void desenhaObjecto(){

 }

 /*Desenhar o Teapot*/
 void drawTeapot(){
 	GLfloat
	bule=0.5;
	GLfloat
	buleP[]= {3, 0, 3};
	glTranslatef(buleP[0], buleP[1], buleP[2]);
	glColor4f(LARANJA[0],LARANJA[1],LARANJA[2],LARANJA[3]);
	glutSolidTeapot (bule);
 }


int main(int argc, char  **argv)
{

	glutInit(&argc, argv);
	//Janela de visualização
	glViewport( 0, 0, (GLsizei) w, (GLsizei) h ); //Coordenadas do ecrã

	//Projeção
	glMatrixMode( GL_PROJECTION ); //Indica que a matriz activa é a matriz de projeccão
	glLoadIdentity( ); //Carrega a matriz identidade/Transforma a matriz activa na identidade
	gluPerspective( 65.0, (GLdouble) w / h, 1.0, 100.0 ); //Define uma projecção perspectiva

	//Observador
	glMatrixMode( GL_MODELVIEW ); //A matriz activa é a modelview
	glLoadIdentity();
	gluLookAt( 0.0,0.0,5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 ); //observador: onde está, para onde
	// olha e qual a direcção do up vector.

	//Cena
	glTranslatef(0,0,5);
	glRotatef(23, 0,1,0);
	glScalef(1,1.4,2);

	glEnable(GL_BLEND);

	init();

	drawTeapot();
	return 0;
}