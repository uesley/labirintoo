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
} Traffic;

void add_Space(Traffic * traffic, Space * space)
{
	
	if (!traffic->first_space) {
        traffic->first_space = space;
        space->next = space;
        return;
    }
    Space * last = traffic->first_space;
	while(last->next != traffic->first_space) {
		last = last->next;
	}
    last->next = space;
	space->next = traffic->first_space;
}

void rotateTraffic(Traffic * traffic, Space * space)
{
	traffic->first_space = space;
}


void new_Traffic(Traffic * traffic)
{   
    int num_spaces = 1 + rand() % 3;
    int band = 120/num_spaces;
    int last_x = 0;
    int i;
    Space * space;
   
    traffic->num_spaces = num_spaces;
    traffic->speed = 1 + rand() % 5;
    traffic->first_space = NULL;

    for (i = 0; i < traffic->num_spaces; i++) {
        last_x += last_x + 15 + rand() % band;
        space = malloc(sizeof(Space));
        new_Space(space, last_x);
        add_Space(traffic, space);
    }
}


void describe_space(Space space) {
    printf("%d <--> %d", space.x_start, space.x_final);
}


void describe_traffic(Traffic traffic)
{
    printf("speed: %d\n", traffic.speed);
    Space * space;
    int i;
    
    for (i =0, space = traffic.first_space; i < traffic.num_spaces; i++, space= space->next){
        describe_space(*space);
        printf("  ");
    }
    printf("\n");
}



#endif /* SCENARIO_H */

