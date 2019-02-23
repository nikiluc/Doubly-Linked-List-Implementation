

#ifndef node_h
#define node_h


#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <exception>



using std::string;
using std::endl;
using std::cout;



/****************************************************************************
 *                                                                          *
 *                      class Node declaration                            *
 *                                                                          *
 ****************************************************************************/

template <typename T>
class Node
{
public:
    T info;
    Node<T> *next;
    Node<T> *previous;
    
    Node(T = T(), Node<T> *next = NULL, Node<T> *previous = NULL);
    
}; //END declaration class Node

//Explicit constructor for Node
template <typename T>
Node<T>::Node(T infoValue, Node<T> *nextPtr, Node<T> *prevPtr)
{
    info = infoValue;
    next = nextPtr;
    previous = prevPtr;
}





#endif /* dlnode_h */
