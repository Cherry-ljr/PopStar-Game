#include "cv.h"
#include "highgui.h"

#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

#define N 10
int mpt[N][N];
int dir[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
int visited[N][N] = { 0 };
int cnt = 0;

struct node{
	int x, y;
}Q[N*N];

IplImage *img_background;
IplImage *img_green;
IplImage *img_blue;
IplImage *img_red;
IplImage *img_purple;
IplImage *img_yellow;
IplImage *img_over;


void print(){

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << mpt[i][j] << " ";

		}
		cout << endl;
	}

}

int check(){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			for (int k = 0; k < 4; k++){
				int tx = i + dir[k][0];
				int ty = j + dir[k][1];
				if (tx >= 0 && ty >= 0 && tx < N&&ty < N){
					if (mpt[i][j] == mpt[tx][ty] && mpt[i][j]!=0)
						return 1;
				
				}
			}
		}

	}
	return 0;
}
void find(int x, int y){

	for (int i = 0; i < 4; i++){
		int tx = x + dir[i][0];
		int ty = y + dir[i][1];
		if (tx >= 0 && ty >= 0 && tx < N&&ty < N){
			if (mpt[tx][ty] == mpt[x][y] && visited[tx][ty] == 0) {
				visited[tx][ty] = 1;
				Q[cnt].x = tx;
				Q[cnt].y = ty;
				cnt++;
				find(tx, ty);
			}
		}
	}
}


void Move()
{
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++)
		{
			if (mpt[i][j] == 0){
				for (int k = i; k >= 0; k--)
				{
					if (k != 0) mpt[k][j] = mpt[k - 1][j];
					else  mpt[k][j] = 0;
				}
			}
		}
	}
	for (int j = N - 1; j >= 0; j--){
		int flag = 0;
		for (int i = 0; i < N; i++)
		{
			if (mpt[i][j] != 0) flag = 1;
		}
		if (flag == 0) {
			for (int k = j; k < N; k++)
			{
				for (int i = 0; i < N; i++)
				{
					if (k != N - 1) mpt[i][k] = mpt[i][k + 1];
					else mpt[i][k] = 0;
				}

			}
		}
	}
}

void clear(){
	if (cnt < 2) return;
	cout << "cnt:" << cnt << endl;
	for (int i = 0; i < cnt; i++)
		mpt[Q[i].x][Q[i].y] = 0;
	Move();

}

void init() {
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
	{
		mpt[i][j] = rand() % 5 + 1;
	}

	img_background = cvLoadImage("C:\\Users\\Administrator\\Desktop\\background.png");
	img_green = cvLoadImage("C:\\Users\\Administrator\\Desktop\\green.png");
	img_blue = cvLoadImage("C:\\Users\\Administrator\\Desktop\\blue.png");
	img_red = cvLoadImage("C:\\Users\\Administrator\\Desktop\\red.png");
	img_purple = cvLoadImage("C:\\Users\\Administrator\\Desktop\\purple.png");
	img_yellow = cvLoadImage("C:\\Users\\Administrator\\Desktop\\yellow.png");
	img_over = cvLoadImage("C:\\Users\\Administrator\\Desktop\\gameover.png");
}
/*
int main(){



	Q[cnt].x = 3;
	Q[cnt].y = 3;
	cnt++;
	visited[x][y] = 1;

	print();
	cout << endl << endl;
	find(x, y);
	clear();

	print();


	return 0;

}
*/


int btn_x = -1;
int btn_y = -1;

void OnMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)//表示鼠标左键按下
	{
		printf("xy %d %d\n", x, y);
		btn_y = y / 30;
		if (y % 30 != 0) btn_y++;
		btn_x = x / 30;
		if (x % 30 != 0) btn_x++;
	}
}

