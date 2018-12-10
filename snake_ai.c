/* ̰�����ƶ�*/

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

/* ����̰��������*/
#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
/* ������Ϸ��ͼԪ��*/ 
#define WALL '*'
#define FOOD '$'


/* ��Ϸ��ͼ*/
char map[12][12] = 
{"************",
"*XXXXH     *",
"*          *",
"*          *",
"*          *",
"*          *",
"*          *",
"*          *",
"*          *",
"*          *",
"*          *",
"************" 
 };  
 
/* �����ߵĳ�ʼ״̬*/
int snake_length = 5; 
int snake_X[SNAKE_MAX_LENGTH] = {1 , 2 , 3 , 4 , 5};
int snake_Y[SNAKE_MAX_LENGTH] = {1 , 1 , 1 , 1 , 1}; 
/*ʳ��ĵ�ַ*/
int food_X = 8;
int food_Y = 7; 

/* ̰�����ƶ���dy = -1�����ϣ� / 1�����£�  �� dx = -1������/ 1�����ң� �� 0�����ƶ��� */
void snake_move (int dy , int dx);
/* ��ӡ��ͼ��*/
void output(void);
/*��Ϸ��������*/
void gameover(void);
/* �ж���Ϸ�Ƿ����*/
int if_dead(void); 
/* �ж����Ƿ�ҧ���Լ�*/
int eat_itself(void); 
/*�߳Ե�ʳ���*/
void eat_food(int dx , int dy);
/*����ʳ��*/
void produce_food(void); 
/*ͣ��һ��ʱ��*/
void stop(clock_t wait);
/*�����ߵ�����*/
int food_head_ins(int x , int y);/*��ͷ��ʳ��ľ���*/
int get_ins(char ch);/*�����ƶ���һ����������������µľ���*/ 
char go_next(void);/*�ߵ��ƶ�����*/
 

/*������*/ 
int main(){
	char input = 'd';/*��������*/ 
	output();/*��ӡ����ʼ��ͼ
	 ��ʽ��ʼ��Ϸ*/ 
	while(if_dead()){
		/*��ȡ��������ָ��*/ 
			input = go_next();
		
		/* ʶ��ִ��ָ�� */
		switch(input){
			case 'A':
			case 'a':
				snake_move(0 , -1);
				break;
			case 'D':
			case 'd':
				snake_move(0 , 1);
				break;
			case 'W':
			case 'w':
				snake_move(-1 , 0);
				break;
			case 'S':
			case 's':
				snake_move(1 , 0);
				break;
			case '#':
				gameover();
				return 0;
			default:
				break;
		}
		output();/* ��ӡִ�й�ָ���ĵ�ͼ */
		sleep(1);
	} 
	gameover();/* ��ӡ��Ϸ��������*/
    return 0;
} 
int if_dead(){
	if(snake_X[snake_length - 1] == 0 || snake_X[snake_length - 1] == 11 
	|| snake_Y[snake_length - 1] == 0 || snake_Y[snake_length - 1] == 11)
		return 0;
	if(eat_itself())
		return 0;
	return 1;
}

int eat_itself(){
	int i , j;
	for(i = 0 ; i < snake_length ; i ++){
		for( j = i + 1 ; j < snake_length ; j ++)
			if(snake_X[i] == snake_X[j] && snake_Y[i] == snake_Y[j])
				return 1;
	}
	return 0;
}	

void snake_move(int dy , int dx){
	/* �ж�̰�����ܷ�����ƶ� */
	if(map[(snake_Y[snake_length - 1] + dy)][(snake_X[snake_length - 1] + dx)] == '$'){
		eat_food(dx , dy);
		return;
	}
	if((snake_X[snake_length - 1] + dx )== snake_X[snake_length - 2]
		&& (snake_Y[snake_length - 1] + dy) == snake_Y[snake_length - 2])
		return;
	int i; 
	for(i = 0 ; i < snake_length - 1 ; i ++){
		snake_X[i] = snake_X[i + 1];
		snake_Y[i] = snake_Y[i + 1];
	}
	snake_X[snake_length - 1] += dx;
	snake_Y[snake_length - 1] += dy;
	return;
}

void output(){
	int x , y , i , j;

	printf("\033[2J");
	for( x = 0 ; x < 12 ; x ++ ){
		for( y = 0 ; y < 12 ; y ++){
			if( x == 0 || x == 11 || y == 11 || y == 0)
				map[x][y] = '*';
			else 
				map[x][y] = ' ';
		}
	}
	map[food_Y][food_X] = '$';
	for( i = 0 ; i < snake_length - 1 ; i ++ ){
			map[snake_Y[i]][snake_X[i]] = 'X';
		map[snake_Y[snake_length - 1]][snake_X[snake_length - 1]] = 'H'; 
	}
	/*���´�ӡҳ��*/ 
	for( i = 0 ; i < 12 ; i ++ ){
		for( j = 0 ; j < 12 ; j ++ ){
			printf("%c",map[i][j]);
		}
		printf("\n");
	}
}

void gameover(){
	printf("\nEND!\n");
	return;
}

void eat_food(int dx , int dy){
	snake_length ++;
	snake_X[snake_length - 1] = snake_X[snake_length - 2] + dx;
	snake_Y[snake_length - 1] = snake_Y[snake_length - 2] + dy;
	produce_food();
}

void produce_food(){
	srand((unsigned)time(0));
	while(1){
		food_X = rand()%12;
		food_Y = rand()%12;
		if(map[food_Y][food_X] == ' '){
			break;
		}
	}
} 

void stop(clock_t wait){
	clock_t time_0;
	time_0 = wait + clock();
	while(time_0 > clock());
}


int food_head_ins(int x , int y){
	int a = x - food_X;
	int b = y - food_Y;
	if(a < 0) a = 0 - a;
	if(b < 0) b = 0 - b;
	return (a + b);
}

int get_ins(char ch){
	int i;
	int head_X = snake_X[snake_length - 1];
	int head_Y = snake_Y[snake_length - 1];
	switch(ch){
		case 'w':
			head_X += 0;
			head_Y -= 1;
			break;
		case 'a':
			head_X -= 1;
			head_Y += 0;
			break;
		case 's':
			head_X += 0;
			head_Y += 1;
			break;
		case 'd':
			head_X += 1;
			head_Y += 0;
			break;
		default:
			break;
	}
	for(i = 0 ; i < snake_length ; i ++ ){
		if(snake_Y[i] == head_Y &&
			snake_X[i] == head_X)
		return 9999;
	}
	if(map[head_X][head_Y] == ' '){
		return food_head_ins(head_X , head_Y);
	}
	return 9999;
}

char go_next(void){
	int i;
	int id , min = 100000;
	char direction[4] = { 'w' , 'a' , 's' , 'd' };
	int instance[4] = {0};
	for( i = 0 ; i < 4 ; i ++ ){
		instance[i] = get_ins(direction[i]);
	}
	for( i = 0 ; i < 4 ; i ++ ){
		if(instance[i] < min){
			min = instance[i];
			id = i;
		}
	}
	if(direction[id] >= 9999){
		return '#';
	}
	return direction[id];
} 

