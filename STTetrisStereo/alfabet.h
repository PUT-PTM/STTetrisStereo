void DrawS(int x, int y,int size);
void DrawC(int x, int y,int size);
void DrawO(int x, int y,int size);
void DrawR(int x, int y,int size);
void DrawE(int x, int y,int size);
void DrawDoubleDot(int x, int y);
void DrawG(int x, int y,int size);
void DrawW(int x, int y,int size);
void DrawM(int x, int y,int size);
void DrawA(int x, int y,int size);
void DrawI(int x, int y,int size);
void DrawX(int x, int y,int size);
void DrawK(int x, int y,int size);
void DrawT(int x, int y,int size);
void DrawN(int x, int y,int size);
void DrawV(int x, int y,int size);

void Draw0(int x, int y,int size);
void Draw1(int x, int y,int size);
void Draw2(int x, int y,int size);
void Draw3(int x, int y,int size);
void Draw4(int x, int y,int size);
void Draw5(int x, int y,int size);
void Draw6(int x, int y,int size);
void Draw7(int x, int y,int size);
void Draw8(int x, int y,int size);
void Draw9(int x, int y,int size);


void DrawTetrisBorder();
void DrawFilledRectangle(int x, int y,int x1, int y1);
void DrawChunk(int x, int y);

void DrawShapeSquare(int x, int y);
void DrawShapeRectangleH(int x, int y);
void DrawShapeRectangleV(int x, int y);
void DrawShapeL(int x, int y);

void WriteSCORE(int x, int y,int size,int score);
void WriteNEWGAME(int x, int y,int size);
void WriteTETRIS(int x, int y,int size);
void WriteRANK(int x, int y,int size);
void WriteEND(int x, int y,int size);


void DrawSnake(int x, int y);
void TETMenu(int x, int y,int size);
void DrawTETLogo();


void MoveRight(int x,int y, int shape);
void MoveLeft(int x,int y, int shape);
void MoveDown(int x,int y, int shape);
void Turn();
void SpawnBlock(int x,int y);

void DrawScreen();
