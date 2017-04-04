#include <alfabet.h>
#include <stdbool.h>
#include "tm_stm32f4_pcd8544.h";
//#include "tm_stm32f4_rng.h";

bool screen[84][48];
int current[2][4];
int z = 4;
int shape = -1;
bool collision = false;
bool gameOver = false;
int Abs(int a) {
	if (a < 0)
		a = a * (-1);
	return a;
}

int Rand() {
	int counter = TIM4->CNT;
	while (counter < 0 || counter > 18) {
		counter = counter / 3;
	}
	return counter;

}
//1 	screen[x][y-i] = true;

//2		screen[x+i][y-size] = true;

//3		screen[x+size+i][y-size] = true;

//4		screen[x+size*2][y-size+i] = true;

//5		screen[x+size+i][y] = true;

//6		screen[x+i][y] = true;

//7		screen[x+size][y-i] = true;

//LITERY
void DrawS(int x, int y, int size) {
	for (int i = 0; i < size + 1; i++)
		screen[x][y - i] = true;

	for (int i = 1; i < size; i++)
		screen[x + i][y] = true;

	for (int i = 0; i < size; i++)
		screen[x + size][y - i] = true;

	for (int i = 0; i < size; i++)
		screen[x + size + i][y - size] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + size * 2][y - size + i] = true;

}
void DrawC(int x, int y, int size) {
	for (int i = 0; i < size + 1; i++)
		screen[x][y - i] = true;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + (size * 2)][y - i] = true;

}
void DrawO(int x, int y, int size) {
	for (int i = 0; i < size + 1; i++)
		screen[x][y - i] = true;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[(x + i)][y] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + (size * 2)][y - i] = true;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[(x + i)][y - size] = true;

}
void DrawR(int x, int y, int size) {
	for (int i = 0; i < size + 1; i++)
		screen[x][y - i] = true;

	for (int i = 0; i < size; i++)
		screen[x + i + 1][y - size] = true;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[(x + i)][y] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + size][y - i] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y - i] = true;

}
void DrawE(int x, int y, int size) {
	for (int i = 0; i < size + 1; i++)
		screen[x][y - i] = true;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + size][y - i] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + (size * 2)][y - i] = true;
}
void DrawN(int x, int y, int size) {
	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y] = true;

	for (int i = 0; i < size; i++)
		screen[x + i][y] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + i][y - size] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y - size] = true;

	for (int i = 0; i < size - 1; i++)
		screen[x + i][y - 1] = true;
	for (int i = 0; i < size - 1; i++)
		screen[x + 3 + i][y - 2] = true;
	for (int i = 0; i < size - 1; i++)
		screen[x + 6 + i][y - 3] = true;

}
void DrawDoubleDot(int x, int y)

{
	screen[x + 1][y - 1] = true;
	screen[x + 5][y - 1] = true;
}
void DrawW(int x, int y, int size) {
	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y] = true;

	for (int i = 0; i < size; i++)
		screen[x + i][y] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + i][y - size] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y - size] = true;

	for (int i = 0; i < 3; i++)
		screen[x + size + i][y - 1] = true;
	for (int i = 0; i < 3; i++)
		screen[x + size + i - 3][y - 2] = true;
	for (int i = 0; i < 3; i++)
		screen[x + size + i][y - 3] = true;

}
void DrawG(int x, int y, int size) {
	DrawC(x, y, size);

	for (int i = 0; i < size / 2 + 1; i++)
		screen[x + size][y - (size / 2) - i] = true;

	for (int i = 0; i < size; i++)
		screen[x + size + i][y - size] = true;
}
void DrawA(int x, int y, int size) {
	//1
	for (int i = 0; i < size + 1; i++)
		screen[x][y - i] = true;

	//2
	for (int i = 0; i < size + 1; i++)
		screen[x + i][y - size] = true;

	//3
	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y - size] = true;

	//5
	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y] = true;

	//6
	for (int i = 0; i < size; i++)
		screen[x + i][y] = true;

	//7
	for (int i = 0; i < size; i++)
		screen[x + size][y - i] = true;
}
void DrawM(int x, int y, int size) {
	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y] = true;

	for (int i = 0; i < size; i++)
		screen[x + i][y] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + i][y - size] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y - size] = true;

	for (int i = 0; i < 3; i++)
		screen[x + i][y - 1] = true;
	for (int i = 0; i < 3; i++)
		screen[x + i + 3][y - 2] = true;
	for (int i = 0; i < 3; i++)
		screen[x + i][y - 3] = true;

}
void DrawK(int x, int y, int size) {
	//5
	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y] = true;

	//6
	for (int i = 0; i < size; i++)
		screen[x + i][y] = true;

	for (int i = 0; i < size; i++)
		screen[x + size - i][y - i] = true;

	for (int i = 0; i < size; i++)
		screen[x + size + i][y - i] = true;

	screen[x][y - size] = true;
	screen[x + (size * 2)][y - size] = true;
}
void DrawX(int x, int y, int size) {
	for (int i = 0; i < size - 1; i++)
		screen[x + i][y - 1] = true;
	for (int i = 0; i < size - 1; i++)
		screen[x + 3 + i][y - 2] = true;
	for (int i = 0; i < size - 1; i++)
		screen[x + 6 + i][y - 3] = true;

	for (int i = 0; i < size - 1; i++)
		screen[x + i][y - 3] = true;
	for (int i = 0; i < size - 1; i++)
		screen[x + 3 + i][y - 2] = true;
	for (int i = 0; i < size - 1; i++)
		screen[x + 6 + i][y - 1] = true;
	screen[x][y - size] = true;
	screen[x + (size * 2)][y - size] = true;
	screen[x][y] = true;
	screen[x + (size * 2)][y] = true;
}
void DrawI(int x, int y, int size) {
	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y - (size / 2) - 1] = true;

}
void DrawT(int x, int y, int size) {
	DrawI(x, y, size);
	for (int i = 0; i < size + 2; i++)
		screen[x][y - i] = true;

}
void DrawV(int x, int y, int size) {

	screen[x][y] = true;
	screen[x+1][y] = true;
	for (int i = 0; i < 4; i++)
		screen[x + i+2][y-1] = true;

	for (int i = 0; i < 3; i++)
			screen[x + i+4][y-2] = true;

	for (int i = 0; i < 2; i++)
				screen[x + i+6][y-2] = true;



	screen[x][y-size] = true;
	screen[x+1][y-size] = true;
	for (int i = 0; i < 4; i++)
			screen[x + i+2][y-3] = true;
}
//---------------------------

//LICZBY
void Draw0(int x, int y, int size) {
	DrawO(x, y, size);

}
void Draw1(int x, int y, int size) {
	for (int i = 0; i < size; i++)
		screen[x + i][y - size + i] = true;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y - size] = true;
}
void Draw2(int x, int y, int size) {
	for (int i = 0; i < size + 1; i++)
		screen[x][y - i] = true;

	for (int i = 1; i < size; i++)
		screen[x + i][y - size] = true;

	for (int i = 0; i < size; i++)
		screen[x + size][y - i] = true;

	for (int i = 0; i < size; i++)
		screen[x + size + i][y] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + size * 2][y - size + i] = true;

}
void Draw3(int x, int y, int size) {
	for (int i = 0; i < size + 1; i++)
		screen[x][y - i] = true;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y - size] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + size][y - i] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + (size * 2)][y - i] = true;

}
void Draw4(int x, int y, int size) {
	for (int i = 0; i < size; i++)
		screen[x + i][y] = true;
	for (int i = 0; i < size; i++)
		screen[x + i][y - size] = true;
	for (int i = 0; i < size; i++)
		screen[x + size][y - i] = true;
	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y - size] = true;

}
void Draw5(int x, int y, int size) {
	DrawS(x, y, size);
}
void Draw6(int x, int y, int size) {

	for (int i = 0; i < size + 1; i++)
		screen[x][y - i] = true;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[(x + i)][y] = true;

	for (int i = 0; i < size; i++)
		screen[x + size][y - i] = true;

	for (int i = 0; i < size; i++)
		screen[x + size + i][y - size] = true;

	for (int i = 0; i < size + 1; i++)
		screen[x + size * 2][y - size + i] = true;
}
void Draw7(int x, int y, int size) {
	for (int i = 0; i < size + 1; i++)
		screen[x][y - i] = true;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y - size] = true;
}
void Draw8(int x, int y, int size) {
	DrawO(x, y, size);

	for (int i = 0; i < size; i++)
		screen[x + size][y - i] = true;
}
void Draw9(int x, int y, int size) {
	DrawS(x, y, size);

	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y - size] = true;
}
//-----------------------------

