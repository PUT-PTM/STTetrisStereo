#include <TetrisLogic.h>
#include <stdbool.h>
#include "tm_stm32f4_pcd8544.h"

bool screen[84][48];
int current[2][4];
int z = 4;
int shape = -1;
bool collision = false;
bool gameOver = false;
int score = 0;
long int rank[7][2] = { 0 };

//Funkcje matematyczne
int Pow(int a, int b) {
	int wynik = 1;

	while (b--) {
		wynik *= a;
	}

	return wynik;
}

int Abs(int a) {
	if (a < 0)
		a = a * (-1);
	return a;
}
//---------------------

//Ranking
void AddToRank(int score, int name) {

	for (int i = 0; i < 7; i++)
		if (rank[i][0] <= score) {
			for (int j = i; j < 7; j++) {
				rank[6 - j][0] = rank[6 - (j + 1)][0];
				rank[6 - j][1] = rank[6 - (j + 1)][1];
			}

			rank[i][0] = score;
			rank[i][1] = name;
			i = 10;
		}
}

void FillRank() {
	rank[0][0] = 0;
	rank[0][1] = 11111111;

	rank[1][0] = 0;
	rank[1][1] = 11111111;

	rank[2][0] = 0;
	rank[2][1] = 11111111;

	rank[3][0] = 0;
	rank[3][1] = 11111111;

	rank[4][0] = 0;
	rank[4][1] = 11111111;

	rank[5][0] = 0;
	rank[5][1] = 11111111;

	rank[6][0] = 0;
	rank[6][1] = 11111111;
}

void DrawRank() {

	int x = 5;
	int y = 47;

	for (int i = 0; i < 7; i++) {
		screen[x + 4 + (i * 11)][y - 3] = true;
	}
	Draw1(x, y, 2, true);
	Draw2(x + 11, y, 2, true);
	Draw3(x + 22, y, 2, true);
	Draw4(x + 33, y, 2, true);

	Draw5(x + 44, y, 2, true);

	Draw6(x + 55, y, 2, true);

	Draw7(x + 66, y, 2, true);

	int scr[4] = { 0 };

	long int temp = 0;
	long int letterResult = 0;

	for (int j = 0; j < 7; j++) {

		letterResult = rank[j][1];

		scr[0] = rank[j][0] / 1000;
		scr[1] = (rank[j][0] - scr[0] * 1000) / 100;
		scr[2] = (rank[j][0] - scr[0] * 1000 - scr[1] * 100) / 10;
		scr[3] = (rank[j][0] - scr[0] * 1000 - scr[1] * 100 - scr[2] * 10);

		for (int i = 0; i < 4; i++) {
			if (i * 100 != 0)
				temp = 1000000 / Pow(100, i);
			else
				temp = 1000000;

			DrawLetter(x + (j * 11), y - (6 + i * 5), 2, letterResult / temp,
					true);

			if (i == 0)
				letterResult = letterResult - ((letterResult / temp) * 1000000);
			else
				letterResult = letterResult
						- ((letterResult / temp) * (1000000 / Pow(100, i)));

			DrawNumber(x + (j * 11), y - (5 + i * 5) - 23, 2, scr[i], true);
		}
	}

	DrawScreen();

}
//--------------

