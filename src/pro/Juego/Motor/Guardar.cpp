#include "Guardar.h"

// Singleton
Guardar* Guardar::pinstance = 0;
Guardar* Guardar::Instance(){
    if(pinstance == 0){
        pinstance = new Guardar;

    }
    return pinstance;
}

Guardar::Guardar(){
    musica=0;
    sonido=0;
    resolucion=0;
    nivelMax=0;
    numMonedas=0;

    // Cargo tmx
    doc.LoadFile("Motor/save.tmx");

    // apuntamos a opciones y partida
    XMLElement* opciones=doc.FirstChildElement("opciones");
    XMLElement* partida=doc.FirstChildElement("partida");
    
    if(opciones!=NULL){
        XMLElement* volMusica=opciones->FirstChildElement("musica");
        volMusica->QueryIntAttribute("volumen", &musica);

        XMLElement* volSonido=opciones->FirstChildElement("sonido");
        volSonido->QueryIntAttribute("volumen", &sonido);

        XMLElement* resPantalla=opciones->FirstChildElement("resolucion");
        resPantalla->QueryIntAttribute("tam", &resolucion);
    }
    if(partida!=NULL){
        XMLElement* nivel=partida->FirstChildElement("nivel");
        nivel->QueryIntAttribute("max", &nivelMax);

        XMLElement* monedas=partida->FirstChildElement("monedas");
        monedas->QueryIntAttribute("max", &numMonedas);

        XMLElement* hab=partida->FirstChildElement("habilidades");
        hab->QueryIntAttribute("max", &habilidades);
    }
}

Guardar::~Guardar(){
    if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }
}

void Guardar::setMusica(int vol){
    XMLElement* opciones=doc.FirstChildElement("opciones");

    if(opciones!=NULL){
        XMLElement* volMusica=opciones->FirstChildElement("musica");
        volMusica->SetAttribute("volumen",vol);
        doc.SaveFile("Motor/save.tmx");
        musica = vol;
    }
}

void Guardar::setSonido(int vol){
    XMLElement* opciones=doc.FirstChildElement("opciones");

    if(opciones!=NULL){
        XMLElement* volSonido=opciones->FirstChildElement("sonido");
        volSonido->SetAttribute("volumen",vol);
        doc.SaveFile("Motor/save.tmx");
        sonido = vol;
    }
}

void Guardar::setResolucion(int res){
    XMLElement* opciones=doc.FirstChildElement("opciones");

    if(opciones!=NULL){
        XMLElement* resPantalla=opciones->FirstChildElement("resolucion");
        resPantalla->SetAttribute("tam",res);
        doc.SaveFile("Motor/save.tmx");
        resolucion = res;
    }
}

void Guardar::setResolucionAtr(int res){
    resolucion = res;
}

void Guardar::setNivel(int niv){
    XMLElement* partida=doc.FirstChildElement("partida");

    if(partida!=NULL&&niv>nivelMax){
        XMLElement* nivel=partida->FirstChildElement("nivel");
        nivel->SetAttribute("max",niv);
        doc.SaveFile("Motor/save.tmx");
        nivelMax = niv;
    }
}

void Guardar::setMonedas(int mon){
    XMLElement* partida=doc.FirstChildElement("partida");

    if(partida!=NULL){
        XMLElement* monedas=partida->FirstChildElement("monedas");
        monedas->SetAttribute("max",mon);
        doc.SaveFile("Motor/save.tmx");
        numMonedas = mon;
    }
}


void Guardar::setHabilidades(int hab){
    XMLElement* partida=doc.FirstChildElement("partida");

    if(partida!=NULL&&hab>=habilidades){
        XMLElement* habilid=partida->FirstChildElement("habilidades");
        habilid->SetAttribute("max",hab);
        doc.SaveFile("Motor/save.tmx");
        habilidades = hab;
    }
}

void Guardar::setHabilidadesAtrib(int hab){
    habilidades = hab;
}

void Guardar::reiniciarPartida(){
    XMLElement* partida=doc.FirstChildElement("partida");
    if(partida!=NULL){
        XMLElement* habilid=partida->FirstChildElement("habilidades");
        habilid->SetAttribute("max",0);
        XMLElement* nivel=partida->FirstChildElement("nivel");
        nivel->SetAttribute("max",0);
        doc.SaveFile("Motor/save.tmx");
        nivelMax = 0;
        habilidades = 0;
    }
}