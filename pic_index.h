#include "Graph_proj.h"


struct tags{
        string filename;
        bool family, friends, aggieland, pets, vacation;
};

istream& operator>>(istream& is, tags& t);
ostream& operator<<(ostream& os, tags& t);


