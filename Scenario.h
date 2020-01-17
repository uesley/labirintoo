#ifndef SCENARIO_H
#define SCENARIO_H

typedef struct S_space{
    int x_start;
    int x_final;
    struct S_space * next;
} Space;

void new_Space(Space * space, int x1);

void new_Space(Space * space, int x1)
{
    space->x_start = x1;
    space->x_final = x1 +15;
    space->next = NULL;
}

typedef struct {
    int num_spaces;
    int speed;
    Space * first_space;
    Space * last_space;
    Space * spaces;
} Traffic;

void add_Space(Traffic * traffic, Space * space)
{
    if (!traffic->spaces) {
        traffic->spaces = space;
        traffic->first_space = space;
    } else {
        traffic->last_space->next = space;
    }
    traffic->last_space = space;
}


void new_Traffic(Traffic * traffic)
{   
    int num_spaces = 1 + rand() % 5;
    int band = 120/num_spaces;
    int last_x = 0;
    int i;
    Space * space;
    
    traffic->num_spaces = num_spaces;
    traffic->speed = 1 + rand() % 5;
    traffic->spaces = NULL;

    for (i = 0; i < traffic->num_spaces; i++) {
        last_x += last_x +  rand() % band;
        space = malloc(sizeof(Space));
        new_Space(space, last_x);
        add_Space(traffic, space);
    }
}


void describe_space(Space space){
    printf("%d <--> %d", space.x_start, space.x_final);
}


void describe_traffic(Traffic traffic)
{
    printf("speed: %d\n", traffic.speed);
    Space * i;
    for (i = traffic.first_space; i; i = i->next){
        describe_space(*i);
        printf("  ");
    }
    printf("\n");
}



#endif /* SCENARIO_H */

