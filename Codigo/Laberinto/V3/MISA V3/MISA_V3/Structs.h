typedef struct {
  int PIN;
  int estado;
  int flag;
} button;

typedef struct {
  int IN2;
  int IN1;
  int EN;
} motor;

typedef struct{
  float KP;
  float KD;
} pdConfig;

typedef struct {
  char Lados[4];
  char visitado;
  char final;
  char distance;
} Node;

typedef struct {
  char x;
  char y;
} Position;

struct Stack {
  int top;
  unsigned capacity;
  Position *array;
};
