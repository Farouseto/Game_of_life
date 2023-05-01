#include "Button.h"

std::vector< std::vector < std::string > > LBVector;           //Saves image layout and button names
std::vector< std::vector < int > > PVector;   //Stores button parameters layer by layer
int Layer = 0;

void LoadLayer (std::ifstream &file, std::string &Symbols)
{
    std::vector <std::string> temp;

    while(Symbols == "L")
    {
        file >> Symbols;
        while (Symbols != "L" && !file.eof() && Symbols != "B")
        {
            temp.push_back(Symbols);
            file >> Symbols;
        }
        LBVector.push_back(temp);
        temp.clear();
    }
}

void LoadP (std::ifstream &file, std::string &Symbols, int &Layer)
{
    int Number = 0, LayerNow = 0;
    std::vector <int> temp;

    while (Symbols == "B")
    {
        file >> LayerNow;

        if (LayerNow != Layer)
        {
            PVector.push_back(temp);
            temp.clear();
            Layer++;
        }

        for (int i = 0; i < 6; i++)
        {
            file >> Number;
            temp.push_back(Number);
        }
        file >> Symbols;
        if (file.eof()) break; //If the file reading sequence is changed
    }
    PVector.push_back(temp);
    temp.clear();
}

void LoadButton()
{
   std::cout << "Enter a link to the file\n";

   std::string Symbols = "";
   char link[128];
   std::cin >> link;
   std::ifstream file(link);

   if (file.is_open())
   {
       std::cout << "File open\n";

       file >> Symbols;
       while (!file.eof())
        {
            if (Symbols == "L") LoadLayer(file, Symbols);
            if (Symbols == "B") LoadP(file, Symbols, Layer);
            file >> Symbols;
        }
        std::cout << "File read\n";
    }
    else
    {
        std::cout << "File opening error\n";
    }
    file.close();
}

std::string ButtonStates (int x, int y, int LayerNow)
{
/*
0: x,
1: y,
2: h,
3: w,
4: ImX,
5: ImY
*/
    for (unsigned int i = 1, ii = 0; i <= PVector[LayerNow].size()/6; i++)
    {
        if ((PVector[LayerNow][ii] <= x && x <= (PVector[LayerNow][ii] + PVector[LayerNow][2+ii]))
            && (PVector[LayerNow][ii+1] <= y && y <= (PVector[LayerNow][ii+1] + PVector[LayerNow][3+ii])))
        {
            return LBVector[LayerNow][i];
        }
        ii = ii + 6; //For correct reading of parameters in a vector
    }
    return "Nothing";
}

void GetPB(std::string name, int L, int &x, int &y, int &h, int &w, int &ImX, int &ImY)
{
    //Button name search
    for (unsigned int i = 1; (LBVector[L].size() - 1) >= i; i++)
    {
        //Parameter passing
        if (name == LBVector[L][i])
        {
            x = PVector[L][0 + (6*(i - 1))];
            y = PVector[L][1 + (6*(i - 1))];
            h = PVector[L][2 + (6*(i - 1))];
            w = PVector[L][3 + (6*(i - 1))];
            ImX = PVector[L][4 + (6*(i - 1))];
            ImY = PVector[L][5 + (6*(i - 1))];
        }
    }
}

int *GetLink(int Layer, int &size)
{
    size = PVector[Layer].size() / 6 - 1;
    return &PVector[Layer][0];
}

void ButtonClose()
{
    LBVector.clear();
    PVector.clear();
}
