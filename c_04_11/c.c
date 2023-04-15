#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define MAZE_SIZE 10
int Stacksize = 10;
typedef struct {
    short r;
    short c;
} element;
typedef struct {
    element* s_tack;
    int top;
}stackType;

char maze[MAZE_SIZE][MAZE_SIZE] = {
        {'1','1','1','1','1','1','1','1','1','1'},
        {'e','1','0','1','0','0','0','1','0','1'},
        {'0','0','0','1','0','0','0','1','0','1'},
        {'0','1','0','0','0','1','1','0','0','1'},
        {'1','0','0','0','1','0','0','0','0','1'},
        {'1','0','0','0','1','0','0','0','0','1'},
        {'1','0','0','0','0','0','1','0','1','1'},
        {'1','0','1','1','1','0','1','1','0','1'},
        {'1','1','0','0','0','0','0','0','0','x'},
        {'1','1','1','1','1','1','1','1','1','1'}
};

element here = { 1,0 }, entry = { 1,0 };

int boolean = 0, number = 0;

int is_empty(stackType* s) {
    return (s->top == -1);
}
int is_full(stackType* s) {
    return (s->top == (Stacksize - 1));
}
void push(stackType* s, element* e) {
    if (is_full(s)) {
        //fprintf(stderr, "\nfull. \n");
        Stacksize *= 2;
        s->s_tack = realloc(s->s_tack, Stacksize * sizeof(element));
        if (s->s_tack == NULL) {
            fprintf(stderr, "�޸� �Ҵ� ����");
            exit(1);
        }
        
    }
      ++s->top;
      s->s_tack[s->top].r = e->r;
      s->s_tack[s->top].c = e->c;
    
}
// here�� �������־����.
element pop(stackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "empty. \n");
        exit(1);
    }
    else {
        element tmp;
        tmp.r = s->s_tack[s->top].r;
        tmp.c = s->s_tack[s->top].c;
        s->top--;
        return  tmp;//s->s_tack[s->top--];
    }

}
void push_loc(stackType* s, int r, int c) {
    if (r < 0 || c < 0) return;
    if (maze[r][c] != '1' && maze[r][c] != '.') {

        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, &tmp);
    }
    else boolean++;

}
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
    printf("\n");

    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
    printf("\n------------------------\n");
}
void intit_stack(stackType* s) {
    s->s_tack = malloc(Stacksize * sizeof(element));
    if (s->s_tack == NULL) {
        printf("stack NULL");
        exit(1);
    }
    s->top = -1;
}
element peek(stackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else return s->s_tack[s->top];
}
int main(void) {
    int r, c;
    stackType s;

    intit_stack(&s);
    here = entry;
    while (maze[here.r][here.c] != 'x') {

        r = here.r;
        c = here.c;

        maze[r][c] = '.';
        maze_print(maze);
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);

        if (is_empty(&s)) {
            printf("����\n");
            return 0;
        }
        //�̵�
        else {
            //���� ��������
            if (boolean == 4) 
                number++;

            
            here = pop(&s);
        }
        boolean = 0;
    }
    printf("����\n���ư� Ƚ���� %d", number);
    free(s.s_tack);
  

    return 0;
}