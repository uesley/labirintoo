//#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "Labirintilt.h"
//#include <GL/glut.h>
#define LEVELS 8

/// COLORS
float CorObstaculo[3] = { 0, 0, 1};
float CorPlayer[3] = { 1, 0, 0};

void desenha_retangulo(int x1, int x2, int y)
{
//  glBegin(GL_QUADS);
//      glVertex2f(x1, y + 5);
//	glVertex2f(x1, y);       
//	glVertex2f(x2, y);       
//	glVertex2f(x2, y + 5);
//  glEnd();
}

void set_color(float color[3]) {
//    glColor3f(color[0], color[1], color[2]);
}

void desenha_cenario(Traffic traffics, int tam)
{
    int i;
    int j;
    Traffic traffic;
    Obstacle obstacle;
    set_color(CorObstaculo);
    for (i = 0; i < tam; i ++) {
        traffic = traffics[i];
        for (j = 0; j < traffic.num_obstacles; j ++) {
            desenha_retangulo(obstacle.x_start, obstacle.x_final, (i + 1) * 5);
        }
    }
}

void desenha_player(Player player) {
    set_color(CorPlayer);
    desenha_retangulo(player.x, player.x + 5, player.y);
}

void Desenha()
{
//    glClear(GL_COLOR_BUFFER_BIT);
    desenha_cenario();
    desenha_player();
//    glFlush();
}

// Função callback chamada quando o tamanho da janela � alterado 
//void AlteraTamanhoJanela(GLsizei w, GLsizei h)
//{
//
//	glViewport(0, 0, w, h);
//
//	// Inicializa o sistema de coordenadas
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	// Estabelece a janela de sele��o (esquerda, direita, inferior, 
//	// superior)
//	gluOrtho2D (0.0f, 120.0f, 0.0f, 40.0f);
//}

//void alerta(char* mensagem, char * titulo) {
//	MessageBox(NULL, mensagem, titulo,  MB_OK);
//}

//// Fun��o callback chamada para gerenciar eventos de teclas
//void moves (int key, int x, int y)
//{
//		
//	switch(key) {
//		case GLUT_KEY_UP: 
//			player.y += 5;
//			if (player.y > 35){
//				alerta("YOU WON!!", ":)");
//				exit(0);
//			}
//			break;
//		case GLUT_KEY_DOWN: 
//			if (player.y > 0){
//				player.y -= 5;
//			}
//			break;
//		case GLUT_KEY_LEFT: 
//			if (player.x > 0) { 
//				player.x -= 5;
//			}
//			break;
//		case GLUT_KEY_RIGHT: 
//			if (player.x < 115) { 
//				player.x += 5;
//			}
//			break;
//		case 27:
//			exit(0);
//	}	
//	Desenha();
//	if (colidiu()) {
//		resetPlayerPosition();
//		player.lives--;
//		if (!player.lives){
//			alerta("GAME OVER", ":(");
//			exit(0);
//		}
//	}
//	Desenha();
//}

//void Mouse(int button, int state,int x, int y){
//	int level = y/5;
//	float vermelho = rand()/(float)RAND_MAX;
//	float verde = rand()/(float)RAND_MAX;
//	float azul = rand()/(float)RAND_MAX;
//
//    if(button != GLUT_RIGHT_BUTTON){
//        return;
//    }
//    
//    
//    CorObstaculo[0] = vermelho;
//	CorObstaculo[1] = verde;
//	CorObstaculo[2] = azul;
//	CorPlayer[0] = verde;
//	CorPlayer[1] = azul;
//	CorPlayer[2] = vermelho;
//	
//	glClearColor(azul, vermelho, verde, 1.0f);				
//	
//	glutPostRedisplay();
//}
//
//int colidiu()
//{
//	int level = player.y / 5;
//	if (level % 2 == 0) {
//		return 0;
//	}
//	
//	return((obstaculos[level/2].x1 > player.x) || (obstaculos[level/2].x2 < player.x + 5));
//}
//
//
//void teclado (unsigned char key, int x, int y)
//{
//	if (key == 27)
//		exit(0);
//}
//// Fun��o respons�vel por inicializar par�metros e vari�veis
//void Inicializa (void)
//{   
//	// Define a cor de fundo da janela de visualiza��o como branca
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//}

// Programa Principal 

Game game;

int main()
{
    new_Game(&game);
    
//    describe_player(game.player);
//    describe_scenario(game);
    
    
//	inicializaObstaculos();
//
//	inicializaPlayer();	
//	// Define do modo de opera��o da GLUT
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//
//	// Especifica a posi��o inicial da janela GLUT
//	glutInitWindowPosition(5,5); 
//
//	// Especifica o tamanho inicial em pixels da janela GLUT
//	glutInitWindowSize(3*450,450); 
// 	gluOrtho2D (0.0f, 40.0f, 0.0f, 40.0f);
// 
//	// Cria a janela passando como argumento o t�tulo da mesma
//	glutCreateWindow("Labirintoo");
//
//	// Registra a fun��o callback de redesenho da janela de visualiza��o
//	glutDisplayFunc(Desenha);
//
//	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
//	glutReshapeFunc(AlteraTamanhoJanela);
//
//	// Registra a fun��o callback para tratamento das teclas ASCII
//	glutMouseFunc(Mouse);
//	glutSpecialFunc(moves);
//
//	glutKeyboardFunc (teclado);    
//	// Chama a fun��o respons�vel por fazer as inicializa��es 
//	Inicializa();
//
//	// Inicia o processamento e aguarda intera��es do usu�rio
//	glutMainLoop();

	return 0;
}