void DrawImage() {
	img_background = cvLoadImage("C:\\Users\\Administrator\\Desktop\\background.png");
	int px = 0;
	int py = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << mpt[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int color = mpt[i][j];
			px = j * 30;
			py = i * 30;
			if (color == 1) {
				for (int x = 0; x<img_green->height; x++)
				{
					for (int y = 0; y<img_green->width; y++)
					{
						int r, g, b;
						r = CV_IMAGE_ELEM(img_green, uchar, y, 3 * x);
						g = CV_IMAGE_ELEM(img_green, uchar, y, 3 * x + 1);
						b = CV_IMAGE_ELEM(img_green, uchar, y, 3 * x + 2);

						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px)) = r;
						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px) + 1) = g;
						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px) + 2) = b;

					}
				}
			}
			if (color == 2) {
				for (int x = 0; x<img_blue->height; x++)
				{
					for (int y = 0; y<img_blue->width; y++)
					{
						int r, g, b;
						r = CV_IMAGE_ELEM(img_blue, uchar, y, 3 * x);
						g = CV_IMAGE_ELEM(img_blue, uchar, y, 3 * x + 1);
						b = CV_IMAGE_ELEM(img_blue, uchar, y, 3 * x + 2);

						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px)) = r;
						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px) + 1) = g;
						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px) + 2) = b;

					}
				}
			}
			if (color == 3) {
				for (int x = 0; x<img_red->height; x++)
				{
					for (int y = 0; y<img_red->width; y++)
					{
						int r, g, b;
						r = CV_IMAGE_ELEM(img_red, uchar, y, 3 * x);
						g = CV_IMAGE_ELEM(img_red, uchar, y, 3 * x + 1);
						b = CV_IMAGE_ELEM(img_red, uchar, y, 3 * x + 2);

						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px)) = r;
						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px) + 1) = g;
						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px) + 2) = b;

					}
				}
			}
			if (color == 4) {
				for (int x = 0; x<img_purple->height; x++)
				{
					for (int y = 0; y<img_purple->width; y++)
					{
						int r, g, b;
						r = CV_IMAGE_ELEM(img_purple, uchar, y, 3 * x);
						g = CV_IMAGE_ELEM(img_purple, uchar, y, 3 * x + 1);
						b = CV_IMAGE_ELEM(img_purple, uchar, y, 3 * x + 2);

						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px)) = r;
						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px) + 1) = g;
						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px) + 2) = b;

					}
				}
			}
			if (color == 5) {
				for (int x = 0; x<img_yellow->height; x++)
				{
					for (int y = 0; y<img_yellow->width; y++)
					{
						int r, g, b;
						r = CV_IMAGE_ELEM(img_yellow, uchar, y, 3 * x);
						g = CV_IMAGE_ELEM(img_yellow, uchar, y, 3 * x + 1);
						b = CV_IMAGE_ELEM(img_yellow, uchar, y, 3 * x + 2);

						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px)) = r;
						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px) + 1) = g;
						CV_IMAGE_ELEM(img_background, uchar, (y + py), 3 * (x + px) + 2) = b;

					}
				}
			}


		}
	}



}

int main(int argc, char* argv[])
{
	int sum=0;
	init();//初始化mpt数组, 背景图片，星星图片

	cvNamedWindow("ljr", 1);
	
	
	DrawImage();
	cvShowImage("ljr", img_background);
	cvSetMouseCallback("ljr", OnMouse);//回调函数
	while (1) {
		btn_x = -1;
		btn_y = -1;
		int key = cvWaitKey(50);
		if (btn_x != -1 && btn_y != -1) {
			btn_x--;
			btn_y--;
			int temp = btn_x;
			btn_x = btn_y;
			btn_y = temp;
			cout << btn_x << " " << btn_y << endl;
			cnt = 0;
			Q[cnt].x = btn_x;
			Q[cnt].y = btn_y;
			cnt++;
			memset(visited, 0, sizeof(visited));
			visited[btn_x][btn_y] = 1;
			find(btn_x, btn_y);
			sum = sum + 10*cnt;
			clear();
			cout << sum << endl;
			DrawImage();
			cvShowImage("ljr", img_background);
			if (check() == 0)
				break;
		}
	}
	char str[10];//一个变量存放将分数强制转化成字符型的数据
	itoa(sum, str, 10);//将int型的数据转化为char型并存放在str字符数组中
	char *text = str;//定义一个指针text指向字符数组、因为cvputtext函数只接受char型指针
	CvPoint p;//定义一个位置点
	CvScalar p_color;
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_DUPLEX, 1.0f, 1.0f, 0, 1, CV_AA);//设置字体
	p_color.val[0] = 255;//设置颜色的RGB值、可以自己百度
	p_color.val[1] = 0;
	p_color.val[2] = 255;
	p.x = 150;//设置在屏幕显示的坐标
	p.y = 80;
	cvPutText(img_over, text, p, &font, p_color);//然后调用函数显示
	

	cvShowImage("ljr", img_over);
	cvWaitKey(0);
	cvDestroyWindow("ljr");
	
	return 0;
}