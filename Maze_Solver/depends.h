#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
constexpr int W_Width = 1600;
constexpr int W_Height = 900;
constexpr int box_dimensions = 20;
constexpr int row = W_Width / box_dimensions;
constexpr int col = W_Height / box_dimensions;

using namespace sf;

typedef struct cell {
	RectangleShape box;
	int wall;
	int visited;
}cell;
cell matrix[row][col];

typedef struct element {
	int r;
	int c;
}element;
element stack[row*col] = { 0 }, cpy_stack[row*col] = { 0 };
int top = -1, top_2 = -1;

Clock cl;
Time dt;	//delta time
int state = 0;
//0 = maze drawing state 
//1 = path finding state
//2 = result show
float mx, my;
int index = 1;

void init(void);
void mouse_update(void);
void solve(int i, int j);
void push(int a, int b);
void pop(void);
void copy_stack(void);