#ifndef SCENARIO_H
#define SCENARIO_H

typedef struct {
    int x_start;
    int x_final;
} Space;

void new_Space(Space * space, int x1);

void new_Space(Space * space, int x1)
{
    space->x_start = x1;
    space->x_final = x1 +15;
}

typedef struct {
    int num_spaces;
    int speed;
    Space * spaces;
} Traffic;

void new_Traffic(Traffic * traffic)
{
    traffic->num_spaces = 1 + rand() % 5;
    traffic->spaces = malloc(sizeof(Space) * traffic->num_spaces);
    traffic->speed = 1 + rand() % 5;
    int i;
    int tam_aux = 30;
    int last_x = 0;
    for (i = 0; i < traffic->num_spaces; i++) {
        last_x += 10 +  rand() % tam_aux;
        new_Space(&traffic->spaces[i], last_x);
    }
}


void describe_space(Space space){
    printf("%d <--> %d", space.x_start, space.x_final);
}


void describe_traffic(Traffic traffic)
{
    printf("speed: %d\n", traffic.speed);
    int i;
    for (i = 0; i < traffic.num_spaces; i++){
        describe_space(traffic.spaces[i]);
        printf("  ");
    }
    printf("\n");
}



#endif /* SCENARIO_H */

