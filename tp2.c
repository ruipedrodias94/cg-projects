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



//---------------------------------------------------------------------------
//-------------------------------------------------------  Variaveis globais
//---------------------------------------------------------------------------

GLfloat wC=10.0, hC=10.0;		    //.. coordenadas reais/mundo

GLfloat wSup=4.0, hSup=1.0;			//.. dimensoes do suporte
GLfloat wLig=0.8, hLig=4.0;			//.. dimensoes da ligacao
GLfloat wExt=1.0, hExt=3.0;			//.. dimensoes da extremidade

GLfloat xSup=0.0,  incSup=0.45;		//.. posicao horizontal do suporte / incremento para deslocamento
GLfloat agLig=0.0,  incLig=6.0;		//.. angulo  da ligacao / incremento para rotacao em graus
GLfloat agExt=90.0, incExt=8.0;		//.. angulo  da extremidade / incremento para rotacao

GLfloat qx=0, qy=10;				//.. posicao do quadrado que cai
GLfloat tam=0.5;					//.. tamanho do quadrado
GLfloat incX=0.10, incY=0.05;		//.. incremento (deslocacao) em cada timer
GLint   msec=10;					//.. definicao do timer (actualizacao)

char texto[30];						//.. texto a ser escrito no ecran
GLint  tentativas=0;				//.. numero de blocos gerados
GLint  apanhados=0;				    //.. apanhdos pela extremidade
GLint  embates=0;				    //.. embates na base

//NOTA: Podera' ser necessario incluir outras variaveis globais
GLfloat matrizModelView[3][3];

//-----------------------------------------------------------------------------------
//  inicializa (definicoes iniciais: cor de fundo/cor para apagar, limites do mundo,
//                             tipo de interpolacao de cor, etc )
//-----------------------------------------------------------------------------------

void inicializa(void){

	glClearColor (0, 0, 0, 1); //Cor de fundo/cor para limpar o  buffer
	gluOrtho2D(-wC,wC,-hC,hC); //Define os limites do mundo 2D/planos de recorte verticais e horizontais
	glShadeModel(GL_SMOOTH); //Define GL_SMOOTH (Gouraud shading) como tipo de shading/interpolacao de cor
	srand(1); //inicia o gerador pseudo-aleatorio (semente=1)
}


//-----------------------------------------------------------------------------------
//  aleatorio (devolve um real no intervalo [minimimo, maximo[ )
//
//-----------------------------------------------------------------------------------

float aleatorio(GLint minimo, GLint maximo){

    GLfloat y;

    y = rand()%1000;
	return (minimo+ 0.001*y*(maximo-minimo));
}

//---------------------------------------------------------------------------
//desenhaQuadrado (desenha um quadrado
//                 tam: tamanho dos lados
//                 (x,y): vertice inferior esquerdo
//                 (r,g,b): cor de preenchimento)
//---------------------------------------------------------------------------
void desenhaQuadrado(GLfloat x, GLfloat y, GLfloat tam,
					 GLfloat r, GLfloat g, GLfloat b            )
{
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
		glVertex2f(x   , y+tam );
		glVertex2f(x   , y    );
		glVertex2f(x+tam, y    );
		glVertex2f(x+tam, y+tam );
	glEnd();
}


//---------------------------------------------------------------------------
//desenhaTexto (escreve/desenha texto
//              string: texto a escrever
//              (x,y): onde (comeca a) escrever (coordenadas do mundo))
//---------------------------------------------------------------------------
void desenhaTexto(char *string, GLfloat x, GLfloat y)
{
	glRasterPos2f(x,y);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}


//---------------------------------------------------------------------------
//desenhaBracoArticulado (desenha o braco articulado/robot)
//
//NOTA: os argumentos desta funcao possuem a mesma descricao que as variaveis globais
//      homonimas
//---------------------------------------------------------------------------

void desenhaBracoArticulado(GLfloat xSup, GLfloat agLig, GLfloat agExt){

	glPushMatrix();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Suporte vermelho
		glColor3f(1,0,0);
	    glTranslatef (xSup, 0.0, 0.0);
		glPushMatrix();
			glScalef (wSup, hSup, 1.0);
			glutSolidCube(1.0); //desenha um cubo com lados de tamanho 1 e centrado na origem
            //NOTA: o glutSolidCube poderia ter sido substituido por uma primitiva GL_QUADS
		glPopMatrix();

		//TODO: - desenhar Ligacao verde
		//      - desenhar Extremidade azul
		//      - determinar a localização da extremidade (Px = ??, Py=??)
		//        DICA: consultar/usar a matriz modelview (GL_MODELVIEW)

    //Ligacao
    glColor3f(0,1,0);
    glRotatef(agLig, 0.0, 0.0, 1.0);
    //Se não se fizer a translação de mais de metade, ele fica centrado com o mesmo centro
    // Do quadrado vermelho
    glTranslatef(0.0, hLig/2, 0.0);

    glPushMatrix();
      glScalef(wLig, hLig, 1.0);
      glutSolidCube(1.0);
    glPopMatrix();

    //Extremidade
    glColor3f(0,0,1);
    glTranslatef(0.0, hLig/2, 0.0);
    glRotatef(agExt , 0.0, 0.0, 1.0);

    glPushMatrix();
      glScalef(wExt, hExt, 1.0);
      glutSolidCube(1.0);
      glTranslatef(hLig, 0.0, 0.0);
      glRotatef(0.0, 0.0, 0.0, 0.0);
    glPopMatrix();

    glGetFloatv(GL_MODELVIEW_MATRIX, &matrizModelView[0][0]);

	glPopMatrix();
}





