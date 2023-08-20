#ifndef OBJECT_H
#define OBJECT_H

template<typename T>
class Object
{
private:
    T item;
public:
    Object(T &renderObject);
    Object(Object &renderObject);
    ~Object();

    void objectDraw(){
        item.draw();
    }
};

template<typename T>
Object<T>::Object(T &renderObject)
{
    this->item = renderObject
}

template<typename T>
Object<T>::Object(Object &renderObject)
{
    this->item = renderObject.item;
}



#endif