//LETTERS
void DrawA(int x, int y, int size, bool light) {
	//1
	for (int i = 0; i < size + 1; i++) {
		screen[x][y - i] = light;
		screen[x + i][y - size] = light;
		screen[x + size + i][y - size] = light;
		screen[x + size + i][y] = light;

	}

	for (int i = 0; i < size; i++) {
		screen[x + i][y] = light;
		screen[x + size][y - i] = light;
	}

}
void DrawB(int x, int y, int size, bool light) {
	DrawO(x, y, size, light);
	for (int i = 0; i < size; i++)
		screen[x + size][y - i] = light;

	screen[x + size + size][y - size] = !light;
	screen[x][y - size] = !light;
}
void DrawC(int x, int y, int size, bool light) {
	for (int i = 0; i < size + 1; i++) {
		screen[x + (size * 2)][y - i] = light;
		screen[x][y - i] = light;
	}

	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y] = light;

}
void DrawD(int x, int y, int size, bool light) {
	DrawO(x, y, size, light);
	screen[x + size + size][y - size] = !light;
	screen[x][y - size] = !light;
}
void DrawE(int x, int y, int size, bool light) {
	for (int i = 0; i < size + 1; i++) {
		screen[x][y - i] = light;
		screen[x + size][y - i] = light;
		screen[x + (size * 2)][y - i] = light;
	}

	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y] = light;

}
void DrawF(int x, int y, int size, bool light) {

	for (int i = 0; i < size + 1; i++) {
		screen[x][y - i] = light;
		screen[x + size][y - i] = light;
	}

	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y] = light;

}
void DrawG(int x, int y, int size, bool light) {
	DrawC(x, y, size, light);

	for (int i = 0; i < size / 2 + 1; i++)
		screen[x + size][y - (size / 2) - i] = light;

	for (int i = 0; i < size; i++)
		screen[x + size + i][y - size] = light;
}
void DrawH(int x, int y, int size, bool light) {
	for (int i = 0; i < size * 2 + 1; i++) {
		screen[x + i][y] = light;
		screen[x + i][y - size] = light;
	}

	for (int i = 0; i < size; i++)
		screen[x + size][y - i] = light;
}
void DrawI(int x, int y, int size, bool light) {

	for (int i = 0; i < size * 2 + 1; i++) {
		screen[x + i][y - (size / 2)] = light;
	}

}
void DrawJ(int x, int y, int size, bool light) {
	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y - size] = light;

	for (int i = 0; i < size; i++) {
		screen[x + size * 2][y - size + i] = light;
		screen[x + size + i][y] = light;
	}

}
void DrawK(int x, int y, int size, bool light) {

	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y] = light;

	for (int i = 0; i < size; i++) {
		screen[x + i][y] = light;
		screen[x + size - i][y - i] = light;
		screen[x + size + i][y - i] = light;
	}

	screen[x][y - size] = light;
	screen[x + (size * 2)][y - size] = light;
}
void DrawL(int x, int y, int size, bool light) {
	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y] = light;
	for (int i = 0; i < size; i++)
		screen[x + size * 2][y - size + i] = light;

}
void DrawM(int x, int y, int size, bool light) {
	if (size == 2) {
		for (int i = 0; i < size * 2 + 1; i++) {
			screen[x + i][y] = light;
			screen[x + i][y - size] = light;
		}

		screen[x + 1][y - size + 1] = light;

	} else {
		for (int i = 0; i < size * 2 + 1; i++) {
			screen[x + i][y] = light;
			screen[x + i][y - size] = light;
		}

		for (int i = 0; i < 3; i++) {
			screen[x + i][y - 1] = light;
			screen[x + i + 3][y - 2] = light;
			screen[x + i][y - 3] = light;
		}

	}

}
void DrawN(int x, int y, int size, bool light) {

	if (size == 2) {
		for (int i = 0; i < size * 2 + 1; i++) {
			screen[x + i][y] = light;
			screen[x + i][y - size] = light;
		}

		screen[x][y - 1] = light;

	} else {

		for (int i = 0; i < size + 1; i++) {
			screen[x + size + i][y] = light;
			screen[x + size + i][y - size] = light;
		}

		for (int i = 0; i < size; i++) {
			screen[x + i][y] = light;
			screen[x + i][y - size] = light;
		}

		for (int i = 0; i < size - 1; i++) {
			screen[x + i][y - 1] = light;

			screen[x + 3 + i][y - 2] = light;

			screen[x + 6 + i][y - 3] = light;
		}

	}

}
void DrawO(int x, int y, int size, bool light) {

	for (int i = 0; i < size * 2 + 1; i++) {
		screen[(x + i)][y] = light;

		screen[(x + i)][y - size] = light;
	}

	for (int i = 0; i < size + 1; i++) {
		screen[x + (size * 2)][y - i] = light;

		screen[x][y - i] = light;
	}

}
void DrawP(int x, int y, int size, bool light) {

	for (int i = 0; i < size + 1; i++) {
		screen[x][y - i] = light;
		screen[x + size][y - i] = light;
	}

	for (int i = 0; i < size; i++)
		screen[x + i + 1][y - size] = light;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[(x + i)][y] = light;

}
void DrawQ(int x, int y, int size, bool light) {
	DrawO(x, y, size, light);

	if (size == 2) {

		screen[x + size + size][y - 2] = !light;
	} else {
		for (int i = 2; i < size + 1; i++)
			screen[x + size + i][y - i] = light;

	}

}
void DrawR(int x, int y, int size, bool light) {

	for (int i = 0; i < size + 1; i++) {
		screen[x][y - i] = light;
		screen[x + size + i][y - i] = light;
		screen[x + size][y - i] = light;
	}

	for (int i = 0; i < size; i++)
		screen[x + i + 1][y - size] = light;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[(x + i)][y] = light;

}
void DrawS(int x, int y, int size, bool light) {

	for (int i = 0; i < size + 1; i++) {
		screen[x][y - i] = light;
		screen[x + size * 2][y - size + i] = light;
	}

	for (int i = 1; i < size; i++) {
		screen[x + i][y] = light;

		screen[x + size][y - i] = light;

		screen[x + size + i][y - size] = light;
	}

}
void DrawT(int x, int y, int size, bool light) {
	DrawI(x, y, size, light);

	for (int i = 0; i < size + 1; i++)
		screen[x][y - i] = light;

}
void DrawU(int x, int y, int size, bool light) {

	for (int i = 0; i < size * 2 + 1; i++) {
		screen[x + i][y] = light;
		screen[x + i][y - size] = light;
	}

	for (int i = 0; i < size; i++)
		screen[x + size * 2][y - size + i] = light;
}
void DrawV(int x, int y, int size, bool light) {
	if (size == 2) {
		for (int i = 0; i < 4; i++)
			screen[x + i][y] = light;
		for (int i = 0; i < 4; i++)
			screen[x + i][y - size] = light;
		screen[x + 4][y - 1] = light;

	} else {
		screen[x][y] = light;
		screen[x + 1][y] = light;
		for (int i = 0; i < 4; i++)
			screen[x + i + 2][y - 1] = light;

		for (int i = 0; i < 3; i++)
			screen[x + i + 4][y - 2] = light;

		for (int i = 0; i < 2; i++)
			screen[x + i + 6][y - 2] = light;

		screen[x][y - size] = light;
		screen[x + 1][y - size] = light;
		for (int i = 0; i < 4; i++)
			screen[x + i + 2][y - 3] = light;
	}

}
void DrawW(int x, int y, int size, bool light) {
	if (size == 2) {
		DrawU(x, y, size, light);

		screen[x + 3][y - 1] = light;
		screen[x + 4][y - 1] = !light;
	}

	else {
		for (int i = 0; i < size + 1; i++) {
			screen[x + size + i][y] = light;

			screen[x + i][y - size] = light;

			screen[x + size + i][y - size] = light;
		}

		for (int i = 0; i < size; i++)
			screen[x + i][y] = light;

		for (int i = 0; i < 3; i++) {
			screen[x + size + i][y - 1] = light;

			screen[x + size + i - 3][y - 2] = light;

			screen[x + size + i][y - 3] = light;
		}

	}

}
void DrawX(int x, int y, int size, bool light) {
	if (size == 2) {
		for (int i = 0; i < 2; i++) {
			screen[x + i][y] = light;
			screen[x + i][y - size] = light;

			screen[x + i + 3][y] = light;

			screen[x + i + 3][y - size] = light;
		}

		screen[x + 2][y - 1] = light;

	} else {

		for (int i = 0; i < size - 1; i++) {
			screen[x + i][y - 1] = light;

			screen[x + 3 + i][y - 2] = light;

			screen[x + 6 + i][y - 3] = light;

			screen[x + i][y - 3] = light;

			screen[x + 3 + i][y - 2] = light;

			screen[x + 6 + i][y - 1] = light;
		}

		screen[x][y - size] = light;
		screen[x + (size * 2)][y - size] = light;
		screen[x][y] = light;
		screen[x + (size * 2)][y] = light;
	}

}
void DrawY(int x, int y, int size, bool light) {

	if (size == 2) {
		for (int i = 0; i < 3; i++) {
			screen[x + i][y] = light;

			screen[x + i][y - size] = light;
		}

		screen[x + 3][y - 1] = light;
		screen[x + 4][y - 1] = light;

	} else {
		for (int i = 0; i < size + 1; i++)
			screen[x + size + i][y - 2] = light;

		screen[x][y - 4] = light;
		screen[x + 1][y - 4] = light;

		screen[x][y] = light;
		screen[x + 1][y] = light;

		screen[x + 2][y - 3] = light;
		screen[x + 3][y - 3] = light;

		screen[x + 2][y - 1] = light;
		screen[x + 3][y - 1] = light;
	}

}
void DrawZ(int x, int y, int size, bool light) {

	if (size == 2) {
		for (int i = 0; i < 3; i++) {
			screen[x][y - i] = light;

			screen[x + size + size][y - i] = light;
		}

		for (int i = 0; i < 2; i++) {
			screen[x + i][y - size] = light;

			screen[x + i + 3][y] = light;
		}

		screen[x + 2][y - 1] = light;

	} else {
		for (int i = 0; i < size + 1; i++) {
			screen[x][y - i] = light;
			screen[x + size * 2][y - size + i] = light;
		}

		for (int i = 0; i < size - 1; i++) {
			screen[x + i][y - 3] = light;

			screen[x + 3 + i][y - 2] = light;

			screen[x + 6 + i][y - 1] = light;
		}
	}
}

