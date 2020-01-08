#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/glut.h>
#define FAIXAS 8

void DesenhaObstaculos();
void DesenhaPlayer();
int colidiu();
void inicializaPlayer();
void inicializaTraffics();
void inicializaObstaculos();


int holes = 2;

typedef struct {
   int x1;
   int x2; 	
} Obstaculo;

typedef struct {
   int x;
   int y;
   int lives; 	
} Player;

typedef struct {
	int spaces;
	int speed;
	int direction;
	Obstaculo obstaculos *;
} Traffic;

typedef struct {
	int level;
	Traffic traffics[FAIXAS/2];
	Player player;
} Game;

Player player;
Game game;

Obstaculo obstaculos[FAIXAS/2];
float CorObstaculo[3] = { 0, 0, 1};
float CorPlayer[3] = { 1, 0, 0};


void inicializaGame() {
	game.level = 1;
	inicializaPlayer();
	inicializaTraffics();
}

void incializaTraffics() {
	int i;
	for (i = 0; i < FAIXAS/2; i ++) {
		game.traffics[i].spaces = 1 + rand() % 5;
		game.traffics[i].speed = game.level * 2 * (1 + rand() % 20) ;
		game.traffics[i] = malloc(sizeof(Obstaculo) );
	}
}

void inicializaObstaculos() {
	int xs[FAIXAS];
	int i;
	srand(time(NULL));
	for (i = 0; i <= FAIXAS; i+=2) {
		xs[i] = rand() % 120;
		xs[i+1] = xs[i] + 15;
	}
	
	for (i = 0; i< FAIXAS/2; i++ ) {
		obstaculos[i].x1 =xs[i*2];
		obstaculos[i].x2 = xs [i*2+1];
	}
}

void resetPlayerPosition() {
	game.player.x = 60;
	game.player.y = 0;
}

void inicializaPlayer() {
	game.player.lives = 3;
	resetPlayerPosition();
}

void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	DesenhaObstaculos();
	DesenhaPlayer();
	glFlush();
}

void DesenhaObstaculos() {
	int level;
	int x1;
	int x2;
	int i;
	int y;
	glColor3f(CorObstaculo[0], CorObstaculo[1], CorObstaculo[2]);     
	
	for (i=0; i<FAIXAS/2; i++){
		level = i * 2 + 1;
		y = level * 5;
		x1 = obstaculos[i].x1;
		x2 = obstaculos[i].x2;
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
	
	glColor3f(CorPlayer[0], CorPlayer[1], CorPlayer[2]);     
	
	glBegin(GL_QUADS);
		glVertex2f(player.x, player.y);
		glVertex2f(player.x + 5, player.y);       
		glVertex2f( player.x + 5, player.y + 5);       
		glVertex2f( player.x, player.y + 5);	
	glEnd();
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{

	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior, 
	// superior)
	gluOrtho2D (0.0f, 120.0f, 0.0f, 40.0f);
}

void alerta(char* mensagem, char * titulo) {
	MessageBox(NULL, mensagem, titulo,  MB_OK);
}
// Fun��o callback chamada para gerenciar eventos de teclas
void moves (int key, int x, int y)
{
		
	switch(key) {
		case GLUT_KEY_UP: 
			player.y += 5;
			if (player.y > 35){
				alerta("YOU WON!!", ":)");
				exit(0);
			}
			break;
		case GLUT_KEY_DOWN: 
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
		if (!player.lives){
			alerta("GAME OVER", ":(");
			exit(0);
		}
	}
	Desenha();
}

void Mouse(int button, int state,int x, int y){
	int level = y/5;
	float vermelho = rand()/(float)RAND_MAX;
	float verde = rand()/(float)RAND_MAX;
	float azul = rand()/(float)RAND_MAX;

    if(button != GLUT_RIGHT_BUTTON){
        return;
    }
    
    
    CorObstaculo[0] = vermelho;
	CorObstaculo[1] = verde;
	CorObstaculo[2] = azul;
	CorPlayer[0] = verde;
	CorPlayer[1] = azul;
	CorPlayer[2] = vermelho;
	
	glClearColor(azul, vermelho, verde, 1.0f);				
	
	glutPostRedisplay();
}

int colidiu()
{
	int level = player.y / 5;
	if (level % 2 == 0) {
		return 0;
	}
	
	return((obstaculos[level/2].x1 > player.x) || (obstaculos[level/2].x2 < player.x + 5));
}


void teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}
// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void timer(int value) {
	int i;
	for (i =0; i< FAIXAS/2; i++ ) {
		obstaculos[i].x1 = (obstaculos[i].x1 + 5 + 4*i) % 120;
		obstaculos[i].x2 = (obstaculos[i].x2 + 5 + 4*i) % 120;
	}
	
	glutPostRedisplay();
	glutTimerFunc(500, timer, value++);
	if (colidiu()) {
		resetPlayerPosition();
		player.lives--;
		if (!player.lives){
			alerta("GAME OVER", ":(");
			exit(0);
		}
	}
}


// Programa Principal 
int main(void)
{	
	inicializaObstaculos();

	inicializaPlayer();	
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(3*450,450); 
 	gluOrtho2D (0.0f, 40.0f, 0.0f, 40.0f);
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Labirintoo");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutMouseFunc(Mouse);
	
	glutSpecialFunc(moves);

	glutKeyboardFunc (teclado);   
	
	glutTimerFunc(500, timer, 1); 
	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
