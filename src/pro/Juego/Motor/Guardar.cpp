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
    secreto1=0;
    secreto2=0;
    secreto3=0;
    terminado=0;
    num_muertes = 0;

    // Cargo tmx
    doc.LoadFile("Motor/save.xml");

    // apuntamos a opciones y partida
    tinyxml2::XMLElement* opciones=doc.FirstChildElement("opciones");
    tinyxml2::XMLElement* partida=doc.FirstChildElement("partida");
    
    if(opciones!=NULL){
        tinyxml2::XMLElement* volMusica=opciones->FirstChildElement("musica");
        volMusica->QueryIntAttribute("volumen", &musica);

        tinyxml2::XMLElement* volSonido=opciones->FirstChildElement("sonido");
        volSonido->QueryIntAttribute("volumen", &sonido);

        tinyxml2::XMLElement* resPantalla=opciones->FirstChildElement("resolucion");
        resPantalla->QueryIntAttribute("tam", &resolucion);
    }
    if(partida!=NULL){
        tinyxml2::XMLElement* nivel=partida->FirstChildElement("nivel");
        nivel->QueryIntAttribute("max", &nivelMax);

        tinyxml2::XMLElement* sec1=partida->FirstChildElement("secreto1");
        sec1->QueryIntAttribute("max", &secreto1);

        tinyxml2::XMLElement* sec2=partida->FirstChildElement("secreto2");
        sec2->QueryIntAttribute("max", &secreto2);

        tinyxml2::XMLElement* sec3=partida->FirstChildElement("secreto3");
        sec3->QueryIntAttribute("max", &secreto3);

        tinyxml2::XMLElement* hab=partida->FirstChildElement("habilidades");
        hab->QueryIntAttribute("max", &habilidades);

        tinyxml2::XMLElement* fin=partida->FirstChildElement("terminado");
        fin->QueryIntAttribute("fin", &terminado);

        tinyxml2::XMLElement* muertes=partida->FirstChildElement("muertes");
        muertes->QueryIntAttribute("max", &num_muertes);
    }
}

Guardar::~Guardar(){
    if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }
}

void Guardar::setMusica(int vol){
    tinyxml2::XMLElement* opciones=doc.FirstChildElement("opciones");

    if(opciones!=NULL){
        tinyxml2::XMLElement* volMusica=opciones->FirstChildElement("musica");
        volMusica->SetAttribute("volumen",vol);
        doc.SaveFile("Motor/save.xml");
        musica = vol;
    }
}

void Guardar::setSonido(int vol){
    tinyxml2::XMLElement* opciones=doc.FirstChildElement("opciones");

    if(opciones!=NULL){
        tinyxml2::XMLElement* volSonido=opciones->FirstChildElement("sonido");
        volSonido->SetAttribute("volumen",vol);
        doc.SaveFile("Motor/save.xml");
        sonido = vol;
    }
}

void Guardar::setResolucion(int res){
    tinyxml2::XMLElement* opciones=doc.FirstChildElement("opciones");

    if(opciones!=NULL){
        tinyxml2::XMLElement* resPantalla=opciones->FirstChildElement("resolucion");
        resPantalla->SetAttribute("tam",res);
        doc.SaveFile("Motor/save.xml");
        resolucion = res;
    }
}

void Guardar::setResolucionAtr(int res){
    resolucion = res;
}

void Guardar::setNivel(int niv){
    tinyxml2::XMLElement* partida=doc.FirstChildElement("partida");

    if(partida!=NULL&&niv>nivelMax){
        tinyxml2::XMLElement* nivel=partida->FirstChildElement("nivel");
        nivel->SetAttribute("max",niv);
        doc.SaveFile("Motor/save.xml");
        nivelMax = niv;
    }
}

void Guardar::setTerminado(int fin){
    tinyxml2::XMLElement* partida=doc.FirstChildElement("partida");

    if(partida!=NULL){
        tinyxml2::XMLElement* term=partida->FirstChildElement("terminado");
        term->SetAttribute("fin",fin);
        doc.SaveFile("Motor/save.xml");
        terminado = fin;
    }
}