//POMOCNICZE
void DrawTetrisBorder() {
	for (int i = 0; i < 75; i++) {
		screen[8 + i][47] = true;
		screen[82 - i][1] = true;
	}

	for (int i = 0; i < 47; i++) {
		screen[83][47 - i] = true;
		screen[8][47 - i] = true;
	}

}
void DrawPointer(int x, int y, int size) {
	x = x + 1;
	for (int i = 0; i < size * 2; i++)
		screen[x + i][y] = true;
	for (int i = 0; i < size; i++)
		screen[x + (size * 2) - i][y - i] = true;
	for (int i = 0; i < size; i++)
		screen[x + i][y - i] = true;

	screen[x + size / 2 + 2][y - size] = true;

}
void DrawChunk(int x, int y) {
	for (int i = 0; i < z + 1; i++) {
		screen[x + i][y] = true;
		screen[x][y - i] = true;
		screen[x + z][y - i] = true;
		screen[x + i][y - z] = true;

		screen[x + i][y - i] = true;
	}
}
void ClearChunk(int x, int y) {
	for (int i = 0; i < z + 1; i++) {
		screen[x + i][y] = false;
		screen[x][y - i] = false;
		screen[x + z][y - i] = false;
		screen[x + i][y - z] = false;

		screen[x + i][y - i] = false;
	}
}
//---------------------

//FIGURY
void DrawShapeSquare(int x, int y) {
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver();

	DrawChunk(x, y);
	DrawChunk(x, y - z - 1);
	DrawChunk(x + z + 1, y);
	DrawChunk(x + z + 1, y - z - 1);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x;
	current[1][1] = y - z;

	current[0][2] = x + z + 1;
	current[1][2] = y;

	current[0][3] = x + z + 1;
	current[1][3] = y - z - 1;
}
void DrawShapeRectangleH(int x, int y) {
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver();

	DrawChunk(x, y);
	DrawChunk(x, y - z - 1);
	DrawChunk(x, y - 2 * (z + 1));
	DrawChunk(x, y - 3 * (z + 1));

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x;
	current[1][1] = y - z - 1;

	current[0][2] = x;
	current[1][2] = y - 2 * (z + 1);

	current[0][3] = x;
	current[1][3] = y - 3 * (z + 1);
}
void DrawShapeRectangleV(int x, int y) {
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver();

	DrawChunk(x, y);
	DrawChunk(x + z + 1, y);
	DrawChunk(x + 2 * (z + 1), y);
	DrawChunk(x + 3 * (z + 1), y);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x + z + 1;
	current[1][1] = y;

	current[0][2] = x + 2 * (z + 1);
	current[1][2] = y;

	current[0][3] = x + 3 * (z + 1);
	current[1][3] = y;
}

void DrawShapeLH(int x, int y) {
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver();

	DrawChunk(x, y);
	DrawChunk(x, y - z - 1);
	DrawChunk(x, y - 2 * (z + 1));
	DrawChunk(x - z - 1, y - 2 * (z + 1));

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x;
	current[1][1] = y - z - 1;

	current[0][2] = x;
	current[1][2] = y - 2 * (z + 1);

	current[0][3] = x - z - 1;
	current[1][3] = y - 2 * (z + 1);
}
void DrawShapeLHInv(int x, int y) {
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver();

	DrawChunk(x, y);
	DrawChunk(x, y - z - 1);
	DrawChunk(x, y - 2 * (z + 1));
	DrawChunk(x - z - 1, y);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x;
	current[1][1] = y - z - 1;

	current[0][2] = x;
	current[1][2] = y - 2 * (z + 1);

	current[0][3] = x - z - 1;
	current[1][3] = y;
}
void DrawShapeLHMir(int x, int y) {
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver();

	DrawChunk(x, y);
	DrawChunk(x, y - z - 1);
	DrawChunk(x, y - 2 * (z + 1));
	DrawChunk(x + z + 1, y - 2 * (z + 1));

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x;
	current[1][1] = y - z - 1;

	current[0][2] = x;
	current[1][2] = y - 2 * (z + 1);

	current[0][3] = x + z + 1;
	current[1][3] = y - 2 * (z + 1);
}
void DrawShapeLHInvMir(int x, int y) {

	DrawChunk(x, y);
	DrawChunk(x, y - z - 1);
	DrawChunk(x, y - 2 * (z + 1));
	DrawChunk(x + z + 1, y);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x;
	current[1][1] = y - z - 1;

	current[0][2] = x;
	current[1][2] = y - 2 * (z + 1);

	current[0][3] = x + z + 1;
	current[1][3] = y;
}

void DrawShapeLV(int x, int y) {
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver();

	DrawChunk(x, y);
	DrawChunk(x + z + 1, y);
	DrawChunk(x + 2 * (z + 1), y);
	DrawChunk(x + 2 * (z + 1), y - z - 1);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x + z + 1;
	current[1][1] = y;

	current[0][2] = x + 2 * (z + 1);
	current[1][2] = y;

	current[0][3] = x + 2 * (z + 1);
	current[1][3] = y - z - 1;
}
void DrawShapeLVInv(int x, int y) {
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver();

	DrawChunk(x, y);
	DrawChunk(x + z + 1, y);
	DrawChunk(x + 2 * (z + 1), y);
	DrawChunk(x + 2 * (z + 1), y + z + 1);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x + z + 1;
	current[1][1] = y;

	current[0][2] = x + 2 * (z + 1);
	current[1][2] = y;

	current[0][3] = x + 2 * (z + 1);
	current[1][3] = y + z + 1;
}
void DrawShapeLVMir(int x, int y) {
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver();

	DrawChunk(x, y);
	DrawChunk(x + z + 1, y);
	DrawChunk(x + 2 * (z + 1), y);
	DrawChunk(x, y - z - 1);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x + z + 1;
	current[1][1] = y;

	current[0][2] = x + 2 * (z + 1);
	current[1][2] = y;

	current[0][3] = x;
	current[1][3] = y - z - 1;
}
void DrawShapeLVInvMir(int x, int y) {
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver();

	DrawChunk(x, y);
	DrawChunk(x + z + 1, y);
	DrawChunk(x + 2 * (z + 1), y);
	DrawChunk(x, y + z + 1);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x + z + 1;
	current[1][1] = y;

	current[0][2] = x + 2 * (z + 1);
	current[1][2] = y;

	current[0][3] = x;
	current[1][3] = y + z + 1;
}

void DrawShapeTH(int x, int y) {
	DrawChunk(x, y);
	DrawChunk(x, y - z - 1);
	DrawChunk(x, y - 2 * (z + 1));
	DrawChunk(x + z + 1, y - z - 1);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x;
	current[1][1] = y - z - 1;

	current[0][2] = x;
	current[1][2] = y - 2 * (z + 1);

	current[0][3] = x + z + 1;
	current[1][3] = y - z - 1;

}
void DrawShapeTHInv(int x, int y) {
	DrawChunk(x, y);
	DrawChunk(x, y - z - 1);
	DrawChunk(x, y - 2 * (z + 1));
	DrawChunk(x - z - 1, y - z - 1);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x;
	current[1][1] = y - z - 1;

	current[0][2] = x;
	current[1][2] = y - 2 * (z + 1);

	current[0][3] = x - z - 1;
	current[1][3] = y - z - 1;

}
void DrawShapeTV(int x, int y) {

	DrawChunk(x, y);
	DrawChunk(x + z + 1, y);
	DrawChunk(x + 2 * (z + 1), y);
	DrawChunk(x + z + 1, y - z - 1);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x + z + 1;
	current[1][1] = y;

	current[0][2] = x + 2 * (z + 1);
	current[1][2] = y;

	current[0][3] = x + z + 1;
	current[1][3] = y - z - 1;
}
void DrawShapeTVInv(int x, int y) {

	DrawChunk(x, y);
	DrawChunk(x + z + 1, y);
	DrawChunk(x + 2 * (z + 1), y);
	DrawChunk(x + z + 1, y + z + 1);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x + z + 1;
	current[1][1] = y;

	current[0][2] = x + 2 * (z + 1);
	current[1][2] = y;

	current[0][3] = x + z + 1;
	current[1][3] = y + z + 1;
}

