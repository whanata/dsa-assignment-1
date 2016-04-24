#include <iostream>

#include "EuroEnglishConverter.h"

using namespace std;

int main(int argc, char *argv[])
{
   if (argc == 2) 
   {
      try
      {
         EuroEnglishConverter converter;
         converter.loadFile(argv[1]);
         converter.printWholeText();
         converter.convert();
         converter.printWholeText();
      }
      catch (exception &ex)
      {
         cout << "\nERROR - Exception thrown\n" << ex.what() << "\n";
      }
   }
   else
   {
      cout << "\nERROR - Invalid command line arguments\n";
   }

   return 0;
}