//----------------------------------------------------------------------------------------
//timer (temporizador/funcao de callback)
//----------------------------------------------------------------------------------------

void timer(int value)
{

    //TODO: actualizar a posicao do quadrado que cai
    //NOTAS: - sempre que o quadrado atinge o fundo
    //            -> o numero de tentativas e' incrementado de uma unidade
    //            -> um novo quadrado e' gerado no topo (coordenada x aleatoria)
	  //       - usar incx e incy para actualizar a posicao do quadrado
    //       - O topo e os limites laterais sao paredes
    //            -> se o quadrado atingir o topo, o incremento em y passa ao simetrico
    //            -> se o quadrado atingir os limites laterais, o incremento em x passa ao simetrico

	glutPostRedisplay();
	glutTimerFunc(msec,timer, 1);
}


//-----------------------------------------------------------------------------------
//....................................................................Eventos teclado
//------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
//teclasNotASCII (funcao de callback)
//Programacao de teclas para deslocar o suporte e rodar a ligacao
//----------------------------------------------------------------------------------------
void teclasNotAscii(int key, int x, int y)
{
	if(key == GLUT_KEY_LEFT) {
		xSup= xSup- incSup;
		glutPostRedisplay();
	}
	if(key == GLUT_KEY_RIGHT) {
		xSup= xSup+ incSup;
		glutPostRedisplay();
	}
	if(key == GLUT_KEY_DOWN) {
		agLig= (int) (agLig - incLig) % 360;
		glutPostRedisplay();
	}
	if(key == GLUT_KEY_UP) {
		agLig= (int) (agLig + incLig) % 360;
		glutPostRedisplay();
	}
}


//----------------------------------------------------------------------------------------
//teclado (funcao de callback)
//Programacao de teclas para rodar a extremidade e terminar o programa
//----------------------------------------------------------------------------------------

void teclado (unsigned char key, int x, int y){

	switch (key) {
	  case 'q':
      agExt -= incExt;
      break;
    case 'a':
      agExt += incExt;
      break;

	case 27:
		exit(0);
		break;
	default:
		break;
	}
}



//----------------------------------------------------------------------------------------
//  desenhaCena (funcao callback de desenho (principal)/desenho da cena)
//----------------------------------------------------------------------------------------
void desenhaCena(void){

	int i,j;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~limpa
	glClear (GL_COLOR_BUFFER_BIT);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~BracoArticulado
	desenhaBracoArticulado(xSup, agLig, agExt);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Quadrado a cair
	desenhaQuadrado(qx,qy,tam,1,1,0);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Grelha de pontos
	glColor3f(1,1,1);
	glBegin(GL_POINTS);
		for (i=-wC;i<wC;i++)
			for (j=-hC;j<hC;j++)
				glVertex2f(i,j);
	glEnd();


	//TODO: Deteccao de colisoes
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Regras do jogo :  Apanha / embate
	//   - apanha - o quadrado bate na extremidade
	//   - embate - o quadrado bate na base
	//   - o jogo termina quando embates>apanha+3




	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Texto/Informacao
	sprintf(texto, "Tentativas = %d", tentativas);
	desenhaTexto(texto, -wC+1, hC-3);
	sprintf(texto, "Embates   = %d", embates);
	desenhaTexto(texto, -wC+1, hC-2);
	sprintf(texto, "Apanhados = %d", apanhados);
	desenhaTexto(texto, -wC+1, hC-1);



	glColor3f(1.0,1.0,1.0);
	char t[]="{pjmm,jpa}@dei.uc.pt";
	desenhaTexto(t, -wC+0.2, -hC+0.2);


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Actualiza cena/troca buffers
	glutSwapBuffers();
}



//---------------------------------------------------------------------------
//.............................................................. Main
//---------------------------------------------------------------------------
int main(int argc, char** argv){
	glutInit(&argc, argv); //===1:Inicia janela
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); //Double mode (duplo buffer), modelo RBG
	glutInitWindowSize (500, 500);  //dimensoes (pixeis)
	glutInitWindowPosition (300, 100); //localizacao da janela
	glutCreateWindow ("Combate Final [Teclas: left, right, up, down, q, a]");//criacao da janela

	inicializa (); //===2:Inicia estado/parametros

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //===3:Registo de callbacks

  glutDisplayFunc(desenhaCena); //desenho
	glutKeyboardFunc(teclado); //eventos de teclado
	glutSpecialFunc(teclasNotAscii); //eventos de teclado
	glutTimerFunc(msec, timer, 1); //temporizador

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  glutMainLoop();    //===4:Inicia processamento

	return 0;
}
