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
      listspc::Iterator<char> resetToStartWord(listspc::Iterator<char> iter) const;
      listspc::Iterator<char> goToFirstLetter(listspc::Iterator<char> &iter);
      void replaceWToV(listspc::Iterator<char> iter);
      void conversionLoop(listspc::Iterator<char> &iter, listspc::Iterator<char> &endWord);

      EuroEnglishConverter()
      {

      }
};

#endif