#ifndef EURO_ENGLISH_CONVERTER_H_
#define EURO_ENGLISH_CONVERTER_H_

#include "List.h"

using namespace std;

class EuroEnglishConverter 
{
   private:
      listspc::List<char> wholeText;

   public:
      void loadFile(string file);
      bool checkWordBoundary(char character) const;
      unsigned short getHash(const listspc::List<char> &charList) const;
      void printWholeText() const;
      void convert();
      bool replaceLetter(char currentLetter, char replacement, listspc::Iterator<char> iter);
      void conversionLoop(listspc::Iterator<char> iter);
      bool replaceC(listspc::Iterator<char> iter);
      bool replaceDualLetter(const string currentString, 
         const char replacement, 
         listspc::Iterator<char> iter);
      bool replaceDoubleToSingle(listspc::Iterator<char> iter);
      bool removeE(listspc::Iterator<char> iter);
      bool endOfWord(listspc::Iterator<char> iter);
      bool replaceEd(listspc::Iterator<char> iter);
      bool replaceEa(listspc::Iterator<char> iter);

};

#endif