void DrawColon(int x, int y) {
	screen[x + 1][y - 1] = true;
	screen[x + 5][y - 1] = true;
}
void DrawLetter(int x, int y, int size, int letter, bool light) {
	switch (letter) {

	case 1:
		DrawA(x, y, size, light);
		break;
	case 2:
		DrawB(x, y, size, light);
		break;
	case 3:
		DrawC(x, y, size, light);
		break;
	case 4:
		DrawD(x, y, size, light);
		break;
	case 5:
		DrawE(x, y, size, light);
		break;
	case 6:
		DrawF(x, y, size, light);
		break;
	case 7:
		DrawG(x, y, size, light);
		break;
	case 8:
		DrawH(x, y, size, light);
		break;
	case 9:
		DrawI(x, y, size, light);
		break;
	case 10:
		DrawJ(x, y, size, light);
		break;
	case 11:
		DrawK(x, y, size, light);
		break;
	case 12:
		DrawL(x, y, size, light);
		break;
	case 13:
		DrawM(x, y, size, light);
		break;
	case 14:
		DrawN(x, y, size, light);
		break;
	case 15:
		DrawO(x, y, size, light);
		break;
	case 16:
		DrawP(x, y, size, light);
		break;
	case 17:
		DrawQ(x, y, size, light);
		break;
	case 18:
		DrawR(x, y, size, light);
		break;
	case 19:
		DrawS(x, y, size, light);
		break;
	case 20:
		DrawT(x, y, size, light);
		break;
	case 21:
		DrawU(x, y, size, light);
		break;
	case 22:
		DrawV(x, y, size, light);
		break;
	case 23:
		DrawW(x, y, size, light);
		break;
	case 24:
		DrawX(x, y, size, light);
		break;
	case 25:
		DrawY(x, y, size, light);
		break;
	case 26:
		DrawZ(x, y, size, light);
		break;
	}

}
//----------------------------

