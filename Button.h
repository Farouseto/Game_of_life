#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

void LoadButton ();          //Opens the file from the specified link and loads the button parameters into a 2D vector
std::string ButtonStates (int x, int y, int LayerNow);
void GetPB(std::string name, int L, int &x, int &y, int &h, int &w, int &ImX, int &ImY);
int *GetLink(int Layer, int &size); //Return the parameters of all buttons of a specific layer and the size of the array
//bool ButtonState (std::string name);
void ButtonClose();

/*
void ButtonEditor ();
GetPB(std::string name, int Layer,int x, int y, int h, int w, int ImX, int ImY);
GetLayer(std::string name);
GetX(std::string name);
GetY(std::string name);
GetH(std::string name);
GetW(std::string name);
GetImX(std::string name);
GetImY(std::string name);
int ButtonState (std:string name); //Узнает активна кнопка или нет
std::string ButtonStates(int x, int y, int layer) //Определяет какая кнопка сейчас нажата
*/

#endif // BUTTON_H_INCLUDED
