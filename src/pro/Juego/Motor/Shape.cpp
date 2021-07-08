#include "Shape.h"

Shape::Shape(){
    rectangle=NULL;
    triangle=NULL;
    circle=NULL;
    convex=NULL;
}

//Le pasamos por parametro el tipo de forma que queremos
Shape::Shape(char type[]){
    if(strcmp(type, "rectangle")==0){
        strcpy(shape_type, "rectangle");
        rectangle = new Rectangle();
    }else if(strcmp(type, "circle")==0){
        strcpy(shape_type, "circle");
        circle = new Circle();
    }else if(strcmp(type, "convex")==0){
        strcpy(shape_type, "convex");
        convex = new Convex();
    }else if(strcmp(type, "triangle")==0){
        strcpy(shape_type, "triangle");
        triangle = new Triangle();
    }else{
        strcpy(shape_type, "");
    }
}

// Destructor
Shape::~Shape(){
    if(rectangle != NULL){
        delete rectangle;
    }
    if(triangle != NULL){
        delete triangle;
        triangle=NULL;
    }
    if(convex != NULL){
        delete convex;
        convex=NULL;
    }
    if(circle != NULL){
        delete circle;
        circle=NULL;
    }
}

void Shape::setFillColor(int r, int g, int b){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->setFillColor(r,g,b);
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->setFillColor(r,g,b);
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->setFillColor(r,g,b);
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->setFillColor(r,g,b);
        }
    }
}
void Shape::setFillColor(char color[]){
    sf::Color c = sf::Color::White;
    if(strcmp(color, "red")==0){
        c = sf::Color::Red;
    }else if(strcmp(color, "blue")==0){
        c = sf::Color::Blue;
    }else if(strcmp(color, "black")==0){
        c = sf::Color::Black;
    }else if(strcmp(color, "yellow")==0){
        c = sf::Color::Yellow;
    }else if(strcmp(color, "green")==0){
        c = sf::Color::Green;
    }else if(strcmp(color, "cyan")==0){
        c = sf::Color::Cyan;
    }else if(strcmp(color, "magenta")==0){
        c = sf::Color::Magenta;
    }else if(strcmp(color, "transparent")==0){
        c = sf::Color::Transparent;
    }
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->setFillColor(c);
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->setFillColor(c);
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->setFillColor(c);
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->setFillColor(c);
        }
    }
}

void Shape::setBorder(float thickness, int r, int g, int b){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->setOutlineThickness(thickness);
            rectangle->setOutlineColor(r,g,b);
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->setOutlineThickness(thickness);
            circle->setOutlineColor(r,g,b);
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->setOutlineThickness(thickness);
            convex->setOutlineColor(r,g,b);
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->setOutlineThickness(thickness);
            triangle->setOutlineColor(r,g,b);
        }
    }
}

void Shape::setSize(float x, float y){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->setSize(x,y);
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->setSize(x);
        }
        else if(strcmp(shape_type, "convex")==0){
            x = (int)ceil(x);
            convex->setPointCount(x);
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->setSize(x);
        }
    }
}

void Shape::setConvexPoints(int point, float x, float y){
    if(strcmp(shape_type,"")!= 0 && strcmp(shape_type, "convex")==0){
        convex->setPoint(point, x, y);
    }
}


void Shape::setPosition(float x, float y){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->setPosition(x,y);
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->setPosition(x,y);
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->setPosition(x,y);
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->setPosition(x,y);
        }
    }
}

void Shape::drawShape(){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->drawRectangle();
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->drawCircle();
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->drawConvex();
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->drawTriangle();
        }
    }
}
sf::RectangleShape Shape::getRectangle(){
    sf::RectangleShape dev;
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            return rectangle->getRectangle();
        }  
    }
    return dev;
}
sf::CircleShape Shape::getCircle(){
    sf::CircleShape dev;
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "circle")==0){
            return circle->getCircle();
        }   
    }
    return dev;
}
sf::ConvexShape Shape::getConvex(){
    sf::ConvexShape dev;
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "convex")==0){
            return convex->getConvex();
        }   
    }
    return dev;
}

sf::CircleShape Shape::getTriangle(){
    sf::CircleShape dev;
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "triangle")==0){
            return triangle->getTriangle();
        }   
    }
    return dev; 
}

void Shape::setScale(float x, float y){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->setScale(x,y);
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->setScale(x,y);
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->setScale(x,y);
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->setScale(x,y);
        }
    }
}

void Shape::setRotation(float x){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->setRotation(x);
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->setRotation(x);
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->setRotation(x);
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->setRotation(x);
        }
    }
}

void Shape::getGlobalBounds(){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->getGlobalBounds();
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->getGlobalBounds();
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->getGlobalBounds();
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->getGlobalBounds();
        }
    }
}

void Shape::getXPosition(){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->getXPosition();
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->getXPosition();
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->getXPosition();
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->getXPosition();
        }
    }
}

void Shape::getYPosition(){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->getYPosition();
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->getYPosition();
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->getYPosition();
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->getYPosition();
        }
    }
}

void Shape::getRotation(){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->getRotation();
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->getRotation();
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->getRotation();
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->getRotation();
        }
    }
}

void Shape::getScale(){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->getScale();
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->getScale();
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->getScale();
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->getScale();
        }
    }
}

void Shape::move(float x, float y){
    if(strcmp(shape_type,"")!= 0){
        if(strcmp(shape_type, "rectangle")==0){
            rectangle->move(x,y);
        }
        else if(strcmp(shape_type, "circle")==0){
            circle->move(x,y);
        }
        else if(strcmp(shape_type, "convex")==0){
            convex->move(x,y);
        }
        else if(strcmp(shape_type, "triangle")==0){
            triangle->move(x,y);
        }
    }
}