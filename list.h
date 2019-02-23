#ifndef list_h
#define list_h


#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <exception>
#include "NoSuchObject.h"
#include "node.h"
#include "iterator.h"

using std::bad_alloc;
using namespace std;


template <typename T>
class List;

template <typename T>
ostream &operator<<( ostream &, const List<T> & );



/****************************************************************************
 ****************************************************************************
 *                                                                          *
 *                        class List declaration                            *
 *                                                                          *
 ****************************************************************************
 ****************************************************************************/

template <typename T>
class List
{
    
    friend ostream &operator<< <>( std::ostream &, const List<T> & );
    
    
    
public:
    
    
    List(); //i
    List( const List<T> & ) throw ( bad_alloc ); //i
    ~List(); //i
    void add( unsigned, const T & ) throw ( bad_alloc, out_of_range ); //i
    void addAll( const List<T> & ) throw ( bad_alloc ); //i
    void addAll( unsigned, const List<T> & ) throw ( bad_alloc, out_of_range ); //i
    void push_front( const T & ) throw ( bad_alloc ); //i
    void push_back( const T & ) throw ( bad_alloc ); //i
    void clear(); //i
    bool contains( const T & ) const; //i
    bool empty() const; //i
    int indexOf( const T & ) const; //i
    T &get( unsigned ) const throw (out_of_range); //i
    T &front() const throw ( NoSuchObject ); //i
    T &back() const throw ( NoSuchObject ); //i
    ListIterator<T> begin(); //i
    ListIterator<T> end(); //i
    ListIterator<T> ListIterator( unsigned ) throw ( out_of_range ); //i
    //T erase( const ListIterator<T> & ) throw (out_of_range); //i
    T pop_front() throw ( NoSuchObject ); //i
    T removeFirstOccurrence( const T & ) throw ( NoSuchObject ); //i
    T pop_back() throw ( NoSuchObject ); //i
    T removeLastOccurrence( const T & ) throw ( NoSuchObject ); //i
    T set( unsigned, const T & ) throw ( out_of_range ); //i
    unsigned size() const; //i
    T* toArray() const throw ( bad_alloc ); //i
    const List<T> &operator=( const List<T> & ) throw ( bad_alloc ); //i
    void printInternal( std::ostream & = cout ); //i
    ListIterator<T> erase( Node<T> * ); //i
    
private:
    Node<T> *frontPtr, *backPtr;
    unsigned sz;
    
    void add( Node<T> *, const T & ) throw ( bad_alloc ); //i
    void initialize(); //i
    Node<T> *getIthNode( unsigned ) const throw ( out_of_range ); //i
    
}; // List class

template <typename T> //works
List<T>::List() {
    //cout << "Entered default constructor of List class." << endl;
    
    frontPtr = new Node<T>;
    backPtr = new Node<T>;
    
    this->initialize();
    
    
} // END List::List()


template <typename T> //works
List<T>::List( const List<T> & t1) throw ( bad_alloc ) {
    
    //cout << "Entered implicit constructor of List class." << endl;
    
    frontPtr = new Node<T>;
    backPtr = new Node<T>;
    
    this->initialize();
    
    *this = t1;
    
    
} // END List::List(const List<T> & t1)


template <typename T> //works
List<T>::~List() {
    
    this->clear();
    
} // END List::~List()

template <typename T>
void List<T>::initialize() //works
{
    frontPtr->next = backPtr;
    frontPtr->previous = frontPtr;
    backPtr->previous = frontPtr;
    backPtr->next = backPtr;
    
    sz = 0;
    
} // END List::initialize()

template <typename T>
void List<T>::clear() //works
{
    cout << "entered function List::clear()....." << endl;
    unsigned long deleteCount = 0;
    
    
    if (frontPtr->next == backPtr) {
        
        cout << "List is empty" << endl;
        
    }
    
    //else if (frontPtr)
    
    else {
        //one or more objects on the list
        Node<T> *trailCurrent = frontPtr->next;
        Node<T> *current = frontPtr->next->next;
        
        //cout << "Size while deleting: " << sz << endl;
        
        while (trailCurrent != backPtr) {
            
            //cout << "Current: " << trailCurrent->info << endl;
            
            delete trailCurrent;
            trailCurrent = current;
            current = current->next;
            sz--;
            deleteCount++;
            
        }
        
        
    }
    
    cout << deleteCount << " objects deleted from the list" << endl;
    
    delete frontPtr;
    delete backPtr;
    
    
    cout << "Size after: " << sz << endl;
    
    
} // END List::clear()

