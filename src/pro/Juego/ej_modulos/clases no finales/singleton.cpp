class singleton{

singleton* singleton::pinstance = 0;
singleton* singleton::Instance(){
    if(pinstance == 0){
        pinstance = new singleton;

    }
    return pinstance;
}

singleton::singleton()
{

}

singleton *p1 = singleton::Instance();
singleton *p2 = p1->Instance();
singleton &ref = * singleton::Instance();

};