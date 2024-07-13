//
//  Seq_item.hpp
//  seq
//
//  Created by Ricardo on 16/8/7.
//  Copyright © 2016年 Ricardo. All rights reserved.
//

#ifndef Seq_item_hpp
#define Seq_item_hpp

#include <stdio.h>

template<class T> class Seq;

template<class T>
class Seq_item{
    friend class Seq<T>;
    int use;
    const T data;
    Seq_item* next;
    
    Seq_item(const T& t, Seq_item* s);
    Seq_item(const T& t): use(1), data(t), next(0) { }
};

template <class T>
Seq_item<T>::Seq_item(const T& t,Seq_item<T>* s):
        use(1), data(t), next(s)
{
    if(s){
        s->use++;
    }
}

#endif /* Seq_item_hpp */
