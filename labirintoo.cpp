//*****************************************************
//
// Casa.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e desenha uma casa.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <windows.h>
#include <stdlib.h>
#include<stdio.h>
#include <GL/glut.h>
void DesenhaObstaculos();
void DesenhaPlayer();
int colidiu();
// Função callback de redesenho da janela de visualização

#define LEVELS 8

typedef struct {
   int x1;
   int x2; 	
} Obstaculo;

typedef struct {
   int x;
   int y;
   int lives; 	
} Player;

Player player;
Obstaculo obstaculos[LEVELS/2];

void inicializaObstaculos() {
	int xs[LEVELS] = {
		5,15,
		115,120,
		0,10,
		18, 25,
		};
	int i;
	for (i =0; i< LEVELS/2; i++ ) {
		obstaculos[i].x1 =xs[i*2];
		obstaculos[i].x2 = xs [i*2+1];
	}
}

void resetPlayerPosition() {
	player.x = 60;
	player.y = 0;
}

void inicializaPlayer() {
	player.lives = 3;
	resetPlayerPosition();
}

void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha uma casinha composta de um quadrado e um triângulo

	// Altera a cor do desenho para azul
	DesenhaObstaculos();
	DesenhaPlayer();

	// Altera a cor do desenho para branco
//	glColor3f(1.0f, 1.0f, 1.0f);  
//	// Desenha a porta e a janela  
//	glBegin(GL_QUADS);
//		glVertex2f(-4.0f,-14.5f);
//		glVertex2f(-4.0f,  0.0f);       
//		glVertex2f( 4.0f,  0.0f);       
//		glVertex2f( 4.0f,-14.5f);       
//		glVertex2f( 7.0f,-5.0f);
//		glVertex2f( 7.0f,-1.0f);       
//		glVertex2f(13.0f,-1.0f);       
//		glVertex2f(13.0f,-5.0f);             
//	glEnd();
//
//	// Altera a cor do desenho para azul
//	glColor3f(0.0f, 0.0f, 1.0f);     
//	// Desenha as "linhas" da janela  
//	glBegin(GL_LINES);      
//		glVertex2f( 7.0f,-3.0f);      
//		glVertex2f(13.0f,-3.0f);       
//		glVertex2f(10.0f,-1.0f);    
//		glVertex2f(10.0f,-5.0f);             
//	glEnd();    
//
//	// Altera a cor do desenho para vermelho
//	glColor3f(1.0f, 0.0f, 0.0f); 
//	// Desenha o telhado
//	glBegin(GL_TRIANGLES);
//		glVertex2f(-15.0f, 5.0f);   
//		glVertex2f(  0.0f,17.0f);    
//		glVertex2f( 15.0f, 5.0f);       
//	glEnd();
// 
	// Executa os comandos OpenGL 
	glFlush();
}

void DesenhaObstaculos() {
	int level;
	int x1;
	int x2;
	int i;
	int y;
	glColor3f(0.0f, 0.0f, 1.0f);     
	
	for (i=0; i<LEVELS/2; i++){
		level = i * 2 + 1;
		y = level * 5;
		x1 = obstaculos[i].x1;
		x2 = obstaculos[i].x2;
		printf("%d %d\n", x1, x2);
		glBegin(GL_QUADS);
			glVertex2f(x1, y);
			glVertex2f(x1, y + 5);       
			glVertex2f( 0,  y + 5);       
			glVertex2f( 0, y);
			
			glVertex2f(120, y);
			glVertex2f(120, y + 5);       
			glVertex2f( x2,  y + 5);       
			glVertex2f( x2, y);
		glEnd();			
	}
}

void DesenhaPlayer() {
	
	glColor3f(1.0f, 0.0f, 0.0f);     
	
	glBegin(GL_QUADS);
		glVertex2f(player.x, player.y);
		glVertex2f(player.x + 5, player.y);       
		glVertex2f( player.x + 5, player.y + 5);       
		glVertex2f( player.x, player.y + 5);	
	glEnd();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	if (largura <= altura) 
		gluOrtho2D (0.0f, 120.0f, 0.0f*altura/largura, 40.0f*altura/largura);
	else 
		gluOrtho2D (0.0f*largura/altura, 120.0f*largura/altura, 0.0f, 40.0f);
}

// Função callback chamada para gerenciar eventos de teclas
void moves (int key, int x, int y)
{
		
	switch(key) {
		case GLUT_KEY_UP: 
			printf("cima");
			if (player.y < 40){
				player.y += 5;
			}
			printf("%d \n", player.y);
			break;
		case GLUT_KEY_DOWN: 
			printf("baixo");
			if (player.y > 0){
				player.y -= 5;
			}
			break;
		case GLUT_KEY_LEFT: 
			if (player.x > 0) { 
				player.x -= 5;
			}
			break;
		case GLUT_KEY_RIGHT: 
			if (player.x < 115) { 
				player.x += 5;
			}
			break;
		case 27:
			exit(0);
	}	
	Desenha();
	if (colidiu()) {
		resetPlayerPosition();
		player.lives--;
		printf("vidas :%d\n", player.lives);
		if (!player.lives){
			printf("morreu de verdade agora!!");
			exit(0);
		}
	}
	Desenha();
}

void Mouse(int button, int state,int x, int y){
    if(button == GLUT_RIGHT_BUTTON){
        glClearColor(rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,rand()/(float)RAND_MAX, 1.0f);
        glutPostRedisplay();
    }
}

int colidiu()
{
	int level = player.y / 5;
	if (level % 2 == 0) {
		return 0;
	}
	
	if ((obstaculos[level/2].x1 > player.x) || (obstaculos[level/2].x2 < player.x + 5)){
		printf("bagaçou tudo\n");
		return 1;
	}

	return 0;
}


void teclado (unsigned char key, int x, int y)
{
		
	if (key == 27)
		exit(0);
}
// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Programa Principal 
int main(void)
{
	inicializaObstaculos();

	inicializaPlayer();	
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(3*450,450); 
 	gluOrtho2D (0.0f, 40.0f, 0.0f, 40.0f);
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Desenho de uma casa");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas ASCII
	glutMouseFunc(Mouse);
	glutSpecialFunc(moves);

	glutKeyboardFunc (teclado);    
	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
