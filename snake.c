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

static struct termios ori_attr, cur_attr;

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
/*�޼��ʶ���������*/
static __inline int tty_reset(void);
static __inline int tty_set(void); 
static __inline int kbhit(void);
/*ͣ��һ��ʱ��*/
void stop(clock_t wait);


int main(){
	char input = 'd';/*��������*/ 
	output();/*��ӡ����ʼ��ͼ
	 ��ʽ��ʼ��Ϸ*/ 
	while(if_dead()){
		/*��ȡ��������ָ��*/ 
		if( kbhit() ){
			input = getchar();
		}
		
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


static __inline 
int tty_reset(void)
{
        if (tcsetattr(STDIN_FILENO, TCSANOW, &ori_attr) != 0)
                return -1;

        return 0;
}


static __inline
int tty_set(void)
{
        
        if ( tcgetattr(STDIN_FILENO, &ori_attr) )
                return -1;
        
        memcpy(&cur_attr, &ori_attr, sizeof(cur_attr) );
        cur_attr.c_lflag &= ~ICANON;
//        cur_attr.c_lflag |= ECHO;
        cur_attr.c_lflag &= ~ECHO;
        cur_attr.c_cc[VMIN] = 1;
        cur_attr.c_cc[VTIME] = 0;

        if (tcsetattr(STDIN_FILENO, TCSANOW, &cur_attr) != 0)
                return -1;

        return 0;
}

static __inline
int kbhit(void) 
{
                   
        fd_set rfds;
        struct timeval tv;
        int retval;

        /* Watch stdin (fd 0) to see when it has input. */
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        /* Wait up to five seconds. */
        tv.tv_sec  = 0;
        tv.tv_usec = 0;

        retval = select(1, &rfds, NULL, NULL, &tv);
        /* Don't rely on the value of tv now! */

        if (retval == -1) {
                perror("select()");
                return 0;
        } else if (retval)
                return 1;
        /* FD_ISSET(0, &rfds) will be true. */
        else
                return 0;
        return 0;
}

void stop(clock_t wait){
	clock_t time_0;
	time_0 = wait + clock();
	while(time_0 > clock());
}