void DrawShapeZH(int x, int y) {

	DrawChunk(x, y);
	DrawChunk(x, y - z - 1);
	DrawChunk(x + z + 1, y - 2 * (z + 1));
	DrawChunk(x + z + 1, y - z - 1);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x;
	current[1][1] = y - z - 1;

	current[0][2] = x + z + 1;
	current[1][2] = y - 2 * (z + 1);

	current[0][3] = x + z + 1;
	current[1][3] = y - z - 1;
}
void DrawShapeZHInv(int x, int y) {

	DrawChunk(x + z + 1, y);
	DrawChunk(x, y - z - 1);
	DrawChunk(x, y - 2 * (z + 1));
	DrawChunk(x + z + 1, y - z - 1);

	current[0][0] = x + z + 1;
	current[1][0] = y;

	current[0][1] = x;
	current[1][1] = y - z - 1;

	current[0][2] = x;
	current[1][2] = y - 2 * (z + 1);

	current[0][3] = x + z + 1;
	current[1][3] = y - z - 1;
}
void DrawShapeZV(int x, int y) {

	DrawChunk(x, y);
	DrawChunk(x, y - z - 1);
	DrawChunk(x + z + 1, y);
	DrawChunk(x - z - 1, y - z - 1);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x;
	current[1][1] = y - z - 1;

	current[0][2] = x + z + 1;
	current[1][2] = y;

	current[0][3] = x - z - 1;
	current[1][3] = y - z - 1;
}
void DrawShapeZVInv(int x, int y) {

	DrawChunk(x, y);
	DrawChunk(x - z - 1, y);
	DrawChunk(x, y - z - 1);
	DrawChunk(x + z + 1, y - z - 1);

	current[0][0] = x;
	current[1][0] = y;

	current[0][1] = x;
	current[1][1] = y - z - 1;

	current[0][2] = x + z + 1;
	current[1][2] = y - z - 1;

	current[0][3] = x - z - 1;
	current[1][3] = y;
}
//----------

//NAPISY
void WriteGOSIA(int x, int y, int size) {
	DrawG(x, y, size);
	y = y - size - 2;
	DrawO(x, y, size);
	y = y - size - 2;
	DrawS(x, y, size);
	y = y - size - 2;
	DrawI(x, y, size);
	y = y - size - 2;
	DrawA(x, y, size);

}
void WriteSCORE(int x, int y, int size, int score) {

	DrawS(x, y, size);
	y = y - size - 2;
	DrawC(x, y, size);
	y = y - size - 2;
	DrawO(x, y, size);
	y = y - size - 2;
	DrawR(x, y, size);
	y = y - size - 2;
	DrawE(x, y, size);
	y = y - size - 1;
	DrawDoubleDot(x, y);
	y = y - size - 1;

	Draw0(x, y, size);
	y = y - size - 2;
	Draw0(x, y, size);
	y = y - size - 2;
	Draw0(x, y, size);
	y = y - size - 2;
	Draw0(x, y, size);
}
void WriteNEWGAME(int x, int y, int size) {
	DrawN(x, y, size);
	y = y - size - 2;
	DrawE(x, y, size);
	y = y - size - 2;
	DrawW(x, y, size);
	y = y - size - 4;
	DrawG(x, y, size);
	y = y - size - 2;
	DrawA(x, y, size);
	y = y - size - 2;
	DrawM(x, y, size);
	y = y - size - 2;
	DrawE(x, y, size);

}
void WriteRANK(int x, int y, int size) {
	DrawR(x, y, size);
	y = y - size - 2;
	DrawA(x, y, size);
	y = y - size - 2;
	DrawN(x, y, size);
	y = y - size - 2;
	DrawK(x, y, size);
}
void WriteEXIT(int x, int y, int size) {
	DrawE(x, y, size);
	y = y - size - 2;
	DrawX(x, y, size);
	y = y - size - 2;
	DrawI(x, y, size);
	y = y - size - 2;
	DrawT(x, y, size);

}
void WriteEND(int x, int y, int size) {
	DrawG(x, y, size);
	y = y - size - 2;
	DrawA(x, y, size);
	y = y - size - 2;
	DrawM(x, y, size);
	y = y - size - 2;
	DrawE(x, y, size);
	y = y - size - 4;

	DrawO(x, y, size);
	y = y - size - 2;
	DrawV(x, y, size);
	y = y - size - 2;
	DrawE(x, y, size);
	y = y - size - 2;
	DrawR(x, y, size);

}
void WriteTETRIS(int x, int y, int size) {
	DrawT(x, y, size);
	y = y - size - 3;
	DrawE(x, y, size);
	y = y - size - 2;
	DrawT(x, y, size);
	y = y - size - 3;
	DrawR(x, y, size);
	y = y - size - 2;
	DrawI(x, y, size);
	y = y - size - 2;
	DrawS(x, y, size);

}
void WriteGAMEOVER(int x, int y, int size) {
	DrawG(x, y, size);
	y = y - size - 2;
	DrawA(x, y, size);
	y = y - size - 2;
	DrawM(x, y, size);
	y = y - size - 2;
	DrawE(x, y, size);
	y = y + 3*( size + 2);
	x = x+size+6;
	DrawO(x, y, size);
	y = y - size - 2;
	DrawV(x, y, size);
	y = y - size - 2;
	DrawE(x, y, size);
	y = y - size - 2;
	DrawR(x, y, size);

}
//-----------

//MENUs AND LOGOs
void TETMenu(int x, int y, int size) {
	WriteNEWGAME(x, y, size);
	WriteRANK(x + 12, y, size);
	WriteEXIT(x + 24, y, size);
}
void DrawSnake(int x, int y) {

	for (int i = 0; i < 5; i++)
		screen[x][y - 4 - i] = true;

	screen[x + 1][y - 3] = true;

	for (int i = 0; i < 5; i++)
		screen[x + i + 2][y - 2] = true;

	screen[x + 7][y - 3] = true;

	for (int i = 0; i < 5; i++)
		screen[x + 8][y - 4 - i] = true;

	screen[x + 7][y - 9] = true;

	for (int i = 0; i < 5; i++)
		screen[x + i + 2][y - 10] = true;

	screen[x + 1][y - 9] = true;

	screen[x + 4][y - 4] = true;
	screen[x + 3][y - 4] = true;
	screen[x + 3][y - 5] = true;
	screen[x + 4][y - 5] = true;

	screen[x + 4][y - 7] = true;
	screen[x + 3][y - 7] = true;
	screen[x + 3][y - 8] = true;
	screen[x + 4][y - 8] = true;

//
	screen[x + 9][y - 5] = true;
	screen[x + 10][y - 4] = true;
	screen[x + 10][y - 3] = true;
	screen[x + 10][y - 2] = true;
	screen[x + 11][y - 1] = true;
	screen[x + 12][y] = true;
	screen[x + 12][y - 2] = true;
//

	for (int i = 0; i < 3; i++)
		screen[x + 9 + i][y - 7] = true;

	for (int i = 0; i < 13; i++)
		screen[x + 12][y - 5 - i] = true;

	screen[x + 10][y - 17] = true;
	screen[x + 11][y - 17] = true;

	for (int i = 0; i < 7; i++)
		screen[x + 9][y - 10 - i] = true;

	screen[x + 8][y - 10] = true;

	screen[x + 9][y - 18] = true;
	screen[x + 9][y - 19] = true;

	screen[x + 8][y - 20] = true;
	screen[x + 7][y - 20] = true;

	for (int i = 0; i < 5; i++)
		screen[x + 6 - i][y - 21] = true;

	screen[x + 3][y - 22] = true;

	for (int i = 0; i < 8; i++)
		screen[x + 4 + i][y - 23] = true;

	screen[x + 12][y - 22] = true;
	screen[x + 13][y - 21] = true;
	screen[x + 14][y - 20] = true;

	for (int i = 0; i < 17; i++)
		screen[x + 15][y - 19 + i] = true;

	screen[x + 14][y - 18] = true;
	screen[x + 13][y - 18] = true;

	screen[x + 14][y - 4] = true;
	screen[x + 13][y - 4] = true;

	screen[x + 16][y - 2] = true;
	screen[x + 17][y - 2] = true;

	for (int i = 0; i < 19; i++)
		screen[x + 18][y - 2 - i] = true;

	screen[x + 16][y - 20] = true;
	screen[x + 17][y - 20] = true;

}
void DrawTETLogo() {
	WriteTETRIS(18, 38, 3);
	//DrawRectangle(15, 40, 27, 5);
	//DrawRectangle(27, 28, 39, 16);
}
//---------------

//MAIN SCREEN DRAW
void ClearScreen() {
	for (int i = 0; i < 84; i++) {
		for (int j = 0; j < 48; j++) {
			screen[i][j] = false;

		}
	}
	DrawTetrisBorder();
	DrawScreen();
}
void DrawScreen() {
	for (int i = 0; i < 84; i++) {
		for (int j = 0; j < 48; j++) {
			if (screen[i][j])
				PCD8544_DrawPixel(i, j, PCD8544_Pixel_Set);
			else
				PCD8544_DrawPixel(i, j, PCD8544_Pixel_Clear);

		}
	}
	//DrawTetrisBorder();
	PCD8544_Refresh();
}
void ClearREC(int x,int y, int x1, int y1)
{
	int sizeX = Abs(x-x1);
	int sizeY = Abs(y-y1);

	for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				screen[i+x][j+y1] = false;

			}
		}
	DrawScreen();
}
//--------------

