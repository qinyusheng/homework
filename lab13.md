# 贪吃蛇实验报告

## 会动的蛇 

### 设计思路
### 能动的蛇设计思路 

采用自上而下的程序设计方法
- 首先按照伪代码（如图一）编写出程序主体的**main**函数，只需设计出基础的结构，不必关注各个功能实现的细节，下一层的函数来解决。
图一：![](images/wei_1.png)

- 按照主函数的需要，为各个功能编写实现的函数：
    - **void snake_move (int dy , int dx)** 函数，用于根据读取到的数据，通过改变贪吃蛇身体各部位的位置（**snake_X** , **snake_Y**），实现贪吃蛇的移动
    - **void output(void)** 函数，首先清空控制台上已有的图像，再按照数组**map**以及**snake_X** 、 **snake_Y**的值打印出游戏地图以及贪吃蛇
    - **void gameover(void)** 打印游戏结束界面
    - 这一层级的一些功能譬如：判断贪吃蛇是否死亡等等，可以不予关注，留给下一层
- 根据上一层的需要编写合适的函数，例如：
    - **int if_dead(void)**，用于判断蛇移动后是否死亡
    - **int eat_itself(void)**，用于判断贪吃蛇移动是否会咬到自己，即头部与身体重合
- 为整个代码设计一个合格的程序头，导入所需的函数库，预先声明好函数和全局变量。

### 实验代码
具体的代码请点击这一页面：[(win 10)snake_move.c](snake_move.c)


### 效果展示
![](images/snake_move.gif)

## 会吃东西的蛇

###设计思路
要让我们的贪吃蛇能够吃到食物并长大，我们只需要以上方**能动的蛇**的代码为基础进行改造，增加一些函数来实现特定功能，如下
- **void eat_food(int dx , int dy)** 我们使用这一函数让贪吃蛇在吃到食物后能够变长，并且保持移动  
具体代码如下：
~~~
/*贪吃蛇吃食物*/
void eat_food(int dx , int dy){
	snake_length ++;
	snake_X[snake_length - 1] = snake_X[snake_length - 2] + dx;
	snake_Y[snake_length - 1] = snake_Y[snake_length - 2] + dy;
	produce_food();
}
~~~
- **void produce_food(void)** 在地图上的空白处随机生成食物，在上一个函数执行完后（即食物被吃后）执行。这里需要使用到随机数的知识，我在上网查阅过相关知识后设计出了如下程序：
~~~
/*随机生成食物*/
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
~~~

- 当然，简单地增加函数还不足以成功改造程序，为了让程序能够成功运行，并实现我们需要地功能，我们还需要对其他地函数如：**void snake_move (int dy , int dx)**
与**void output(void)** 等。

### 实验代码
改造后代码如下：[(win 10)snake_eat.c](snake_eat.c)


### 效果展示
![](images/snake_eat_2.gif)

## 优化输入
在上面的代码中我们使用，函数**getchar()** 读取玩家的输入，但是每次输入后都必须按下回车才能让程序开始执行。这严重影响了我们的游戏体验，因此，为了让输入更加方便，我引入了老师提供的几个函数：
- **int tty_reset(void)**
- **int tty_set(void)** 
- **int kbhit(void)**

并修改了原本的输入方式：
- 原：
~~~
input = getchar();
~~~
- 现：
~~~
if( kbhit() ){
	input = go_next();
}
~~~  
如此便可直接读取键盘的输入，不必输入回车。但是，如果仅仅做出这样的改造，你会发现你的蛇将会迅速一头撞到墙上。因为计算机的运行速度太快，进行一次循环的时间实在太短，我们没法进行操作。因此我们还需要让程序慢下来。
此处我使用了**Linux**环境下<**unistd.h**> 库中的 **sleep**。在**Windows**环境下，可以使用 <**windows.h**> 库中的**Sleep**函数，注意第一个字母需要大写。  
另外，**Linux**的**sleep**括号中的单位是**秒**，而**Windows**中**Sleep**括号中的单位为**毫秒**。  
我们在while的函数块的末尾使用了**sleep**函数，使程序在此处停顿一秒。就可以让蛇的移动慢下来，一秒只走一步。  

~~~
/*linux*/
sleep(1);
/*Windows*/
Sleep(1000);
~~~

### 实验代码
最终，优化过后的蛇的代码如下：[(linux)snake.c](snake.c)