//NUMBERS
void Draw0(int x, int y, int size, bool light) {
	DrawO(x, y, size, light);

}
void Draw1(int x, int y, int size, bool light) {
	for (int i = 0; i < size; i++)
		screen[x + i][y - size + i] = true;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y - size] = true;
}
void Draw2(int x, int y, int size, bool light) {

	for (int i = 0; i < size + 1; i++) {
		screen[x][y - i] = true;
		screen[x + size * 2][y - size + i] = true;
	}

	for (int i = 1; i < size; i++) {
		screen[x + i][y - size] = true;

		screen[x + size][y - i] = true;

		screen[x + size + i][y] = true;
	}

}
void Draw3(int x, int y, int size, bool light) {

	for (int i = 0; i < size + 1; i++) {
		screen[x][y - i] = true;

		screen[x + size][y - i] = true;

		screen[x + (size * 2)][y - i] = true;
	}

	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y - size] = true;
}
void Draw4(int x, int y, int size, bool light) {

	for (int i = 0; i < size; i++) {
		screen[x + i][y] = true;

		screen[x + i][y - size] = true;

		screen[x + size][y - i] = true;
	}

	for (int i = 0; i < size + 1; i++)
		screen[x + size + i][y - size] = true;

}
void Draw5(int x, int y, int size, bool light) {
	DrawS(x, y, size, light);
}
void Draw6(int x, int y, int size, bool light) {

	for (int i = 0; i < size + 1; i++) {
		screen[x][y - i] = true;
		screen[x + size * 2][y - size + i] = true;
	}

	for (int i = 0; i < size * 2 + 1; i++)
		screen[(x + i)][y] = true;

	for (int i = 0; i < size; i++) {
		screen[x + size][y - i] = true;

		screen[x + size + i][y - size] = true;
	}

}
void Draw7(int x, int y, int size, bool light) {
	for (int i = 0; i < size + 1; i++)
		screen[x][y - i] = true;

	for (int i = 0; i < size * 2 + 1; i++)
		screen[x + i][y - size] = true;
}
void Draw8(int x, int y, int size, bool light) {
	DrawO(x, y, size, light);

	for (int i = 0; i < size; i++)
		screen[x + size][y - i] = true;
}
void Draw9(int x, int y, int size, bool light) {
	Draw5(x, y, size, light);

	for (int i = 0; i < size + 1; i++)
		screen[x + i][y - size] = true;
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
		screen[7][47 - i] = true;
	}

}
void DrawChangePointerUP(int x, int y, int size, bool light) {
	x = x - 2;
	size++;
	for (int i = 0; i < size; i++)
		screen[x][y - i] = light;

	y++;
	for (int i = 1; i < size / 2 + 1; i++)
		screen[x - i][y - i] = light;

	for (int i = 0; i < size / 2 + 1; i++)
		screen[x - ((size / 2) + 1) + i][y - ((size / 2) + 1) - i] = light;

}
void DrawChangePointerDOWN(int x, int y, int size, bool light) {
	size++;
	x = x + (size * 2);

	for (int i = 0; i < size; i++)
		screen[x][y - i] = light;

	y++;
	for (int i = 1; i < size / 2 + 1; i++)
		screen[x + i][y - i] = light;

	for (int i = 0; i < size / 2 + 1; i++)
		screen[x + ((size / 2) + 1) - i][y - ((size / 2) + 1) - i] = light;

}

