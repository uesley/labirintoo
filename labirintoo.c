#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "Labirintilt.h"
#include <GL/glut.h>
#define LEVELS 8

#define RESOLUTION 100

/// COLORS
float CorObstaculo[4] = { 0, 0, 1, 1};
float CorPlayer[4] = { 1, 0, 0, 1};
Game game;

void desenha_retangulo(int x1, int x2, int y)
{
	glBegin(GL_QUADS);
    	glVertex2f(x1, y + 5);
    	glVertex2f(x1, y);       
		glVertex2f(x2, y);       
		glVertex2f(x2, y + 5);
	glEnd();
}

void set_color(float color[4]) {
    glColor4f(color[0], color[1], color[2], color[3]);
}

void desenha_cenario(Traffic * traffics, int tam)
{
    int i;
    int j;
    Traffic traffic;
    Space * space;
    Space inicio;
    Space fim;
    
    set_color(CorObstaculo);
    
    new_Space(&inicio, -15);
    new_Space(&fim, 120);

    for (i = 0; i < tam; i ++) {
        traffic = traffics[i];
        inicio.next = traffic.first_space;
        for (space = &inicio, j = 0; j < traffic.num_spaces ; j++, space = space->next) {
            if (space->x_final < 0 || space->x_start > 120) {
                continue;
            }
            desenha_retangulo(space->x_final, space->next->x_start, 5 + i*10 );
        }
        desenha_retangulo(space->x_final, 120, 5 + i*10 );
    }
}

void desenha_player(Player player) {
	if (player.lives  < 4 ){
		CorPlayer[3] = 1.0 / (4 - player.lives);
	}
    set_color(CorPlayer);
    desenha_retangulo(player.x, player.x + 5, player.y);
}

void Desenha()
{
    glClear(GL_COLOR_BUFFER_BIT);
    desenha_cenario(game.traffics, 4);
    desenha_player(game.player);
    glFlush();
}

// Função callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{

	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior, 
	// superior)
	gluOrtho2D (0.0f, 120.0f, 0.0f, 45.0f);
}

void alerta(char* mensagem, char * titulo) {
	MessageBox(NULL, mensagem, titulo,  MB_OK);
}

void game_over()
{
	alerta("Deu ruim, tente novamente", "Alerta");
    exit(0);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void moves (int key, int x, int y)
{
    move_player(key - GLUT_KEY_LEFT, &game.player);
    Desenha();
    if (colision(game) && !survive(&game)) {
        game_over();
    }
    if (win(game)) {
    	next_level(&game);
    	muda_cor_fase();
	}
//    Desenha();
}

void muda_cor_fase() {
	float vermelho = rand()/(float)RAND_MAX;
	float verde = rand()/(float)RAND_MAX;
	float azul = rand()/(float)RAND_MAX;
	CorObstaculo[0] = vermelho;
	CorObstaculo[1] = verde;
	CorObstaculo[2] = azul;
	
//	CorPlayer[0] = verde;
//	CorPlayer[1] = azul;
//	CorPlayer[2] = vermelho;
	
	glutPostRedisplay();
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

void teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

void Inicializa (void)
{   
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


int speed_min = 1;

void Timer(int i) 
{
    int K = RESOLUTION/(10 * game.level);
    if (i >= K) {
        move_scenario(&game, speed_min);
        speed_min = (++speed_min) % 5;
        i = 1;
    }
    
    glutPostRedisplay();
    Desenha();
     if (colision(game) && !survive(&game)) {
        game_over();
    }
    glutTimerFunc(1000/RESOLUTION ,Timer, i + game.level);
}

int main()
{	
   new_Game(&game);
    
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(5,5); 

	glutInitWindowSize(3*450,500); 
// 	gluOrtho2D (0.0f, 45.0f, 0.0f, 45.0f);
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Labirintilt");
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutMouseFunc(Mouse);
	glutSpecialFunc(moves);

	glutKeyboardFunc (teclado);    
	glutTimerFunc(1000/RESOLUTION ,Timer,1);
	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