//ZARZADZANIE FIGURAMI
extern uint32_t TM_RNG_Get(void);
void GameOver() {
	gameOver = true;
	TIM_Cmd(TIM2, DISABLE);
	TIM_Cmd(TIM3, DISABLE);
	ClearREC(35, 38,59,11);
	WriteGAMEOVER(38, 36, 4);
	WriteSCORE(0, 47, 3, 0);

}
void MoveRight(int x, int y, int shape) //shape (0-18)
{
	switch (shape) {

	case 0: //kwadrat
	{
		if (!screen[x][y - z - 1 - z - 1]
				&& !screen[x + z + 1][y - z - 1 - z - 1]) {
			ClearChunk(x, y);
			ClearChunk(x + z + 1, y);
			DrawChunk(x, y - ((z + 1) * 2));
			DrawChunk(x + z + 1, y - ((z + 1) * 2));

			current[0][0] = x;
			current[0][1] = x;
			current[1][0] = y - z - 1;
			current[1][1] = y - ((z + 1) * 2);

			current[0][2] = x + z + 1;
			current[0][3] = x + z + 1;
			current[1][2] = y - z - 1;
			current[1][3] = y - ((z + 1) * 2);

		}

		break;
	}

	case 1: //prostokat poziomy
	{
		if (!screen[x][y - (4 * (z + 1))]) {
			ClearChunk(x, y);

			DrawChunk(x, y - 4 * (z + 1));

			current[0][0] = x;
			current[0][1] = x;
			current[1][0] = y - z - 1;
			current[1][1] = y - (z + 1) * 2;

			current[0][2] = x;
			current[0][3] = x;
			current[1][2] = y - (z + 1) * 3;
			current[1][3] = y - 4 * (z + 1);

		}

		break;
	}
	case 2: //prostokat pionowy
	{
		if (!screen[x][y - z - 1] && !screen[x + z + 1][y - z - 1]
				&& !screen[x + 2 * (z + 1)][y - z - 1]
				&& !screen[x + 3 * (z + 1)][y - z - 1]) {
			ClearChunk(x, y);
			ClearChunk(x + 1 * (z + 1), y);
			ClearChunk(x + 2 * (z + 1), y);
			ClearChunk(x + 3 * (z + 1), y);

			DrawChunk(x, y - z - 1);
			DrawChunk(x + 1 * (z + 1), y - z - 1);
			DrawChunk(x + 2 * (z + 1), y - z - 1);
			DrawChunk(x + 3 * (z + 1), y - z - 1);

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x + 1 * (z + 1);
			current[1][1] = y - z - 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y - z - 1;

			current[0][3] = x + 3 * (z + 1);
			current[1][3] = y - z - 1;
		}

		break;
	}

	case 3: //Pionowe L
	{
		if (!screen[x][y - 3 * (z + 1)]
				&& !screen[x - z - 1][y - 3 * (z + 1)]) {
			ClearChunk(x, y);
			ClearChunk(x - z - 1, y - 2 * (z + 1));

			DrawChunk(x, y - 3 * (z + 1));
			DrawChunk(x - z - 1, y - 3 * (z + 1));

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x;
			current[1][1] = y - 2 * (z + 1);

			current[0][2] = x;
			current[1][2] = y - 3 * (z + 1);

			current[0][3] = x - z - 1;
			current[1][3] = y - 3 * (z + 1);

		}

		break;
	}
	case 4: // Pionowe L odwr�cone(Inverted)   _|
	{
		if (!screen[x - z - 1][y - z - 1] && !screen[x][y - 3 * (z + 1)]) {

			ClearChunk(x, y);
			ClearChunk(x - z - 1, y);

			DrawChunk(x - z - 1, y - z - 1);
			DrawChunk(x, y - 3 * (z + 1));

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x;
			current[1][1] = y - 2 * (z + 1);

			current[0][2] = x;
			current[1][2] = y - 3 * (z + 1);

			current[0][3] = x - z - 1;
			current[1][3] = y - z - 1;

		}

		break;
	} //							     _
	case 5: // Pionowe L odbite(Mirrored)|
	{
		if (!screen[x][y - 3 * (z + 1)]
				&& !screen[x + z + 1][y - 3 * (z + 1)]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y - 2 * (z + 1));

			DrawChunk(x, y - 3 * (z + 1));
			DrawChunk(x + z + 1, y - 3 * (z + 1));

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x;
			current[1][1] = y - 2 * (z + 1);

			current[0][2] = x;
			current[1][2] = y - 3 * (z + 1);

			current[0][3] = x + z + 1;
			current[1][3] = y - 3 * (z + 1);

		}

		break;
	}
	case 6: // Pionowe L odbitei odwrocone   _
	{ //

		if (!screen[x][y - 3 * (z + 1)] && !screen[x + z + 1][y - z - 1]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y);

			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x, y - 3 * (z + 1));

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x;
			current[1][1] = y - 2 * (z + 1);

			current[0][2] = x;
			current[1][2] = y - 3 * (z + 1);

			current[0][3] = x + z + 1;
			current[1][3] = y - z - 1;

		}

		break;
	}
	case 7: //Poziome L
	{
		if (!screen[x][y - z - 1] && !screen[x + z + 1][y - z - 1]
				&& !screen[x + 2 * (z + 1)][y - 2 * (z + 1)]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y);
			ClearChunk(x + z + 1 + z + 1, y);

			DrawChunk(x, y - z - 1);
			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x + 2 * (z + 1), y - 2 * (z + 1));

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y - z - 1;

			current[0][3] = x + 2 * (z + 1);
			current[1][3] = y - 2 * (z + 1);

		}
		break;
	}

	case 8: //Poziome odwrocone L  |___
	{

		if (!screen[x][y - z - 1] && !screen[x + z + 1][y - z - 1]
				&& !screen[x + 2 * (z + 1)][y - z - 1]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y);
			ClearChunk(x + z + 1 + z + 1, y + z + 1);

			DrawChunk(x, y - z - 1);
			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x + 2 * (z + 1), y - z - 1);

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y - z - 1;

			current[0][3] = x + 2 * (z + 1);
			current[1][3] = y - z - 1;

		}
		break;
	}

	case 9: //Poziome L odbite  -----|
	{

		if (!screen[x][y - 2 * (z + 1)] && !screen[x + z + 1][y - z - 1]
				&& !screen[x + 2 * (z + 1)][y - z - 1]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y);
			ClearChunk(x + z + 1 + z + 1, y);

			DrawChunk(x, y - 2 * (z + 1));
			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x + 2 * (z + 1), y - z - 1);

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y - z - 1;

			current[0][3] = x;
			current[1][3] = y - z - 1;

		}
		break;
	}
	case 10: //Poziome L odbite i odwrocone |-----
	{

		if (!screen[x][y - z - 1] && !screen[x + z + 1][y - z - 1]
				&& !screen[x + 2 * (z + 1)][y - z - 1]) {

			ClearChunk(x, y + z + 1);
			ClearChunk(x + z + 1, y);
			ClearChunk(x + z + 1 + z + 1, y);

			DrawChunk(x, y - z - 1);
			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x + 2 * (z + 1), y - z - 1);

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y - z - 1;

			current[0][3] = x;
			current[1][3] = y - z - 1;

		}
		break;
	}
	case 11: // Poziome T
	{
		if (!screen[x][y - 3 * (z + 1)]
				&& !screen[x + z + 1][y - 2 * (z + 1)]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y - z - 1);

			DrawChunk(x, y - 3 * (z + 1));
			DrawChunk(x + z + 1, y - 2 * (z + 1));

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x;
			current[1][1] = y - 2 * (z + 1);

			current[0][2] = x;
			current[1][2] = y - 3 * (z + 1);

			current[0][3] = x + z + 1;
			current[1][3] = y - 2 * (z + 1);

		}
		break;
	}
	case 12: // Poziome odwrocone T  _L
	{
		if (!screen[x][y - 3 * (z + 1)]
				&& !screen[x - z - 1][y - 2 * (z + 1)]) {

			ClearChunk(x, y);
			ClearChunk(x - z - 1, y - z - 1);

			DrawChunk(x, y - 3 * (z + 1));
			DrawChunk(x - z - 1, y - 2 * (z + 1));

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x;
			current[1][1] = y - 2 * (z + 1);

			current[0][2] = x;
			current[1][2] = y - 3 * (z + 1);

			current[0][3] = x - z - 1;
			current[1][3] = y - 2 * (z + 1);

		}
		break;
	}
	case 13:
		// Pionowe T  I-
	{
		if (!screen[x][y - z - 1] && !screen[x + 2 * (z + 1)][y - z - 1]
				&& !screen[x + z + 1][y - 2 * (z + 1)]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y);
			ClearChunk(x + 2 * (z + 1), y);

			DrawChunk(x, y - z - 1);
			DrawChunk(x + z + 1, y - 2 * (z + 1));
			DrawChunk(x + 2 * (z + 1), y - z - 1);

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y - z - 1;

			current[0][3] = x + z + 1;
			current[1][3] = y - 2 * (z + 1);

		}
		break;
	}
	case 14:
		// Pionowe T  odwrocone -I
	{
		if (!screen[x][y - z - 1] && !screen[x + z + 1][y - z - 1]
				&& !screen[x + 2 * (z + 1)][y - z - 1]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y + z + 1);
			ClearChunk(x + 2 * (z + 1), y);

			DrawChunk(x, y - z - 1);
			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x + 2 * (z + 1), y - z - 1);

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y - z - 1;

			current[0][3] = x + z + 1;
			current[1][3] = y;

		}
		break;
	}
	case 15:
		// Poziome Z	-|_
	{
		if (!screen[x][y - 2 * (z + 1)]
				&& !screen[x + z + 1][y - 3 * (z + 1)]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y - z - 1);

			DrawChunk(x, y - 2 * (z + 1));
			DrawChunk(x + z + 1, y - 3 * (z + 1));

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x;
			current[1][1] = y - 2 * (z + 1);

			current[0][2] = x + z + 1;
			current[1][2] = y - 2 * (z + 1);

			current[0][3] = x + z + 1;
			current[1][3] = y - 3 * (z + 1);

		}
		break;
	}
	case 16:
		// Poziome odworcone Z	_|-
	{
		if (!screen[x][y - 2 * (z + 1)]
				&& !screen[x - z - 1][y - 3 * (z + 1)]) {

			ClearChunk(x, y);
			ClearChunk(x - z - 1, y - z - 1);

			DrawChunk(x, y - 2 * (z + 1));
			DrawChunk(x - z - 1, y - 3 * (z + 1));

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x;
			current[1][1] = y - 2 * (z + 1);

			current[0][2] = x - z - 1;
			current[1][2] = y - 2 * (z + 1);

			current[0][3] = x - z - 1;
			current[1][3] = y - 3 * (z + 1);

		}
		break;
	}
	case 17:
		// Pionowe Z	_|-
	{
		if (!screen[x - z - 1][y - 2 * (z + 1)] && !screen[x][y - 2 * (z + 1)]
				&& !screen[x + z + 1][y - z - 1]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y);
			ClearChunk(x - z - 1, y - z - 1);

			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x, y - 2 * (z + 1));
			DrawChunk(x - z - 1, y - 2 * (z + 1));

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x;
			current[1][1] = y - 2 * (z + 1);

			current[0][2] = x + z + 1;
			current[1][2] = y - z - 1;

			current[0][3] = x - z - 1;
			current[1][3] = y - 2 * (z + 1);

		}
		break;
	}
	case 18:
		// Pionowe odworcone Z  	',
	{
		if (!screen[x - z - 1][y - z - 1] && !screen[x][y - 2 * (z + 1)]
				&& !screen[x + z + 1][y - 2 * (z + 1)]) {

			ClearChunk(x, y);
			ClearChunk(x - z - 1, y);
			ClearChunk(x + z + 1, y - z - 1);

			DrawChunk(x - z - 1, y - z - 1);
			DrawChunk(x, y - 2 * (z + 1));
			DrawChunk(x + z + 1, y - 2 * (z + 1));

			current[0][0] = x;
			current[1][0] = y - z - 1;

			current[0][1] = x;
			current[1][1] = y - 2 * (z + 1);

			current[0][2] = x + z + 1;
			current[1][2] = y - z - 1;

			current[0][3] = x - z - 1;
			current[1][3] = y - z - 1;

		}
		break;
	}
	}
}

