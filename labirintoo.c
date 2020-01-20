#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "Labirintilt.h"
#include <GL/glut.h>
#define LEVELS 8

#define RESOLUTION 80
void Desenha();

/// COLORS
float CorObstaculo[4] = { 0, 0, 1, 1};
float CorPlayer[4] = { 1, 0, 0, 1};
int page = 0;
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
    
	glClearColor(1, 1, 1, 1);

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

// FunÃ§Ã£o callback chamada quando o tamanho da janela ï¿½ alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{

	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleï¿½ï¿½o (esquerda, direita, inferior,
	// superior)
	gluOrtho2D (0.0f, 120.0f, 0.0f, 45.0f);
}

void alerta(char* mensagem, char * titulo) {
	MessageBox(NULL, mensagem, titulo,  MB_OK);
}

void game_over()
{
   alerta("Você perdeu, tente novamente", "Alerta");
   page = 0;
}

// Funï¿½ï¿½o callback chamada para gerenciar eventos de teclas
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

void paginaAjuda() {
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(53,38,0);
    glScalef(0.015, 0.015, 0.015); // diminui o tamanho do fonte
    glLineWidth(1.3); // define a espessura da linha
    DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Instrucoes");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25,35,0);
    glScalef(0.011, 0.011, 0.011);
    glLineWidth(1); // define a espessura da linha
    DesenhaTextoStroke(GLUT_STROKE_ROMAN,"O objetivo do jogo e chegar do outro lado da via, evitando o contato com os obstaculos.");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25,33,0);
    glScalef(0.011, 0.011, 0.011);
    glLineWidth(1); // define a espessura da linha
    DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Voce tem 3 tentativas para isso.");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25,27,0);
    glScalef(0.011, 0.011, 0.011);
    glLineWidth(1); // define a espessura da linha
    DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Para controlar o player utilize as teclas direcionais do teclado ou as teclas: 'a', 'w', 'd' e 's'");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25,21,0);
    glScalef(0.011, 0.011, 0.011);
    glLineWidth(1); // define a espessura da linha
    DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Para sair do menu Instrucoes pressione o botao direito do mouse, e escolha a opção desejada.");
    glPopMatrix();
    //Executa os comandos OpenGL para renderizaÃ§Ã£o.
//    glutMainLoop();
//    system("pause");
}

void paginainicial(void){
    glClearColor(0.0, 0.0, 0.0, 1);
    glPushMatrix();
    glColor3f(.439200, 0.858800, 0.858800);
    glTranslatef(15,28,0);
    glScalef(0.05, 0.05, 0.05);
    glLineWidth(2); // define a espessura da linha
    DesenhaTextoStroke(GLUT_BITMAP_TIMES_ROMAN_24,"     LABIRINTILT");
    glPopMatrix();
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(0,21,0);
    glScalef(0.02, 0.02, 0.02);
    glLineWidth(1); // define a espessura da linha
    DesenhaTextoStroke(GLUT_BITMAP_TIMES_ROMAN_24,"                        NOVO JOGO");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.5,17,0);
    glScalef(0.02, 0.02, 0.02);
    DesenhaTextoStroke(GLUT_BITMAP_TIMES_ROMAN_24,"                         AJUDA");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.75,13,0);
    glScalef(0.02, 0.02, 0.02);
    DesenhaTextoStroke(GLUT_BITMAP_TIMES_ROMAN_24,"                          SAIR");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(35,34,0);
    glScalef(2, 2, 2);
    glColor3f(.45, 0.86, 0.86);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(6,0,0);
    glVertex3f(6,1,0);
    glVertex3f(0,1,0);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(38,36.5,0);
    glScalef(2, 2, 2);
    glColor3f(.4, 0.4, 1);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(6,0,0);
    glVertex3f(6,1,0);
    glVertex3f(0,1,0);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(31,39,0);
    glScalef(2, 2, 2);
    glColor3f(.45, 0.86, 0.86);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(6,0,0);
    glVertex3f(6,1,0);
    glVertex3f(0,1,0);
    glEnd();
    glPopMatrix();
    glFlush();
    glutMainLoop();
}

