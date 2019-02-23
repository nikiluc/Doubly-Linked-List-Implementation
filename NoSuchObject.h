//
//  NoSuchObject.h
//  COSC052Spring2018L22Ex1
//

#ifndef _COSC052L22Ex1_NoSuchObject_h_
#define _COSC052L22Ex1_NoSuchObject_h_

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
using std::logic_error;
using std::out_of_range;



/****************************************************************************
 *                                                                          *
 *                   class NoSuchObject declaration                         *
 *                                                                          *
 ****************************************************************************/


class NoSuchObject : public logic_error
{
public:
    NoSuchObject(string msg = "no such object");
    
}; //END definition class no_such_object

NoSuchObject::NoSuchObject(string msg) : std::logic_error(msg) {
    // nothing else to do
}





#endif
