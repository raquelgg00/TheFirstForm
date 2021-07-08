class singleton{

public:
    static singleton* Instance();
protected:
    singleton();
    singleton(const singleton & );
    singleton &operator= (const singleton & );
private:
    static singleton* pinstance;

};