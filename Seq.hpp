//
//  Seq.hpp
//  seq
//
//  Created by Ricardo on 16/8/7.
//  Copyright © 2016年 Ricardo. All rights reserved.
//

#ifndef Seq_hpp
#define Seq_hpp

#include <stdio.h>
#include "Seq_item.hpp"
template<class T>
class Seq{
public:
    Seq(): item(0) { }
    Seq(const T& t, const Seq& x):
        item(new Seq_item<T>(t,x.item)){ }
    Seq(const Seq&);
    ~Seq();
    Seq& operator=(const Seq&);
    T hd() const;
    Seq tl() const;
    operator bool() const;
    Seq& operator++();
    Seq operator++(int);
    T operator*() { return hd(); }
private:
    Seq_item<T>* item;
    Seq(Seq_item<T>* s);
    void destroy(Seq_item<T>* item);
};

template<class T>
Seq<T>::operator bool() const{
    return item != 0;
}

template<class T>
Seq<T>::Seq(const Seq<T>& s):
    item(s.item)
{
    if (item) {
        item->use++;
    }
}

template<class T>
T Seq<T>::hd() const
{
    if (item) {
        return item->data;
    } else {
        throw "hd of an emoty Seq";
    }
}

template<class T>
Seq<T>::Seq(Seq_item<T>* s): item(s)
{
    if(s)
        s->use++;
}

template<class T>
Seq<T> Seq<T>::tl() const
{
    if (item) {
        return Seq<T>(item->next);
    } else{
        throw "tl of an empty Seq";
    }
}

template<class T>
void Seq<T>::destroy(Seq_item<T> *item){
    while(item && --item->use == 0){
        Seq_item<T>* next = item->next;
        delete item;
        item = next;
    }
}

template<class T>
Seq<T>& Seq<T>::operator=(const Seq<T> & s){
    if(s.item)
        s.item->use++;
    destroy(item);
    item = s.item;
    return *this;
}

template<class T>
Seq<T>::~Seq<T>(){
    destroy(item);
}

template<class T>
Seq<T>& Seq<T>::operator++(){
    if(item){
        Seq_item<T>* p = item->next;
        if (p) {
            p->use++;
        }
        if (--item->use == 0) {
            delete item;
        }
        item = p;
    }
    return *this;
}

template<class T>
Seq<T> Seq<T>::operator++(int){
    Seq<T> ret = *this;
    if(item){
        --item->use;
        item = item->next;
        if (item) {
            item->use++;
        }
    }
    return ret;
}


#endif /* Seq_hpp */
