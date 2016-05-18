#ifndef EURO_ENGLISH_CONVERTER_H_
#define EURO_ENGLISH_CONVERTER_H_

#include <list>

using namespace std;

class EuroEnglishConverter 
{
   private:
      list<char> wholeText;

   public:
      void loadFile(string file);
      bool checkWordBoundary(char character) const;
      unsigned short getHash(const list<char> &charList) const;
      void printWholeText() const;
      void convert();
      bool replaceLetter(char currentLetter, char replacement, list<char>::iterator iter);
      void conversionLoop(list<char>::iterator iter);
      bool replaceC(list<char>::iterator iter);
      bool replaceDualLetter(const string currentString, 
         const char replacement, 
         list<char>::iterator iter);
      bool replaceDoubleToSingle(list<char>::iterator iter);
      bool removeE(list<char>::iterator iter);
      bool endOfWord(const list<char>::iterator iter);
      bool replaceEd(list<char>::iterator iter);
      bool replaceEa(list<char>::iterator iter);

};

#endif