void MoveLeft(int x, int y, int shape) //shape (0-18)
{
	switch (shape) {
	case 0: //kwadrat
	{
		if (!screen[x][y + 1] && !screen[x + z + 1][y + 1]) {
			ClearChunk(x, y - z - 1);
			ClearChunk(x + z + 1, y - z - 1);

			DrawChunk(x, y + z + 1);
			DrawChunk(x + z + 1, y + z + 1);

			current[0][0] = x;
			current[0][1] = x;
			current[1][0] = y + z + 1;
			current[1][1] = y;

			current[0][2] = x + z + 1;
			current[0][3] = x + z + 1;
			current[1][2] = y + z + 1;
			current[1][3] = y;

		}
		break;
	}
	case 1: //prostokat poziomy
	{
		if (!screen[x][y + 1]) {
			ClearChunk(x, y - 3 * (z + 1));

			DrawChunk(x, y + (z + 1));

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x;
			current[1][1] = y;

			current[0][2] = x;
			current[1][2] = y - (z + 1);

			current[0][3] = x;
			current[1][3] = y - 2 * (z + 1);

		}

		break;
	}
	case 2: //prostokat pionowy
	{
		if (!screen[x][y + 1] && !screen[x + z + 1][y + 1]
				&& !screen[x + 2 * (z + 1)][y + 1]
				&& !screen[x + 3 * (z + 1)][y + 1]) {
			ClearChunk(x, y);
			ClearChunk(x + 1 * (z + 1), y);
			ClearChunk(x + 2 * (z + 1), y);
			ClearChunk(x + 3 * (z + 1), y);

			DrawChunk(x, y + z + 1);
			DrawChunk(x + 1 * (z + 1), y + z + 1);
			DrawChunk(x + 2 * (z + 1), y + z + 1);
			DrawChunk(x + 3 * (z + 1), y + z + 1);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x + 1 * (z + 1);
			current[1][1] = y + z + 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y + z + 1;

			current[0][3] = x + 3 * (z + 1);
			current[1][3] = y + z + 1;
		}

		break;
	}
	case 3: //Poziome L  ___|
	{
		if (!screen[x][y + 1] && !screen[x - z - 1][y - z - 1]) {
			ClearChunk(x, y - 2 * (z + 1));
			ClearChunk(x - z - 1, y - 2 * (z + 1));

			DrawChunk(x, y + z + 1);
			DrawChunk(x - z - 1, y - z - 1);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x;
			current[1][1] = y;

			current[0][2] = x;
			current[1][2] = y - z - 1;

			current[0][3] = x - z - 1;
			current[1][3] = y - z - 1;

		}

		break;
	}

	case 4: //Poziome odwrocone L  |___
	{
		if (!screen[x][y + 1] && !screen[x - z - 1][y + 1]) {

			ClearChunk(x, y - 2 * (z + 1));
			ClearChunk(x - z - 1, y);

			DrawChunk(x, y + z + 1);
			DrawChunk(x - z - 1, y + z + 1);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x;
			current[1][1] = y;

			current[0][2] = x;
			current[1][2] = y - z - 1;

			current[0][3] = x - z - 1;
			current[1][3] = y + z + 1;

		}

		break;
	}

	case 5: //Poziome L odbite  ¯¯¯|
	{
		if (!screen[x][y + 1] && !screen[x + z + 1][y - z - 1]) {

			ClearChunk(x, y - 2 * (z + 1));
			ClearChunk(x + z + 1, y - 2 * (z + 1));

			DrawChunk(x, y + z + 1);
			DrawChunk(x + z + 1, y - z - 1);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x;
			current[1][1] = y;

			current[0][2] = x;
			current[1][2] = y - z - 1;

			current[0][3] = x + z + 1;
			current[1][3] = y - z - 1;

		}

		break;
	}

	case 6: //Poziome L odbite i odwrocone |¯¯
	{
		if (!screen[x][y + 1] && !screen[x + z + 1][y + 1]) {

			ClearChunk(x, y - 2 * (z + 1));
			ClearChunk(x + z + 1, y);

			DrawChunk(x, y + z + 1);
			DrawChunk(x + z + 1, y + z + 1);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x;
			current[1][1] = y;

			current[0][2] = x;
			current[1][2] = y - z - 1;

			current[0][3] = x + z + 1;
			current[1][3] = y + z + 1;

		}

		break;
	}
	case 7: //Pionowe L
	{
		if (!screen[x][y + 1] && !screen[x + z + 1][y + 1]
				&& !screen[x + 2 * (z + 1)][y + 1]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y);
			ClearChunk(x + z + 1 + z + 1, y - z - 1);

			DrawChunk(x, y + z + 1);
			DrawChunk(x + z + 1, y + z + 1);
			DrawChunk(x + 2 * (z + 1), y + z + 1);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x + z + 1;
			current[1][1] = y + z + 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y + z + 1;

			current[0][3] = x + 2 * (z + 1);
			current[1][3] = y;

		}

		break;
	}
	case 8: // Pionowe L odwr�cone(Inverted)   _|
	{
		if (!screen[x][y + 1] && !screen[x + z + 1][y + 1]
				&& !screen[x + 2 * (z + 1)][y + z + 1 + 1]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y);
			ClearChunk(x + z + 1 + z + 1, y);

			DrawChunk(x, y + z + 1);
			DrawChunk(x + z + 1, y + z + 1);
			DrawChunk(x + 2 * (z + 1), y + 2 * (z + 1));

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x + z + 1;
			current[1][1] = y + z + 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y + z + 1;

			current[0][3] = x + 2 * (z + 1);
			current[1][3] = y + 2 * (z + 1);

		}

		break;
	}
	case 9: // Pionowe L odbite(Mirrored)|
	{
		if (!screen[x][y + 1] && !screen[x + z + 1][y + 1]
				&& !screen[x + 2 * (z + 1)][y + 1]) {

			ClearChunk(x, y - z - 1);
			ClearChunk(x + z + 1, y);
			ClearChunk(x + z + 1 + z + 1, y);

			DrawChunk(x, y + z + 1);
			DrawChunk(x + z + 1, y + z + 1);
			DrawChunk(x + 2 * (z + 1), y + z + 1);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x + z + 1;
			current[1][1] = y + z + 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y + z + 1;

			current[0][3] = x;
			current[1][3] = y - z - 1;

		}

		break;
	}
	case 10: // Pionowe L odbitei odwrocone   _
	{ //        							   |
		if (!screen[x][y + z + 2] && !screen[x + z + 1][y + 1]
				&& !screen[x + 2 * (z + 1)][y + 1]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y);
			ClearChunk(x + z + 1 + z + 1, y);

			DrawChunk(x, y + 2 * (z + 1));
			DrawChunk(x + z + 1, y + z + 1);
			DrawChunk(x + 2 * (z + 1), y + z + 1);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x + z + 1;
			current[1][1] = y + z + 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y + z + 1;

			current[0][3] = x;
			current[1][3] = y + 2 * (z + 1);

		}
		break;
	}
	case 11: // Poziome T
	{
		if (!screen[x][y + 1] && !screen[x + z + 1][y]) {

			ClearChunk(x, y - 2 * (z + 1));
			ClearChunk(x + z + 1, y - z - 1);

			DrawChunk(x + z + 1, y);
			DrawChunk(x, y + z + 1);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x;
			current[1][1] = y;

			current[0][2] = x;
			current[1][2] = y - z - 1;

			current[0][3] = x + z + 1;
			current[1][3] = y;

		}
		break;
	}
	case 12: // Poziome odwrocone T  _L
	{
		if (!screen[x][y + 1] && !screen[x - z - 1][y]) {

			ClearChunk(x, y - 2 * (z + 1));
			ClearChunk(x - z - 1, y - z - 1);

			DrawChunk(x, y + z + 1);
			DrawChunk(x - z - 1, y);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x;
			current[1][1] = y;

			current[0][2] = x;
			current[1][2] = y - z - 1;

			current[0][3] = x - z - 1;
			current[1][3] = y;

		}
		break;
	}
	case 13:
		// Pionowe T  I-
	{
		if (!screen[x][y + 1] && !screen[x + 2 * (z + 1)][y + 1]
				&& !screen[x + z + 1][y + 1]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y - z - 1);
			ClearChunk(x + 2 * (z + 1), y);

			DrawChunk(x, y + z + 1);
			DrawChunk(x + z + 1, y + z + 1);
			DrawChunk(x + 2 * (z + 1), y + z + 1);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x + z + 1;
			current[1][1] = y + z + 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y + z + 1;

			current[0][3] = x + z + 1;
			current[1][3] = y;

		}
		break;
	}
	case 14:
		// Pionowe T  odwrocone -I
	{
		if (!screen[x][y + 1] && !screen[x + z + 1][y + z + 2]
				&& !screen[x + 2 * (z + 1)][y + 1]) {

			ClearChunk(x, y);
			ClearChunk(x + z + 1, y);
			ClearChunk(x + 2 * (z + 1), y);

			DrawChunk(x, y + z + 1);
			DrawChunk(x + z + 1, y + 2 * (z + 1));
			DrawChunk(x + 2 * (z + 1), y + z + 1);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x + z + 1;
			current[1][1] = y + z + 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y + z + 1;

			current[0][3] = x + z + 1;
			current[1][3] = y + 2 * (z + 1);

		}
		break;
	}
	case 15:
		// Poziome Z	-|_
	{
		if (!screen[x][y + 1] && !screen[x + z + 1][y]) {

			ClearChunk(x, y - z - 1);
			ClearChunk(x + z + 1, y - 2 * (z + 1));

			DrawChunk(x, y + z + 1);
			DrawChunk(x + z + 1, y);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x;
			current[1][1] = y;

			current[0][2] = x + z + 1;
			current[1][2] = y;

			current[0][3] = x + z + 1;
			current[1][3] = y - z - 1;

		}
		break;
	}
	case 16:
		// Poziome odworcone Z	_|-
	{
		if (!screen[x][y + 1] && !screen[x - z - 1][y]) {

			ClearChunk(x, y - z - 1);
			ClearChunk(x - z - 1, y - 2 * (z + 1));

			DrawChunk(x, y + z + 1);
			DrawChunk(x - z - 1, y);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x;
			current[1][1] = y;

			current[0][2] = x - z - 1;
			current[1][2] = y;

			current[0][3] = x + z + 1;
			current[1][3] = y - z - 1;

		}
		break;
	}
	case 17:
		// Pionowe odworcone Z	,`
	{
		if (!screen[x][y + 1] && !screen[x + z + 1][y + 1]
				&& !screen[x - z - 1][y]) {

			ClearChunk(x, y - z - 1);
			ClearChunk(x + z + 1, y);
			ClearChunk(x - z - 1, y - z - 1);

			DrawChunk(x, y + z + 1);
			DrawChunk(x + z + 1, y + z + 1);
			DrawChunk(x - z - 1, y);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x;
			current[1][1] = y;

			current[0][2] = x + z + 1;
			current[1][2] = y + z + 1;

			current[0][3] = x - z - 1;
			current[1][3] = y;

		}
		break;
	}
	case 18:
		// Pionowe odworcone Z  	',
	{
		if (!screen[x][y + 1] && !screen[x - z - 1][y + 1]
				&& !screen[x + z + 1][y]) {

			ClearChunk(x - z - 1, y);
			ClearChunk(x, y - z - 1);
			ClearChunk(x + z + 1, y - z - 1);

			DrawChunk(x - z - 1, y + z + 1);
			DrawChunk(x, y + z + 1);
			DrawChunk(x + z + 1, y);

			current[0][0] = x;
			current[1][0] = y + z + 1;

			current[0][1] = x;
			current[1][1] = y;

			current[0][2] = x + z + 1;
			current[1][2] = y;

			current[0][3] = x - z - 1;
			current[1][3] = y + z + 1;

		}
		break;
	}
	}
}

