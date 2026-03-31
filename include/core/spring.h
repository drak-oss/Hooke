#ifndef SPRING_H
#define SPRING_H

struct Spring {
    int id ;

    int NodeA ;
    int NodeB ;

    float restLength ;
    float stifness ;
    float damping ;

    Spring(int id , int NodeA , int NodeB , float restLength , float stifness , float damping)
        : id(id) , NodeA(NodeA) , NodeB(NodeB) , restLength(restLength) , stifness(stifness) , damping(damping) {} ;
} ;

#endif