template <typename T>
void List<T>::add(Node<T> *current, const T& val) throw (bad_alloc) { //works
    
    Node<T> *newInsert = new Node<T>(val, NULL, NULL);
    
    Node<T> *precede = current->previous;
    Node<T> *after = current;
    
    newInsert->previous = precede;
    newInsert->next = after;
    after->previous = newInsert;
    precede->next = newInsert;
    
    
}

template <typename T>
void List<T>::add(unsigned ndx, const T& val) throw (bad_alloc, out_of_range)  { //works
    
    if (ndx >= sz) {// update to code from Lecture 2
        throw out_of_range("List<T>::add(unsigned ndx, const T& val) Index"
                           " is not valid, elements range from 0 to size minus 1.");
    }
    
    Node<T> *current = getIthNode(ndx);
    
    
    this->add(current, val);
    
    sz++;
    
    
}


/*
 Adds a Node to the front of a list
 */
template <typename T>
void List<T>::push_front(const T& val) throw (bad_alloc)  { //works
    
    Node<T> *addMe = new Node<T>(val, NULL, NULL);
    
    
    
    addMe->next = frontPtr->next;
    addMe->previous = frontPtr;
    
    frontPtr->next->previous = addMe;
    frontPtr->next = addMe;
    
    
    sz++;
    
}

template <typename T>
void List<T>::push_back(const T& val) throw (bad_alloc)  { //works
    
    Node<T> *addMe = new Node<T>(val, NULL, NULL);
    //if the list is empty
    
    if ((*this).empty()) {
        
        addMe->next = frontPtr->next;
        addMe->previous = frontPtr;
        
        frontPtr->next->previous = addMe;
        frontPtr->next = addMe;
        
    }
    
    else {
        
        //cout << "okay" << endl;
        
        //set new Node previous pointer to backPtr previous
        addMe->previous = backPtr->previous;
        
        //set new Node next pointer to backPtr
        addMe->next = backPtr;
        
        backPtr->previous->next = addMe;
        backPtr->previous = addMe;
        
        // cout << "Cool: "<< backPtr->previous->info << endl;
        
        
    }
    
    sz++;
    
    
}

//Sets an ListIterator to the first node in the list
template <typename T>
ListIterator<T> List<T>::begin() { //works
    
    ListIterator<T> itr;
    
    itr.current = frontPtr;
    
    return itr;
    
}

template <typename T>
ListIterator<T> List<T>::end() { //works
    
    ListIterator<T> itr;
    
    itr.current = backPtr;
    
    return itr;
    
}


template <typename T>
ListIterator<T> List<T>::ListIterator( unsigned ndx ) throw ( out_of_range ) //works
{
    
    if (ndx > sz) {
        throw out_of_range("List::ListIterator(unsigned ndx) ndx value not valid");
    }
    
    ListIterator<T> itr;
    
    itr.movingForward = true;
    itr.movingBackward = false;
    
    Node<T> *temp = frontPtr;
    
    
    for (unsigned long i = 0; i < ndx; i++)
    {
        temp = temp->next;
    }
    
    
    itr.current = temp;
    
    return itr;
    
} // END List::ListIterator( unsigned )

template <typename T>
const List<T>& List<T>::operator=( const List<T> & L1) throw ( bad_alloc ) { //works
    
    
    //If there is nothing in the other deque
    if (L1.size() == 0) {
        
    }
    
    else {
        
        //Clears deque on left side of assignment operator
        //this->clear();
        
        //front pointer points to a new copy made from the other deque
        
        
        Node<T> *current = L1.frontPtr->next;
        
        while (current != L1.backPtr) {
            
            this->push_back(current->info);
            
            current = current->next;
            
        }
        
    }
    
    return *this;
    
}

template <typename T>
bool List<T>::empty() const { //works
    
    return sz == 0;
    
} // END empty()