void MoveDown(int x, int y, int shape) //shape (0-18)
{
	switch (shape) {
	case 0: //kwadrat
	{
		if (!screen[x + z + 1 + z + 1][y]
				&& !screen[x + z + 1 + z + 1][y - z - 1]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x, y - z - 1);

			DrawChunk(x + (z + 1) * 2, y);
			DrawChunk(x + (z + 1) * 2, y - z - 1);

			current[0][0] = x + z + 1;
			current[0][1] = x + z + 1;
			current[1][0] = y;
			current[1][1] = y - z - 1;

			current[0][2] = x + (z + 1) * 2;
			current[0][3] = x + (z + 1) * 2;
			current[1][2] = y;
			current[1][3] = y - z - 1;

		} else
			collision = true;
		break;
	}
	case 1: //prostokat poziomy
	{
		if (!screen[x + z + 1][y]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x, y - 1 * (z + 1));
			ClearChunk(x, y - 2 * (z + 1));
			ClearChunk(x, y - 3 * (z + 1));

			DrawChunk(x + z + 1, y);
			DrawChunk(x + z + 1, y - 1 * (z + 1));
			DrawChunk(x + z + 1, y - 2 * (z + 1));
			DrawChunk(x + z + 1, y - 3 * (z + 1));

			current[0][0] = x + z + 1;
			//current[1][0] = y;

			current[0][1] = x + z + 1;
			//current[1][1] = y;

			current[0][2] = x + z + 1;
			//current[1][2] = y - (z + 1);

			current[0][3] = x + z + 1;
			//current[1][3] = y - 2 * (z + 1);

		} else
			collision = true;
		break;
	}
	case 2: //prostokat pionowy
	{
		if (!screen[x + 4 * (z + 1)][y]) {
			ClearChunk(x, y);
			collision = false;
			DrawChunk(x + 4 * (z + 1), y);

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + 2 * (z + 1);
			current[1][1] = y;

			current[0][2] = x + 3 * (z + 1);
			current[1][2] = y;

			current[0][3] = x + 4 * (z + 1);
			current[1][3] = y;
		} else
			collision = true;
		break;
	}
	case 3: //Poziome L  ___|
	{
		if (!screen[x + z + 1][y] && !screen[x + z + 1][y - z - 1]
				&& !screen[x + z + 1][y - 2 * (z + 1)]) {
			ClearChunk(x, y);
			ClearChunk(x, y - z - 1);
			ClearChunk(x - z - 1, y - 2 * (z + 1));

			DrawChunk(x + z + 1, y);
			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x + z + 1, y - 2 * (z + 1));

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + z + 1;
			current[1][2] = y - 2 * (z + 1);

			current[0][3] = x;
			current[1][3] = y - 2 * (z + 1);

		} else
			collision = true;
		break;
	}
	case 4: //Poziome odwrocone L  |___
	{
		if (!screen[x + z + 1][y] && !screen[x + z + 1][y - z - 1]
				&& !screen[x + z + 1][y - 2 * (z + 1)]) {
			collision = false;
			ClearChunk(x, y - z - 1);
			ClearChunk(x, y - 2 * (z + 1));
			ClearChunk(x - z - 1, y);

			DrawChunk(x + z + 1, y);
			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x + z + 1, y - 2 * (z + 1));

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + z + 1;
			current[1][2] = y - 2 * (z + 1);

			current[0][3] = x;
			current[1][3] = y;

		} else
			collision = true;
		break;
	}

	case 5: //Poziome L odbite  ¯¯¯|
	{
		if (!screen[x + z + 1][y] && !screen[x + z + 1][y - z - 1]
				&& !screen[x + z + 1 + z + 1][y - 2 * (z + 1)]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x, y - z - 1);
			ClearChunk(x, y - 2 * (z + 1));

			DrawChunk(x + z + 1, y);
			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x + 2 * (z + 1), y - 2 * (z + 1));

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + z + 1;
			current[1][2] = y - 2 * (z + 1);

			current[0][3] = x + 2 * (z + 1);
			current[1][3] = y - 2 * (z + 1);

		} else
			collision = true;
		break;
	}
	case 6: //Poziome L odbite i odwrocone |¯¯
	{
		if (!screen[x + 2 * (z + 1)][y] && !screen[x + z + 1][y - z - 1]
				&& !screen[x + z + 1][y - 2 * (z + 1)]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x, y - z - 1);
			ClearChunk(x, y - 2 * (z + 1));

			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x + z + 1, y - 2 * (z + 1));
			DrawChunk(x + 2 * (z + 1), y);

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + z + 1;
			current[1][2] = y - 2 * (z + 1);

			current[0][3] = x + 2 * (z + 1);
			current[1][3] = y;

		} else
			collision = true;
		break;
	}
	case 7: //Pionowe L
	{
		if (!screen[x + 3 * (z + 1)][y - z - 1]
				&& !screen[x + 3 * (z + 1)][y]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x + z + 1 + z + 1, y - z - 1);

			DrawChunk(x + 3 * (z + 1), y);
			DrawChunk(x + 3 * (z + 1), y - z - 1);

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + 2 * (z + 1);
			current[1][1] = y;

			current[0][2] = x + 3 * (z + 1);
			current[1][2] = y;

			current[0][3] = x + 3 * (z + 1);
			current[1][3] = y + z + 1;

		} else
			collision = true;
		break;
	}
	case 8: // Pionowe L odwr�cone(Inverted)   _|
	{
		if (!screen[x + 3 * (z + 1)][y]
				&& !screen[x + 3 * (z + 1)][y + z + 1]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x + z + 1 + z + 1, y + z + 1);

			DrawChunk(x + 3 * (z + 1), y);
			DrawChunk(x + 3 * (z + 1), y + z + 1);

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + 2 * (z + 1);
			current[1][1] = y;

			current[0][2] = x + 3 * (z + 1);
			current[1][2] = y;

			current[0][3] = x + 3 * (z + 1);
			current[1][3] = y + z + 1;

		} else
			collision = true;
		break;
	}
	case 9: // Pionowe L odbite(Mirrored)|
	{
		if (!screen[x + z + 1][y - z - 1] && !screen[x + 3 * (z + 1)][y]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x, y - z - 1);

			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x + 3 * (z + 1), y);

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + 2 * (z + 1);
			current[1][1] = y;

			current[0][2] = x + 3 * (z + 1);
			current[1][2] = y;

			current[0][3] = x + z + 1;
			current[1][3] = y - z - 1;
		} else
			collision = true;
		break;
	}
	case 10:
		// Pionowe L odbitei odwrocone   _
	{ //        |
		if (!screen[x + z + 1][y + z + 1] && !screen[x + 3 * (z + 1)][y]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x, y + z + 1);

			DrawChunk(x + z + 1, y + z + 1);
			DrawChunk(x + 3 * (z + 1), y);

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + 2 * (z + 1);
			current[1][1] = y;

			current[0][2] = x + 3 * (z + 1);
			current[1][2] = y;

			current[0][3] = x + z + 1;
			current[1][3] = y + z + 1;

		} else
			collision = true;
		break;
	}
	case 11:
		// Poziome T
	{
		if (!screen[x + z + 1][y - 2 * (z + 1)] && !screen[x + z + 1][y]
				&& !screen[x + 2 * (z + 1)][y - z - 1]) {
			collision = false;
			ClearChunk(x, y - 2 * (z + 1));
			ClearChunk(x, y - z - 1);
			ClearChunk(x, y);

			DrawChunk(x + z + 1, y);
			DrawChunk(x + z + 1, y - 2 * (z + 1));
			DrawChunk(x + 2 * (z + 1), y - z - 1);

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + z + 1;
			current[1][2] = y - 2 * (z + 1);

			current[0][3] = x + 2 * (z + 1);
			current[1][3] = y - z - 1;

		} else
			collision = true;
		break;
	}
	case 12:
		// Poziome odwrocone T  _L
	{
		if (!screen[x + z + 1][y] && !screen[x + z + 1][y - z - 1]
				&& !screen[x + z + 1][y - 2 * (z + 1)]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x - z - 1, y - z - 1);

			ClearChunk(x, y - 2 * (z + 1));

			DrawChunk(x + z + 1, y);
			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x + z + 1, y - 2 * (z + 1));

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + z + 1;
			current[1][2] = y - 2 * (z + 1);

			current[0][3] = x;
			current[1][3] = y - z - 1;

		} else
			collision = true;
		break;
	}
	case 13:
		// Pionowe T  I-
	{
		if (!screen[x + 3 * (z + 1)][y]
				&& !screen[x + 2 * (z + 1)][y - z - 1]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x + z + 1, y - z - 1);

			DrawChunk(x + 3 * (z + 1), y);
			DrawChunk(x + 2 * (z + 1), y - z - 1);

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + 2 * (z + 1);
			current[1][1] = y;

			current[0][2] = x + 3 * (z + 1);
			current[1][2] = y;

			current[0][3] = x + 2 * (z + 1);
			current[1][3] = y - z - 1;

		} else
			collision = true;
		break;
	}
	case 14:
		// Pionowe T  odwrocone -I
	{
		if (!screen[x + 3 * (z + 1)][y]
				&& !screen[x + 2 * (z + 1)][y + z + 1]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x + z + 1, y + z + 1);

			DrawChunk(x + 3 * (z + 1), y);
			DrawChunk(x + 2 * (z + 1), y + z + 1);

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + 2 * (z + 1);
			current[1][1] = y;

			current[0][2] = x + 3 * (z + 1);
			current[1][2] = y;

			current[0][3] = x + 2 * (z + 1);
			current[1][3] = y + z + 1;

		} else
			collision = true;
		break;
	}
	case 15:
		// Poziome Z	-|_
	{
		if (!screen[x + z + 1][y] && !screen[x + 2 * (z + 1)][y - z - 1]
				&& !screen[x + 2 * (z + 1)][y - 2 * (z + 1)]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x, y - z - 1);
			ClearChunk(x + z + 1, y - 2 * (z + 1));

			DrawChunk(x + z + 1, y);
			DrawChunk(x + 2 * (z + 1), y - z - 1);
			DrawChunk(x + 2 * (z + 1), y - 2 * (z + 1));

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y - z - 1;

			current[0][3] = x + 2 * (z + 1);
			current[1][3] = y - 2 * (z + 1);

		} else
			collision = true;
		break;
	}
	case 16:
		// Poziome odworcone Z	_|-
	{
		if (!screen[x + z + 1][y] && !screen[x + z + 1][y - z - 1]
				&& !screen[x][y - 2 * (z + 1)]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x - z - 1, y - z - 1);
			ClearChunk(x - z - 1, y - 2 * (z + 1));

			DrawChunk(x + z + 1, y);
			DrawChunk(x + z + 1, y - z - 1);
			DrawChunk(x, y - 2 * (z + 1));

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x;
			current[1][2] = y - z - 1;

			current[0][3] = x;
			current[1][3] = y - 2 * (z + 1);

		} else
			collision = true;
		break;
	}

	case 17:
		// Poziome odworcone Z	_|-
	{
		if (!screen[x + 2 * (z + 1)][y] && !screen[x + z + 1][y - z - 1]) {
			collision = false;
			ClearChunk(x, y);
			ClearChunk(x - z - 1, y - z - 1);

			DrawChunk(x + 2 * (z + 1), y);
			DrawChunk(x + z + 1, y - z - 1);

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x;
			current[1][1] = y - z - 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y;

			current[0][3] = x;
			current[1][3] = y - z - 1;

		} else
			collision = true;
		break;
	}
	case 18:
		// Poziome odworcone Z	-|_
	{
		if (!screen[x + z + 1][y] && !screen[x + 2 * (z + 1)][y - z - 1]) {
			collision = false;
			ClearChunk(x - z - 1, y);
			ClearChunk(x, y - z - 1);

			DrawChunk(x + z + 1, y);
			DrawChunk(x + 2 * (z + 1), y - z - 1);

			current[0][0] = x + z + 1;
			current[1][0] = y;

			current[0][1] = x + z + 1;
			current[1][1] = y - z - 1;

			current[0][2] = x + 2 * (z + 1);
			current[1][2] = y - z - 1;

			current[0][3] = x;
			current[1][3] = y;

		} else
			collision = true;
		break;
	}
	default:
		break;
	}

}

