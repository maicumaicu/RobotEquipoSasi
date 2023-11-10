typedef struct {
  int IN2;
  int IN1;
  int EN;
} motor;

typedef struct {
  int PIN;
  int estado;
  int flag;
} button;

typedef struct {
  int Lados[4];
  int visitado;
  int final;
  int distance;
} Node;

typedef struct {
  int x;
  int y;
} Position;

struct Stack {
  int top;
  unsigned capacity;
  Position *array;
};
