#include <stdbool.h>
void DrawA(int x, int y,int size, bool light);
void DrawB(int x, int y,int size, bool light);
void DrawC(int x, int y,int size, bool light);
void DrawD(int x, int y,int size, bool light);
void DrawE(int x, int y,int size, bool light);
void DrawF(int x, int y,int size, bool light);
void DrawG(int x, int y,int size, bool light);
void DrawH(int x, int y,int size, bool light);
void DrawI(int x, int y,int size, bool light);
void DrawJ(int x, int y,int size, bool light);
void DrawDoubleDot(int x, int y);
void DrawK(int x, int y,int size, bool light);
void DrawL(int x, int y,int size, bool light);
void DrawM(int x, int y,int size, bool light);
void DrawN(int x, int y,int size, bool light);
void DrawO(int x, int y,int size, bool light);
void DrawQ(int x, int y,int size, bool light);
void DrawU(int x, int y,int size, bool light);
void DrawP(int x, int y,int size, bool light);
void DrawR(int x, int y,int size, bool light);
void DrawS(int x, int y,int size, bool light);
void DrawT(int x, int y,int size, bool light);
void DrawW(int x, int y,int size, bool light);
void DrawX(int x, int y,int size, bool light);
void DrawY(int x, int y,int size, bool light);
void DrawZ(int x, int y,int size, bool light);



void Draw0(int x, int y,int size, bool light);
void Draw1(int x, int y,int size, bool light);
void Draw2(int x, int y,int size, bool light);
void Draw3(int x, int y,int size, bool light);
void Draw4(int x, int y,int size, bool light);
void Draw5(int x, int y,int size, bool light);
void Draw6(int x, int y,int size, bool light);
void Draw7(int x, int y,int size, bool light);
void Draw8(int x, int y,int size, bool light);
void Draw9(int x, int y,int size, bool light);


void DrawTetrisBorder();
void DrawFilledRectangle(int x, int y,int x1, int y1);
void DrawChunk(int x, int y);

void DrawShapeSquare(int x, int y);
void DrawShapeRectangleH(int x, int y);
void DrawShapeRectangleV(int x, int y);
void DrawShapeL(int x, int y);

void AddToRank(int score, int name);
void FillRank();
void WriteSCORE(int x, int y,int size,int score, bool light);
void WriteNEWGAME(int x, int y,int size, bool light);
void WriteTETRIS(int x, int y,int size, bool light);
void WriteRANK(int x, int y,int size, bool light);
void WriteEND(int x, int y,int size, bool light);
void WriteGAMEOVER(int x, int y, int size, bool light);
void WriteSETNICK(int x, int y, int size, bool light);
void WriteFUNCTOSTART(int x, int y, int size, bool light);

void DrawChangePointerUP(int x, int y, int size);
void ClearChangePointerUP(int x, int y, int size);
void DrawChangePointerDOWN(int x, int y, int size);
void ClearChangePointerDOWN(int x, int y, int size) ;

void CheckHorizontal();
void ClearPointer(int x, int y,int size);
void DrawSnake(int x, int y);
void TETMenu(int x, int y,int size);

void ClearScreen();
void DrawRank();

void DrawNumber(int x, int y, int size, int number, bool light);
void DrawLetter(int x, int y, int size, int letter, bool light);
void ParseScore(int x, int y,int size);
void FillREC(int x, int y, int x1, int y1, bool light);
void ClearRow(int number);
void TetrisMenu();
void DrawPointer(int x, int y, int size);

void MoveRight();
void MoveLeft();
void MoveDown();
void Turn();
void SpawnBlock();

void DrawScreen();
