#ifndef FLOTANTEINTERPOLADO_H
#define FLOTANTEINTERPOLADO_H
class FlotanteInterpolado{

    private:
        float x, y;
        float prevX, prevY;

    protected:
        
    public:
        FlotanteInterpolado();
        FlotanteInterpolado(float, float);
        void setPositionXY(float, float);
        void setPositionX(float);
        void setPositionY(float);
        void restaurarPosiciones();
        float getX();
        float getY();
        float getPrevX();
        float getPrevY();
        void reset();
};
#endif
