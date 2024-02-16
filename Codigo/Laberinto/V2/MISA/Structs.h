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
