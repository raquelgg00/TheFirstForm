#ifndef JUEGOSTATE_H
#define JUEGOSTATE_H
class JuegoState {
 public:
  virtual void CambiarEstado() = 0;
  virtual void render(float ) = 0;
  virtual void input() = 0;
  virtual void update() = 0;
  virtual ~JuegoState(){};
};

#endif