void Guardar::setMonedas(int mon){
    tinyxml2::XMLElement* partida=doc.FirstChildElement("partida");

    if(partida!=NULL){
        tinyxml2::XMLElement* monedas=NULL;
        if(mon==1){
            monedas=partida->FirstChildElement("secreto1");
            secreto1=1;
        }
        else if(mon==2){
            monedas=partida->FirstChildElement("secreto2");
            secreto2=1;
        }
        else{
            monedas=partida->FirstChildElement("secreto3");
            secreto3=1;
        }
        monedas->SetAttribute("max",1);
        doc.SaveFile("Motor/save.xml");
    }
}


void Guardar::setHabilidades(int hab){
    tinyxml2::XMLElement* partida=doc.FirstChildElement("partida");

    if(partida!=NULL&&hab>=habilidades){
        tinyxml2::XMLElement* habilid=partida->FirstChildElement("habilidades");
        habilid->SetAttribute("max",hab);
        doc.SaveFile("Motor/save.xml");
        habilidades = hab;
    }
}


void Guardar::setMuertes(int hab){
    tinyxml2::XMLElement* partida=doc.FirstChildElement("partida");

    if(partida!=NULL){
        tinyxml2::XMLElement* habilid=partida->FirstChildElement("muertes");
        habilid->SetAttribute("max",hab);
        doc.SaveFile("Motor/save.xml");
        num_muertes = hab;
    }
}

void Guardar::setHabilidadesAtrib(int hab){
    habilidades = hab;
}

void Guardar::reiniciarPartida(){
    tinyxml2::XMLElement* partida=doc.FirstChildElement("partida");
    if(partida!=NULL){
        tinyxml2::XMLElement* habilid=partida->FirstChildElement("habilidades");
        habilid->SetAttribute("max",0);
        tinyxml2::XMLElement* nivel=partida->FirstChildElement("nivel");
        nivel->SetAttribute("max",0);
        tinyxml2::XMLElement* fin=partida->FirstChildElement("terminado");
        fin->SetAttribute("fin",0);
        tinyxml2::XMLElement* muertes=partida->FirstChildElement("muertes");
        muertes->SetAttribute("max",0);
        tinyxml2::XMLElement* sec1=partida->FirstChildElement("secreto1");
        sec1->SetAttribute("max",0);
        tinyxml2::XMLElement* sec2=partida->FirstChildElement("secreto2");
        sec2->SetAttribute("max",0);
        tinyxml2::XMLElement* sec3=partida->FirstChildElement("secreto3");
        sec3->SetAttribute("max",0);
        tinyxml2::XMLElement* nombre=partida->FirstChildElement("nombre");
        nombre->SetText(" ");

        doc.SaveFile("Motor/save.xml");
        nivelMax = 0;
        habilidades = 0;
        terminado=0;
        num_muertes=0;
        secreto1=0;
        secreto2=0;
        secreto3=0;
    }
}

void Guardar::setNombre(std::string nom){
    tinyxml2::XMLElement* partida=doc.FirstChildElement("partida");

    if(partida!=NULL){
        tinyxml2::XMLElement* nivel=partida->FirstChildElement("nombre");
        nivel->SetText(nom.c_str());
        doc.SaveFile("Motor/save.xml");
    }
}

std::string Guardar::getNombre(){
    // Cargo tmx
    doc.LoadFile("Motor/save.xml");
    // apuntamos a partida
    tinyxml2::XMLElement* partida=doc.FirstChildElement("partida");

    if(partida!=NULL){
        tinyxml2::XMLElement* nombre=partida->FirstChildElement("nombre");
        if(nombre != NULL && nombre->GetText() != 0){

            return nombre->GetText();
        }
        else {
            return "";
        }
    }
    return "";
}