void SpawnBlock(int x, int y) {
	switch (shape) {
	case 0: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x + z + 1][y] == true
				|| screen[x + z + 1][y - z - 1] == true)
			GameOver();

		DrawShapeSquare(x, y);
		break;
	}
	case 1: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x][y - 3 * (z + 1)] == true)
			GameOver();

		DrawShapeRectangleH(x, y);
		break;

	}
	case 2: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x + 3 * (z + 1)][y] == true)
			GameOver();

		DrawShapeRectangleV(x, y);
		break;
	}
	case 3: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x - z - 1][y - 2 * (z + 1)] == true)
			GameOver();

		DrawShapeLH(x, y);
		break;

	}
	case 4: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x - z - 1][y] == true)
			GameOver();

		DrawShapeLHInv(x, y);
		break;

	}
	case 5: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x + z + 1][y - 2 * (z + 1)] == true)
			GameOver();

		DrawShapeLHMir(x, y);
		break;

	}
	case 6: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x + z + 1][y] == true)
			GameOver();

		DrawShapeLHInvMir(x, y);
		break;

	}
	case 7: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x + 2 * (z + 1)][y - z - 1] == true)
			GameOver();

		DrawShapeLV(x, y);
		break;

	}
	case 8: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x + 2 * (z + 1)][y + z + 1] == true)
			GameOver();

		DrawShapeLVInv(x, y);
		break;

	}
	case 9: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x][y - z - 1] == true)
			GameOver();

		DrawShapeLVMir(x, y);
		break;

	}
	case 10: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x][y + z + 1] == true)
			GameOver();

		DrawShapeLVInvMir(x, y);
		break;

	}

	case 11: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x + z + 1][y - z - 1] == true)
			GameOver();

		DrawShapeTH(x, y);
		break;

	}
	case 12: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x - z - 1][y - z - 1] == true)
			GameOver();

		DrawShapeTHInv(x, y);
		break;

	}
	case 13: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x + z + 1][y - z - 1] == true)
			GameOver();

		DrawShapeTV(x, y);
		break;

	}
	case 14: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x + z + 1][y + z + 1] == true)
			GameOver();

		DrawShapeTVInv(x, y);
		break;

	}
	case 15: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x + z + 1][y - 2 * (z + 1)] == true
				|| screen[x + z + 1][y - z - 1] == true)
			GameOver();

		DrawShapeZH(x, y);
		break;

	}
	case 16: {
		if (screen[x + z + 1][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x + z + 1][y - z - 1] == true)
			GameOver();

		DrawShapeZHInv(x, y);
		break;

	}
	case 17: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x + z + 1][y] == true
				|| screen[x - z - 1][y - z - 1] == true)
			GameOver();

		DrawShapeZV(x, y);
		break;

	}
	case 18: {
		if (screen[x][y] == true || screen[x - z - 1][y] == true
				|| screen[x][y - z - 1] == true
				|| screen[x + z + 1][y - z - 1] == true)
			GameOver();

		DrawShapeZVInv(x, y);
		break;

	}

	default:
		break;
	}
}