void DrawPointer(int x, int y, int size, bool light) {
	x = x + 1;
	for (int i = 0; i < size * 2; i++)
		screen[x + i][y] = light;

	for (int i = 0; i < size; i++) {
		screen[x + i][y - i] = light;
		screen[x + (size * 2) - i][y - i] = light;
	}

	screen[x + size / 2 + 2][y - size] = light;

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
void ClearChunk2(int x, int y) {
	for (int i = 0; i < 3; i++) {
		screen[x + i][y] = false;
		screen[x][y - i] = false;
		screen[x + z - 1][y - i] = false;
		screen[x + i][y - z + 1] = false;

		screen[x + z - 1][y - 3] = false;

		screen[x + i][y - i] = false;
	}
}
//---------------------

//SHAPES
void DrawShapeSquare(int x, int y) {
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver = true;

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
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver = true;

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
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver = true;

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
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver = true;

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
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver = true;

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
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver = true;

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
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver = true;

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
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver = true;

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
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver = true;

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
	//if(screen[x][y] == true || screen[x][y-z] == true || screen[x+z][y] == true || screen[x+z][y-z] == true) gameOver = true;

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

//WORDS
void WriteFUNCTOSTART(int x, int y, int size, bool light) {
	DrawF(x, y, size, light);
	y = y - size - 2;
	DrawU(x, y, size, light);
	y = y - size - 2;
	DrawN(x, y, size, light);
	y = y - size - 2;
	DrawC(x, y, size, light);
	y = y - size - 4;
	DrawT(x, y, size, light);
	y = y - size - 2;
	DrawO(x, y, size, light);

	y = y + 4 * size + 10;
	x = x + 10;

	DrawS(x, y, size, light);
	y = y - size - 2;
	DrawT(x, y, size, light);
	y = y - size - 2;
	DrawA(x, y, size, light);
	y = y - size - 2;
	DrawR(x, y, size, light);
	y = y - size - 2;
	DrawT(x, y, size, light);
}
void WriteSCORE(int x, int y, int size, int score, bool light) {

	DrawS(x, y, size, light);
	y = y - size - 2;
	DrawC(x, y, size, light);
	y = y - size - 2;
	DrawO(x, y, size, light);
	y = y - size - 2;
	DrawR(x, y, size, light);
	y = y - size - 2;
	DrawE(x, y, size, light);
	y = y - size - 1;
	DrawColon(x, y);
	y = y - size - 1;

	Draw0(x, y, size, light);
	y = y - size - 2;
	Draw0(x, y, size, light);
	y = y - size - 2;
	Draw0(x, y, size, light);
	y = y - size - 2;
	Draw0(x, y, size, light);
}
void WriteNEWGAME(int x, int y, int size, bool light) {
	DrawN(x, y, size, light);
	y = y - size - 2;
	DrawE(x, y, size, light);
	y = y - size - 2;
	DrawW(x, y, size, light);
	y = y - size - 4;
	DrawG(x, y, size, light);
	y = y - size - 2;
	DrawA(x, y, size, light);
	y = y - size - 2;
	DrawM(x, y, size, light);
	y = y - size - 2;
	DrawE(x, y, size, light);

}
void WriteRANK(int x, int y, int size, bool light) {
	DrawR(x, y, size, light);
	y = y - size - 2;
	DrawA(x, y, size, light);
	y = y - size - 2;
	DrawN(x, y, size, light);
	y = y - size - 2;
	DrawK(x, y, size, light);
}
void WriteEXIT(int x, int y, int size, bool light) {
	DrawE(x, y, size, light);
	y = y - size - 2;
	DrawX(x, y, size, light);
	y = y - size - 2;
	DrawI(x, y, size, light);
	y = y - size - 2;
	DrawT(x, y, size, light);

}
void WriteEND(int x, int y, int size, bool light) {
	DrawG(x, y, size, light);
	y = y - size - 2;
	DrawA(x, y, size, light);
	y = y - size - 2;
	DrawM(x, y, size, light);
	y = y - size - 2;
	DrawE(x, y, size, light);
	y = y - size - 4;

	DrawO(x, y, size, light);
	y = y - size - 2;
	DrawV(x, y, size, light);
	y = y - size - 2;
	DrawE(x, y, size, light);
	y = y - size - 2;
	DrawR(x, y, size, light);

}
void WriteTETRIS(int x, int y, int size, bool light) {
	DrawT(x, y, size, light);
	y = y - size - 3;
	DrawE(x, y, size, light);
	y = y - size - 2;
	DrawT(x, y, size, light);
	y = y - size - 3;
	DrawR(x, y, size, light);
	y = y - size - 2;
	DrawI(x, y, size, light);
	y = y - size - 2;
	DrawS(x, y, size, light);

}
void WriteGAMEOVER(int x, int y, int size, bool light) {
	DrawG(x, y, size, light);
	y = y - size - 2;
	DrawA(x, y, size, light);
	y = y - size - 2;
	DrawM(x, y, size, light);
	y = y - size - 2;
	DrawE(x, y, size, light);
	y = y + 3 * (size + 2);
	x = x + size + 6;
	DrawO(x, y, size, light);
	y = y - size - 2;
	DrawV(x, y, size, light);
	y = y - size - 2;
	DrawE(x, y, size, light);
	y = y - size - 2;
	DrawR(x, y, size, light);

}
void WriteSETNICK(int x, int y, int size, bool light) {

	DrawS(x, y, size, light);
	y = y - size - 2;
	DrawE(x, y, size, light);
	y = y - size - 2;
	DrawT(x, y, size, light);
	y = y - size - 6;
	DrawN(x, y, size, light);
	y = y - size - 2;
	DrawI(x, y, size, light);
	y = y - size - 2;
	DrawC(x, y, size, light);
	y = y - size - 2;
	DrawK(x, y, size, light);

}
//-----------

//MENUs AND LOGOs
void TetrisMenu() {
	int x = 50;
	int y = 42;
	int size = 4;
	WriteNEWGAME(x, y, size, true);
	WriteRANK(x + 12, y, size, true);
	WriteEXIT(x + 24, y, size, true);

	for (int i = 0; i < 48; i++) {
		for (int j = 0; j < 48; j++) {
			screen[i][j] = true;
		}
	}

	WriteTETRIS(x - 44, y, size, false);

	ClearChunk2(x - 28, y);
	ClearChunk2(x - 28, y - 4);
	ClearChunk2(x - 28, y - 8);
	ClearChunk2(x - 24, y - 4);

	ClearChunk2(x - 32, y - 30);
	ClearChunk2(x - 28, y - 26);
	ClearChunk2(x - 32, y - 26);
	ClearChunk2(x - 28, y - 30);

	ClearChunk2(x - 20, y - 12);
	ClearChunk2(x - 20, y - 16);
	ClearChunk2(x - 20, y - 20);
	ClearChunk2(x - 20, y - 24);

	ClearChunk2(x - 20, y - 32);
	ClearChunk2(x - 16, y - 32);
	ClearChunk2(x - 16, y - 36);
	ClearChunk2(x - 12, y - 36);

	ClearChunk2(x - 10, y - 6);
	ClearChunk2(x - 10, y - 10);
	ClearChunk2(x - 14, y - 10);
	ClearChunk2(x - 14, y - 14);
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

//---------------

//ENGINE
void MoveScreenDownFrom(int number) {

	for (int i = number; i >= 0; i--) {
		for (int j = 1; j <= 9; j++) {
			if (screen[i * 5 + 13][j * 5 + 1]) {
				ClearChunk(i * 5 + 13, j * 5 + 1);
				DrawChunk(i * 5 + 13 + 5, j * 5 + 1);
			}
		}
	}
}
void CheckHorizontal() {
	int counter = 0;

	for (int i = 0; i <= 13; i++) {
		for (int j = 1; j <= 9; j++) {
			if (screen[i * 5 + 13][j * 5 + 1])
				counter++;
		}

		if (counter == 9) {
			ClearRow(i);
			MoveScreenDownFrom(i);

			score++;
			FillREC(0, 47, 8, 0, false);
			ParseScore(0, 47, score);

		}

		counter = 0;

	}

	DrawTetrisBorder();

}
void ClearRow(int number) {
	number = number + 1;
	for (int j = 1; j <= 9; j++)
		ClearChunk(number * 5 + 8, j * 5 + 1);
}
void DrawNumber(int x, int y, int size, int number, bool light) {
	switch (number) {
	case 0: {
		Draw0(x, y, size, light);
		break;
	}
	case 1: {
		Draw1(x, y, size, light);
		break;
	}
	case 2: {
		Draw2(x, y, size, light);
		break;
	}
	case 3: {
		Draw3(x, y, size, light);
		break;
	}
	case 4: {
		Draw4(x, y, size, light);
		break;
	}
	case 5: {
		Draw5(x, y, size, light);
		break;
	}
	case 6: {
		Draw6(x, y, size, light);
		break;
	}
	case 7: {
		Draw7(x, y, size, light);
		break;
	}
	case 8: {
		Draw8(x, y, size, light);
		break;
	}
	case 9: {
		Draw9(x, y, size, light);
		break;
	}
	}

}
void ParseScore(int x, int y, int number) {

	int t, s, d, j;

	t = number / 1000;
	s = (number - t * 1000) / 100;
	d = (number - t * 1000 - s * 100) / 10;
	j = (number - t * 1000 - s * 100 - d * 10);

	int size = 3;
	DrawS(x, y, size, true);
	y = y - size - 2;
	DrawC(x, y, size, true);
	y = y - size - 2;
	DrawO(x, y, size, true);
	y = y - size - 2;
	DrawR(x, y, size, true);
	y = y - size - 2;
	DrawE(x, y, size, true);
	y = y - size - 1;
	DrawColon(x, y);
	y = y - size - 1;

	switch (t) {
	case 0: {
		Draw0(x, y, size, true);
		break;
	}
	case 1: {
		Draw1(x, y, size, true);
		break;
	}
	case 2: {
		Draw2(x, y, size, true);
		break;
	}
	case 3: {
		Draw3(x, y, size, true);
		break;
	}
	case 4: {
		Draw4(x, y, size, true);
		break;
	}
	case 5: {
		Draw5(x, y, size, true);
		break;
	}
	case 6: {
		Draw6(x, y, size, true);
		break;
	}
	case 7: {
		Draw7(x, y, size, true);
		break;
	}
	case 8: {
		Draw8(x, y, size, true);
		break;
	}
	case 9: {
		Draw9(x, y, size, true);
		break;
	}

	}
	y = y - size - 2;
//---------------------------------
	switch (s) {
	case 0: {
		Draw0(x, y, size, true);
		break;
	}
	case 1: {
		Draw1(x, y, size, true);
		break;
	}
	case 2: {
		Draw2(x, y, size, true);
		break;
	}
	case 3: {
		Draw3(x, y, size, true);
		break;
	}
	case 4: {
		Draw4(x, y, size, true);
		break;
	}
	case 5: {
		Draw5(x, y, size, true);
		break;
	}
	case 6: {
		Draw6(x, y, size, true);
		break;
	}
	case 7: {
		Draw7(x, y, size, true);
		break;
	}
	case 8: {
		Draw8(x, y, size, true);
		break;
	}
	case 9: {
		Draw9(x, y, size, true);
		break;
	}

	}
	y = y - size - 2;
//--------------------------
	switch (d) {
	case 0: {
		Draw0(x, y, size, true);
		break;
	}
	case 1: {
		Draw1(x, y, size, true);
		break;
	}
	case 2: {
		Draw2(x, y, size, true);
		break;
	}
	case 3: {
		Draw3(x, y, size, true);
		break;
	}
	case 4: {
		Draw4(x, y, size, true);
		break;
	}
	case 5: {
		Draw5(x, y, size, true);
		break;
	}
	case 6: {
		Draw6(x, y, size, true);
		break;
	}
	case 7: {
		Draw7(x, y, size, true);
		break;
	}
	case 8: {
		Draw8(x, y, size, true);
		break;
	}
	case 9: {
		Draw9(x, y, size, true);
		break;
	}

	}
	y = y - size - 2;
//-----------------------
	switch (j) {
	case 0: {
		Draw0(x, y, size, true);
		break;
	}
	case 1: {
		Draw1(x, y, size, true);
		break;
	}
	case 2: {
		Draw2(x, y, size, true);
		break;
	}
	case 3: {
		Draw3(x, y, size, true);
		break;
	}
	case 4: {
		Draw4(x, y, size, true);
		break;
	}
	case 5: {
		Draw5(x, y, size, true);
		break;
	}
	case 6: {
		Draw6(x, y, size, true);
		break;
	}
	case 7: {
		Draw7(x, y, size, true);
		break;
	}
	case 8: {
		Draw8(x, y, size, true);
		break;
	}
	case 9: {
		Draw9(x, y, size, true);
		break;
	}

	}

}
//-----------

//MAIN SCREEN DRAW
void ClearScreen() {
	for (int i = 0; i < 84; i++) {
		for (int j = 0; j < 48; j++) {
			screen[i][j] = false;
			PCD8544_DrawPixel(i, j, PCD8544_Pixel_Clear);

		}
	}
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
	PCD8544_Refresh();
}
void FillREC(int x, int y, int x1, int y1, bool light) {
	int sizeX = Abs(x - x1);
	int sizeY = Abs(y - y1);

	for (int i = 0; i < sizeX + 1; i++) {
		for (int j = 0; j < sizeY + 1; j++) {
			screen[i + x][j + y1] = light;

		}
	}
	DrawScreen();
}
//--------------

//SHAPE MOVEMENT
extern uint32_t TM_RNG_Get(void);

void MoveRight() //shape (0-18)
{
	int x = current[0][0];
	int y = current[1][0];

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
void MoveLeft() //shape (0-18)
{
	int x = current[0][0];
	int y = current[1][0];

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
void MoveDown() //shape (0-18)
{
	int x = current[0][0];
	int y = current[1][0];
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
		if (!screen[x + z + 1][y] && !screen[x + z + 1][y - z - 1]
				&& !screen[x + z + 1][y - 2 * (z + 1)]
				&& !screen[x + z + 1][y - 3 * (z + 1)]) {
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
void SpawnBlock() {
	int x = 13;
	int y = 31;
	int rShape = TM_RNG_Get() % 7;

	while (rShape > 6) {
		rShape = rShape / 2;

	}
	if (rShape < 0)
		rShape = 0;
	switch (rShape) {

	case 0:
		shape = 0;
		break;
	case 1:
		shape = 1;
		break;
	case 2:
		shape = 3;
		break;
	case 3:
		shape = 7;
		break;
	case 4:
		shape = 11;
		break;
	case 5:
		shape = 15;
		break;
	case 6:
		shape = 17;
		break;
	}
	//shape = 5;
	switch (shape) {
	case 0: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x + z + 1][y] == true
				|| screen[x + z + 1][y - z - 1] == true)
			gameOver = true;

		DrawShapeSquare(x, y);
		break;
	}
	case 1: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x][y - 3 * (z + 1)] == true)
			gameOver = true;

		DrawShapeRectangleH(x, y);
		break;

	}
	case 2: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x + 3 * (z + 1)][y] == true)
			gameOver = true;

		DrawShapeRectangleV(x, y);
		break;
	}
	case 3: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x - z - 1][y - 2 * (z + 1)] == true)
			gameOver = true;

		DrawShapeLH(x, y);
		break;

	}
	case 4: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x - z - 1][y] == true)
			gameOver = true;

		DrawShapeLHInv(x, y);
		break;

	}
	case 5: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x + z + 1][y - 2 * (z + 1)] == true)
			gameOver = true;

		DrawShapeLHMir(x, y);
		break;

	}
	case 6: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x + z + 1][y] == true)
			gameOver = true;

		DrawShapeLHInvMir(x, y);
		break;

	}
	case 7: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x + 2 * (z + 1)][y - z - 1] == true)
			gameOver = true;

		DrawShapeLV(x, y);
		break;

	}
	case 8: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x + 2 * (z + 1)][y + z + 1] == true)
			gameOver = true;

		DrawShapeLVInv(x, y);
		break;

	}
	case 9: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x][y - z - 1] == true)
			gameOver = true;

		DrawShapeLVMir(x, y);
		break;

	}
	case 10: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x][y + z + 1] == true)
			gameOver = true;

		DrawShapeLVInvMir(x, y);
		break;

	}

	case 11: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x + z + 1][y - z - 1] == true)
			gameOver = true;

		DrawShapeTH(x, y);
		break;

	}
	case 12: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x - z - 1][y - z - 1] == true)
			gameOver = true;

		DrawShapeTHInv(x, y);
		break;

	}
	case 13: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x + z + 1][y - z - 1] == true)
			gameOver = true;

		DrawShapeTV(x, y);
		break;

	}
	case 14: {
		if (screen[x][y] == true || screen[x + z + 1][y] == true
				|| screen[x + 2 * (z + 1)][y] == true
				|| screen[x + z + 1][y + z + 1] == true)
			gameOver = true;

		DrawShapeTVInv(x, y);
		break;

	}
	case 15: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x + z + 1][y - 2 * (z + 1)] == true
				|| screen[x + z + 1][y - z - 1] == true)
			gameOver = true;

		DrawShapeZH(x, y);
		break;

	}
	case 16: {
		if (screen[x + z + 1][y] == true || screen[x][y - z - 1] == true
				|| screen[x][y - 2 * (z + 1)] == true
				|| screen[x + z + 1][y - z - 1] == true)
			gameOver = true;

		DrawShapeZHInv(x, y);
		break;

	}
	case 17: {
		if (screen[x][y] == true || screen[x][y - z - 1] == true
				|| screen[x + z + 1][y] == true
				|| screen[x - z - 1][y - z - 1] == true)
			gameOver = true;

		DrawShapeZV(x, y);
		break;

	}
	case 18: {
		if (screen[x][y] == true || screen[x - z - 1][y] == true
				|| screen[x][y - z - 1] == true
				|| screen[x + z + 1][y - z - 1] == true)
			gameOver = true;

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
			tmpy = current[1][0];

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

			DrawShapeRectangleH(tmpx, tmpy);

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
//===========================================