template <typename T>
void List<T>::addAll(const List<T> & list) throw (bad_alloc)  { //works
    
    
    Node<T> *current = list.frontPtr->next;
    
    while (current != list.backPtr) {
        
        
        this->push_back(current->info);
        
        current = current->next;
        
    }
    
    
}

template <typename T>
void List<T>::addAll( unsigned ndx , const List<T> & list) throw ( bad_alloc, out_of_range ) { //works
    
    if (ndx > sz) {// update to code from Lecture 2
        throw out_of_range("List<T>::addAll(unsigned ndx) ndx value not valid");
    }
    
    if (ndx == sz) {
        sz++;
        
        Node<T> *otherlistcurrent = list.frontPtr->next;
        
        while (otherlistcurrent != list.backPtr) {
            
            this->add(ndx, otherlistcurrent->info);
            
            ndx++;
            
            otherlistcurrent = otherlistcurrent->next;
            
        }
        sz--;
    }
    
    else {
        
        Node<T> *otherlistcurrent = list.frontPtr->next;
        
        while (otherlistcurrent != list.backPtr) {
            
            this->add(ndx, otherlistcurrent->info);
            
            ndx++;
            
            otherlistcurrent = otherlistcurrent->next;
            
        }
        
    }
    
    
}

template <typename T>
bool List<T>::contains(const T& obj) const { //works
    
    bool yes = false;
    
    Node<T> *current = frontPtr->next;
    
    while (current != backPtr) {
        if (current->info == obj){
            
            yes = true;
        }
        
        current = current->next;
        
    }
    
    
    return yes;
    
}
//Returns the index of the first occurrence
//of the specified element in this list, or
//-1 if this list does not contain the element
template <typename T>
int List<T>::indexOf(const T & obj) const { //works
    
    
    int counter = 0;
    Node<T> *current = frontPtr->next;
    while (current != backPtr) {
        if (current->info == obj){
            
            return counter;
            
        }
        
        else {
            
            current = current->next;
            counter++;
            
        }
        
    }
    
    return -1;
    
    
}


template <typename T>
T& List<T>::get(unsigned int ndx) const  throw (out_of_range) { //works
    
    if (ndx >= sz) {
        throw out_of_range("List<T>::get(unsigned ndx) ndx value not valid");
    }
    
    Node<T> *current = getIthNode(ndx);
    
    return current->info;
    
}

