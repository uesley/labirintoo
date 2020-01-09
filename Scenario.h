#ifndef SCENARIO_H
#define SCENARIO_H

typedef struct {
    int x_start;
    int x_final;
} Obstacle;

void new_Obstacle(Obstacle * obstacle, int x1, int x2);

void new_Obstacle(Obstacle * obstacle, int x1, int x2)
{
    obstacle->x_start = x1;
    obstacle->x_final = x2;
}

typedef struct {
    int num_obstacles;
    int speed;
    Obstacle * obstacles;
} Traffic;

void new_Traffic(Traffic * traffic)
{
    traffic->num_obstacles = 1 + rand() % 5;
    traffic->obstacles = malloc(sizeof(Obstacle) * traffic->num_obstacles);
    traffic->speed = 1 + rand() % 5;
    int i;
    int tam_aux = 120 / traffic->num_obstacles;
    int last_x = 0;
    for (i = 0; i < traffic->num_obstacles; i++) {
        last_x += rand() % tam_aux;
        new_Obstacle(&traffic->obstacles[i], last_x, last_x + 15);
    }
}

void describe_obstacle(Obstacle obstacle){
    printf("%d <--> %d", obstacle.x_start, obstacle.x_final);
}


void describe_traffic(Traffic traffic)
{
    printf("speed: %d\n", traffic.speed);
    int i;
    for (i = 0; i < traffic.num_obstacles; i++){
        describe_obstacle(traffic.obstacles[i]);
        printf("  ");
    }
    printf("\n");
}



#endif /* SCENARIO_H */

