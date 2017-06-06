#include <stdbool.h>
















//Funkcje matematyczne
int Pow(int a, int b);
int Abs(int a);
//---------------------

//Ranking
void AddToRank(int score, int name);
void FillRank();
void DrawRank();
//--------------
void DrawNumber(int x, int y, int size, int number, bool light);
void DrawLetter(int x, int y, int size, int letter, bool light);
//----------------------------

//POMOCNICZE
void DrawTetrisBorder();
void DrawPointer(int x, int y, int size, bool light);
void DrawChangePointerUP(int x, int y, int size, bool light);
void DrawChangePointerDOWN(int x, int y, int size, bool light);
void DrawChunk(int x, int y);
void ClearChunk(int x, int y);
void ClearChunk2(int x, int y);
void ParseScore(int x, int y, int size);
//---------------------

//SHAPES
void DrawShapeSquare(int x, int y);
void DrawShapeRectangleH(int x, int y);
void DrawShapeRectangleV(int x, int y);

void DrawShapeLH(int x, int y);
void DrawShapeLHInv(int x, int y);
void DrawShapeLHMir(int x, int y);
void DrawShapeLHInvMir(int x, int y);

void DrawShapeLV(int x, int y);
void DrawShapeLVInv(int x, int y);
void DrawShapeLVMir(int x, int y);
void DrawShapeLVInvMir(int x, int y);

void DrawShapeTH(int x, int y);
void DrawShapeTHInv(int x, int y);
void DrawShapeTV(int x, int y);
void DrawShapeTVInv(int x, int y);

void DrawShapeZH(int x, int y);
void DrawShapeZHInv(int x, int y);
void DrawShapeZV(int x, int y);
void DrawShapeZVInv(int x, int y);
//----------

//WORDS
void WriteFUNCTOSTART(int x, int y, int size, bool light);
void WriteSCORE(int x, int y, int size, int score, bool light);
void WriteNEWGAME(int x, int y, int size, bool light);
void WriteRANK(int x, int y, int size, bool light);
void WriteEXIT(int x, int y, int size, bool light);
void WriteEND(int x, int y, int size, bool light);
void WriteTETRIS(int x, int y, int size, bool light);
void WriteGAMEOVER(int x, int y, int size, bool light);
void WriteSETNICK(int x, int y, int size, bool light);
//-----------

//MENUS
void TetrisMenu();
void DrawSnake(int x, int y);
//-----------

//ENGINE
void MoveScreenDownFrom(int number);
void CheckHorizontal();
void ClearRow(int number);
void DrawNumber(int x, int y, int size, int number, bool light);
void ParseScore(int x, int y, int number);
//-----------

//MAIN SCREEN DRAW
void ClearScreen();
void DrawScreen();

void FillREC(int x, int y, int x1, int y1, bool light);

//--------------