void MenuPrincipal(int op) {
    page = op;
    if (op == 1) {
    	game.level = 1;
    	game.player.lives = 3;
    	reset_position_player(&game.player);
	}
}

void CriaMenu()
{
    int menu;

    menu = glutCreateMenu(MenuPrincipal);
    glutAddMenuEntry("Menu",4);
    glutAddMenuEntry("Novo jogo",1);
    glutAddMenuEntry("Ajuda",2);
    glutAddMenuEntry("Sair",3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void DesenhaTextoStroke(void *font, char *string)
{
	// Exibe caractere a caractere
	while(*string)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++);
}

void Mouse(int button, int state,int x, int y){
	int level = y/5;
	float vermelho = rand()/(float)RAND_MAX;
	float verde = rand()/(float)RAND_MAX;
	float azul = rand()/(float)RAND_MAX;

    /*if(button != GLUT_RIGHT_BUTTON){
        return;
    }

    CorObstaculo[0] = vermelho;
	CorObstaculo[1] = verde;
	CorObstaculo[2] = azul;
	CorPlayer[0] = verde;
	CorPlayer[1] = azul;
	CorPlayer[2] = vermelho;

	glClearColor(azul, vermelho, verde, 1.0f);
    */
	if (button == GLUT_RIGHT_BUTTON){
        if (state == GLUT_DOWN){
            CriaMenu();
        }
    }
    if(button == GLUT_LEFT_BUTTON){
            printf("(%i,%i)\n",x,y);
        if(x>(565) && x <(746)){
            if(y>(240) && y <(268)){
                MenuPrincipal(1);
            }
            if(y>285 && y <312){
                MenuPrincipal(2);
            }
            if(y>330 && y <355){
                MenuPrincipal(3);
            }
        }
    }

	glutPostRedisplay();
}

void teclado (unsigned char key, int x, int y)
{
	switch(key){
		case 'a':
			move_player_left(&game.player);
			break;
		case 'w':
			move_player_up(&game.player);
			if (win(game)) {
    			next_level(&game);
    			muda_cor_fase();
			}
			break;
		case 'd':
			move_player_right(&game.player);
			break;
		case 's':
			move_player_down(&game.player);
			break;
		case 27:
			if (page) {
				page = 0;
				return;
			}
			exit(0);
	}
}

// Funï¿½ï¿½o responsï¿½vel por inicializar parï¿½metros e variï¿½veis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualizaï¿½ï¿½o como branca
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

void Desenha()
{
    glClear(GL_COLOR_BUFFER_BIT);
    switch(page) {
    	case 1:
			desenha_cenario(game.traffics, 4);
    		desenha_player(game.player);
    		break;
    	case 2:
    		paginaAjuda();
    		break;
    	case 3:
    		exit(0);
    	default:
    		paginainicial();   	
	}
	
    glFlush();
}

int main()
{
   new_Game(&game);

	// Define do modo de operaï¿½ï¿½o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posiï¿½ï¿½o inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(3*450,500);
// 	gluOrtho2D (0.0f, 45.0f, 0.0f, 45.0f);

	// Cria a janela passando como argumento o tï¿½tulo da mesma
	glutCreateWindow("Labirintilt");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	// Registra a funï¿½ï¿½o callback de redimensionamento da janela de visualizaï¿½ï¿½o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a funï¿½ï¿½o callback para tratamento das teclas ASCII
	glutMouseFunc(Mouse);
	glutSpecialFunc(moves);
    // Registra a funï¿½ï¿½o callback de redesenho da janela de visualizaï¿½ï¿½o
	glutDisplayFunc(Desenha);

	glutKeyboardFunc (teclado);
	glutTimerFunc(1000/RESOLUTION ,Timer,1);

	// Chama a funï¿½ï¿½o responsï¿½vel por fazer as inicializaï¿½ï¿½es
	Inicializa();

	// Inicia o processamento e aguarda interaï¿½ï¿½es do usuï¿½rio
	glutMainLoop();

	return 0;
}
