/* ̰�����ƶ�*/

#include <stdio.h>
#include <stdlib.h>

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


int main(){
	char input;/*��������*/ 
	output();/*��ӡ����ʼ��ͼ
	 ��ʽ��ʼ��Ϸ*/ 
	while(if_dead()){
		input = getchar();/*��ȡ��������ָ��*/ 
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
			default:
				break;
		}
		output();/* ��ӡִ�й�ָ���ĵ�ͼ */
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
	system("cls");/*���ҳ��*/
	int x , y , i , j;
	for( x = 0 ; x < 12 ; x ++ ){
		for( y = 0 ; y < 12 ; y ++){
			if( x == 0 || x == 11 || y == 11 || y == 0)
				map[x][y] = '*';
			else 
				map[x][y] = ' ';
		}
	}
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
	system("cls");
	printf("END!");
	return;
}