void Turn() {
	int x = current[0][0];
	int y = current[1][0];

	int tmpx, tmpy;

	switch (shape) {
	case 0: {

		break;
	}
	case 1: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x + z + 1][y] != true && screen[x + 2 * (z + 1)][y] != true
				&& screen[x + 3 * (z + 1)][y] != true) {
			shape = 2;
			tmpx = current[0][0];
			tmpy = current[1][2];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeRectangleV(tmpx, tmpy);

		}
		break;
	}
	case 2: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x][y - z - 1] != true && screen[x][y + z + 1] != true
				&& screen[x][y + 2 * (z + 1)] != true
				&& screen[x][y + 1] != true && screen[x][y + z + 1 + 1] != true) {
			shape = 1;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeRectangleH(tmpx, tmpy + 2 * (z + 1));

		}
		break;
	}
	case 3: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x + z + 1][y] != true && screen[x + 2 * (z + 1)][y] != true
				&& screen[x + 2 * (z + 1)][y - z - 1] != true) {
			shape = 7;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeLV(tmpx, tmpy);

		}
		break;
	}
	case 4: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x + z + 1][y] != true && screen[x + 2 * (z + 1)][y] != true) {
			shape = 9;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeLVMir(tmpx, tmpy);

		}
		break;
	}
	case 5: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x + z + 1][y] != true && screen[x + 2 * (z + 1)][y] != true
				&& screen[x + 2 * (z + 1)][y + 1] != true) {
			shape = 8;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeLVInv(tmpx, tmpy);

		}
		break;
	}
	case 6: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x + 2 * (z + 1)][y] != true && screen[x][y + 1] != true) {
			shape = 10;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeLVInvMir(tmpx, tmpy);

		}
		break;
	}
	case 7: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x][y - z - 1] != true && screen[x][y - 2 * (z + 1)] != true) {
			shape = 6;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][2], current[1][0] - z - 1);

			DrawShapeLHInvMir(tmpx, tmpy);

		}
		break;
	}
	case 8: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x][y - z - 1] != true && screen[x][y - 2 * (z + 1)] != true
				&& screen[x - z - 1][y] != true) {

			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeLHInv(tmpx, tmpy);
			shape = 4;
		}
		break;
	}
	case 9: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x][y - 2 * (z + 1)] != true
				&& screen[x + z + 1][y - 2 * (z + 1)] != true) {
			shape = 5;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeLHMir(tmpx, tmpy);

		}
		break;
	}
	case 10: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x][y - z - 1] != true && screen[x][y - 2 * (z + 1)] != true
				&& screen[x - z - 1][y - 2 * (z + 1)] != true) {

			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeLH(tmpx, tmpy);
			shape = 3;
		}
		break;
	}

	case 11: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x + z + 1][y] != true && screen[x + 2 * (z + 1)][y] != true
				&& screen[x + z + 1][y + 1] != true) {
			shape = 14;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeTVInv(tmpx, tmpy);

		}
		break;
	}
	case 12: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x + z + 1][y] != true && screen[x + 2 * (z + 1)][y] != true
				&& screen[x + z + 1][y - z - 1] != true) {
			shape = 13;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeTV(tmpx, tmpy);

		}
		break;
	}
	case 13: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x][y - z - 1] != true && screen[x][y - 2 * (z + 1)] != true) {
			shape = 11;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeTH(tmpx, tmpy);

		}
		break;
	}
	case 14: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x][y - z - 1] != true && screen[x][y - 2 * (z + 1)] != true
				&& screen[x - z - 1][y - z - 1] != true) {
			shape = 12;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeTHInv(tmpx, tmpy);

		}
		break;
	}
	case 15: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x + z + 1][y] != true && screen[x - z - 1][y - z - 1] != true) {
			shape = 17;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeZV(tmpx, tmpy);

		}
		break;
	}
	case 16: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x - z - 1][y] != true && screen[x + z + 1][y - z - 1] != true) {
			shape = 18;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeZVInv(tmpx, tmpy);

		}
		break;
	}
	case 17: {
		// sprawdzenie czy obrot jest mozliwy

		if (screen[x][y - 2 * (z + 1)] != true
				&& screen[x + z + 1][y - z - 1] != true) {
			shape = 16;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeZHInv(tmpx, tmpy);

		}
		break;
	}
	case 18: {
		// sprawdzenie czy obrot jest mozliwy
		if (screen[x + z + 1][y - 2 * (z + 1)] != true) {
			shape = 15;
			tmpx = current[0][0];
			tmpy = current[1][0];

			//czyszczenie miejsca obecnego
			ClearChunk(current[0][0], current[1][0]);
			ClearChunk(current[0][1], current[1][1]);
			ClearChunk(current[0][2], current[1][2]);
			ClearChunk(current[0][3], current[1][3]);

			DrawShapeZH(tmpx, tmpy);

		}
		break;
	}

	default:
		break;

	}
}
