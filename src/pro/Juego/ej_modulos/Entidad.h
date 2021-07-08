#ifndef ENTIDAD_H
#define ENTIDAD_H
#include "Sprite.h"

class Entidad {
  public:
  
  virtual void setPosition(int, int)=0;
  virtual void updatemover()=0;
  virtual void render(float)=0;
  virtual void onCollisionPlayer(int)=0;
  virtual void setColisionesMapa(bool *)=0;
  virtual float getX()=0;
  virtual float getY()=0;
  virtual Sprite* getSprite()=0;
  virtual ~Entidad(){};

};

#endif