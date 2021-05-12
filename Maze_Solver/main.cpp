
#include "depends.h"

int main()
{
	RenderWindow window(VideoMode(W_Width, W_Height), "Maze Solver", Style::Close);
	float t = 0;
	init();

	while (window.isOpen())
	{
		dt = cl.restart();

		Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case Event::Closed:
				window.close();
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Enter))
					state = 1;
				if (Keyboard::isKeyPressed(Keyboard::R))
					init();
			default:
				break;
			}
		}

		///////////////////////

		mx = Mouse::getPosition(window).x;
		my = Mouse::getPosition(window).y;

		if (state == 0)	//when drawing 
			mouse_update();

		if (state == 1)	//solve the maze;
			solve(0, 0);

		if (top == -1 && state == 2)
		{
			t += dt.asMilliseconds();
			while (index <= top_2 && t >= 10)
			{
				t = 0;
				matrix[cpy_stack[index].r][cpy_stack[index].c].box.setFillColor(Color(128, 0, 0, 255));
				index++;
			}
		}

		/////////////////////////

		window.clear();

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				window.draw(matrix[i][j].box);

		window.display();
	}
}


void init(void)
{
	state = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j].box.setSize(Vector2f(box_dimensions - 2, box_dimensions - 2));
			matrix[i][j].box.setFillColor(Color(255, 218, 185, 255));
			matrix[i][j].box.setOutlineThickness(2.f);
			matrix[i][j].box.setOutlineColor(Color::Black);
			matrix[i][j].box.setPosition(i * box_dimensions, j * box_dimensions);
			matrix[i][j].wall = 0;
			matrix[i][j].visited = 0;
		}
	}
	matrix[0][0].box.setFillColor(Color::Green);
	matrix[row - 1][col - 1].box.setFillColor(Color::Blue);
	top = -1;
	top_2 = -1;
	index = 1;
}

void mouse_update(void)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int hot = mx > matrix[i][j].box.getPosition().x && mx < matrix[i][j].box.getPosition().x + box_dimensions
				&& my > matrix[i][j].box.getPosition().y && my < matrix[i][j].box.getPosition().y + box_dimensions;

			if (hot && Mouse::isButtonPressed(Mouse::Button::Left))
			{
				matrix[i][j].box.setFillColor(Color(20, 20, 20, 255));
				matrix[i][j].wall = 1;
			}
			if (hot && Mouse::isButtonPressed(Mouse::Button::Right))
			{
				matrix[i][j].box.setFillColor(Color(255, 218, 185, 255));
				matrix[i][j].wall = 0;
			}
		}
	}

}

void solve(int i, int j)
{
	if (state == 2)
		return;
	if (i == row - 1 && j == col - 1)
	{
		sleep(milliseconds(100));
		copy_stack();
		state = 2;
		return;
	}
	if (top < 0)
		push(i, j);
	else if (matrix[i][j].wall == 1 || matrix[i][j].visited == 1 || i<0 || i>row - 1 || j<0 || j>col - 1 ||
		(stack[top - 1].r == i && stack[top - 1].c == j))
		return;
	else
		push(i, j);

	solve(i + 1, j);
	solve(i, j + 1);
	solve(i - 1, j);
	solve(i, j - 1);

	pop();
}

void push(int a, int b)
{
	top++;
	stack[top].r = a;
	stack[top].c = b;
	matrix[a][b].visited = 1;
}
void pop()
{
	top--;
}
void copy_stack()
{
	int i;
	for (i = 0; i <= top; i++)
		cpy_stack[++top_2] = stack[i];
}