template <typename T>
T & List<T>::front() const throw ( NoSuchObject ) { //works
    
    if (sz == 0) {
        throw NoSuchObject("List::getFirst() The list is empty.");
        
    }
    
    Node<T> *current = frontPtr;
    
    cout << "Front: " << current->next->info << endl;
    
    return current->next->info;
    
    }
    
    template <typename T>
    T & List<T>::back() const throw ( NoSuchObject ) { //works
        
        if (sz == 0) {
            throw NoSuchObject("List::getFirst() The list is empty.");
            
        }
        
        Node<T> *current = backPtr;
        
        //cout << "Back: " << current->previous->info << endl;
        
        return current->previous->info;
        
    }
    
    template <typename T>
    ListIterator<T>& List<T>::erase(Node<T>* current) { //works
        
        Node<T> *priorDelete = current->previous;
        Node<T> *postDelete = current->next;
        
        postDelete->previous = priorDelete;
        priorDelete->next = postDelete;
        
        sz--;
        
        cout << "hi" << endl;
        
        cout << "Object Removed: " << current->info << endl;
        
        
        //current = current->next;
        
        return current;
        
    }
    
    /*
     template <typename T>
     T List<T>::erase(const ListIterator<T> & I1) throw (out_of_range)  { //works
     
     if (ndx >= sz) {// update to code from Lecture 2
     throw out_of_range("List<T>::erase(unsigned ndx) ndx value not valid");
     }
     
     //unsigned long counter = 0;
     
     //Node<T> *current = getIthNode(ndx);
     
     Node<T> *current = I1.current;
     
     
     
     return this->erase(current);
     
     
     }
     
     */
    
    template <typename T>
    T List<T>::pop_front() throw ( NoSuchObject ) { //works
        
        if (sz == 0) {
            throw NoSuchObject("List<T>::pop_front() the list is empty");
        }
        
        Node<T> *current = frontPtr->next;
        
        return this->erase(current);
        
    }
    
    template <typename T>
    T List<T>::removeFirstOccurrence( const T & obj) throw ( NoSuchObject ) { //works
        
        
        if (sz == 0) {
            throw NoSuchObject("List<T>::removeFirstOccurence() the list is empty");
        }
        
        Node<T> *current = frontPtr->next;
        
        while (current != backPtr) {
            if (current->info == obj) {
                
                return this->erase(current);
                
            }
            
            current = current->next;
        }
        
        throw NoSuchObject("List<T>::removeFirstOccurence() object was not found");
        
    }
    
    template <typename T>
    T List<T>::pop_back() throw ( NoSuchObject ) { //works
        if (sz == 0) {
            throw NoSuchObject("List<T>::pop_front() the list is empty");
        }
        
        Node<T> *current = backPtr->previous;
        
        return this->erase(current);
        
    }
    
    //Finds the last occurence of a Node with a certain object
    //and removes it
    template <typename T>
    T List<T>::removeLastOccurrence( const T & obj) throw ( NoSuchObject ) { //works
        
        
        if (sz == 0) {
            throw NoSuchObject("List<T>::removeLastOccurence() the list is empty");
        }
        
        Node<T> *current = backPtr->previous;
        
        while (current != frontPtr) {
            if (current->info == obj) {
                
                return this->erase(current);
                
            }
            
            current = current->previous;
        }
        
        throw NoSuchObject("List<T>::removeLastOccurence() object was not found");
        
    }
    
    //Replaces a node at the Ith position on this list with new one
    //throws out_of_range if the ndx (index) value is greater
    //than the amount of elements on the list
    template <typename T>
    T List<T>::set( unsigned ndx, const T & obj) throw ( out_of_range ) { //works
        
        if (ndx >= sz) {
            throw out_of_range("List<T>::set(unsigned ndx, const T& obj) "
                               "ndx value is more or equal than the size of the list");
        }
        add(ndx, obj);
        
        
        Node<T> *current = getIthNode(ndx);
        
        return this->erase(current->next);
        
        
    }
    
    //Finds in the Node in the Ith position and returns
    //a reference to it
    template <typename T>
    Node<T>* List<T>::getIthNode( unsigned ndx) const throw ( out_of_range ) { //works
        
        if (ndx > sz) {
            throw out_of_range
            ("List<T>::set(unsigned ndx, const T& obj)"
             " ndx value is greater than size of list.");
        }
        
        unsigned int counter = 0;
        
        Node<T> *current = frontPtr->next;
        
        while (counter != ndx) {
            
            
            current = current->next;
            
            counter++;
            
        }
        
        return current;
        
    }
    
    //Returns the size of the list
    template <typename T>
    unsigned List<T>::size() const { //works
        
        return sz;
        
        
    }
    
    //Copies objects from Nodes in the list and puts them
    //into a dynamically allocated array
    template <typename T>
    T* List<T>::toArray() const throw (bad_alloc){ //works
        
        T* array = new T [size()];
        
        unsigned int counter = 0;
        
        Node<T> *current = frontPtr->next;
        
        while (current != backPtr) {
            
            array[counter] = current->info;
            
            current = current->next;
            counter++;
            
        }
        
        return array;
        
    }
    
    //(internal) Prints out information about each node in the list
    template <typename T>
    void List<T>::printInternal(ostream& cout){ //works
        
        Node<T>* current = frontPtr->next;
        int i = 1; //already at first non-sentinel node
        cout << "front: " << frontPtr->next->info << endl;
        while ( current != backPtr ) {
            cout << "Node " << i << endl;
            cout << "  address: " << current << endl;
            cout << "  object: " << current->info << endl;
            cout << "  next: " << current->next << endl;
            current = current->next;
            i++;
        }
    } // List<T>::printInternal()
    
    //Modifies ostream so to print out each element in this list
    template <typename T>
    ostream& operator<<(ostream& out, const List<T> & list) { //works
        
        
        Node<T> *current = list.frontPtr->next;
        
        out << "[";
        
        while (current != list.backPtr) {
            
            if (current->next == list.backPtr) {
                
                out << current->info;
            }
            
            else {
                
                out << current->info << ",";
                
            }
            
            current = current->next;
        }
        
        out << "]";
        
        return out;
        
    }
    
    
    
#endif

