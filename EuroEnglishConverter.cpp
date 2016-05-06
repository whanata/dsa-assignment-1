#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>

using namespace std;

#include "EuroEnglishConverter.h"

void EuroEnglishConverter::loadFile(string file)
{
   ifstream fin;
   char character = 0;
   bool gotSize = false;
   int counter = 0;
   int wordBoundaryCounter = 0;

   // open stream to file
   fin.open(file.c_str(), ios::in);
   if (!fin) 
   {
      throw runtime_error("Can't open " + file);
   }

   try
   {
      while (fin.get(character)) 
      {
         this->wholeText.pushBack(character);
      }
   }
   catch (exception &ex)
   {
      cout << "\nERROR - Exception thrown\n" << ex.what() << "\n";
      fin.close();
   }

   // we have finished reading the file, close the stream to it
   fin.close();
}

void EuroEnglishConverter::convert()
{
   listspc::Iterator<char> iter;
   listspc::Iterator<char> endWord;

   this->wholeText.pushFront(' ');
   this->wholeText.pushBack(' ');

   for (endWord = this->wholeText.begin(); endWord != this->wholeText.end(); endWord++)
   {
      this->conversionLoop(endWord);
   }

   this->wholeText.popFront();
   this->wholeText.popBack();
}

void EuroEnglishConverter::conversionLoop(listspc::Iterator<char> iter)
{
   bool changesMade;
   int counter = 0;
   do 
   {
      changesMade = false;
      if (this->replaceLetter('w', 'v', iter))
      {
         changesMade = true;
      }
      else if (this->replaceDoubleToSingle(iter))
      {
         changesMade = true;
      }
      else if (this->replaceDualLetter("ph", 'f', iter))
      {
         changesMade = true;
      }
      else if (this->replaceDualLetter("th", 'z', iter))
      {
         changesMade = true;
      }
      else if (this->replaceDualLetter("ou", 'u', iter))
      {
         changesMade = true;
      }
      else if (this->replaceEa(iter))
      {
         changesMade = true;
      }
      else if (this->replaceC(iter))
      {
         changesMade = true;
      }
      else if (this->removeE(iter))
      {
         changesMade = true;
      }
      else if (this->replaceEd(iter))
      {
         changesMade = true;
      }
      counter ++;
   } while (changesMade == true);
}

bool EuroEnglishConverter::removeE(listspc::Iterator<char> iter)
{
   listspc::Iterator<char> lastIter = iter;
   string eString = "eE";
   int wordCount = 0;

   if (this->endOfWord(iter))
   {
      lastIter--;
      while (!(this->checkWordBoundary(*lastIter)))
      {
         wordCount++;
         lastIter--;
      }
      if (wordCount > 3)
      {
         iter--;
         if (eString.find(*iter) != string::npos)
         {
            this->wholeText.erase(iter);
            return true;
         }
      }
   }
   return false;
}

bool EuroEnglishConverter::endOfWord(listspc::Iterator<char> iter)
{
   listspc::Iterator<char> lastIter = iter;
   if (this->checkWordBoundary(*lastIter))
   {
      lastIter--;
      if (lastIter != this->wholeText.end() && !(this->checkWordBoundary(*lastIter)))
      {
         return true;
      }
   }
   return false;
}

bool EuroEnglishConverter::replaceEd(listspc::Iterator<char> iter)
{
   listspc::Iterator<char> lastIter = iter;
   string eString = "eE";
   string dString = "dD";

   if (this->endOfWord(lastIter))
   {
      lastIter--;
      if (lastIter != this->wholeText.end() && dString.find(*lastIter) != string::npos)
      {
         lastIter--;
         if (lastIter != this->wholeText.end() && eString.find(*lastIter) != string::npos)
         {
            this->wholeText.erase(lastIter);
            return true;
         }
      }
   }
   return false;
}

bool EuroEnglishConverter::replaceDoubleToSingle(listspc::Iterator<char> iter)
{
   listspc::Iterator<char> nextIter = iter;

   nextIter++;
   if (nextIter != this->wholeText.end() && !(this->checkWordBoundary(*iter)))
   {
      if (tolower(*iter) == tolower(*nextIter))
      {
         this->wholeText.erase(nextIter);
         return true;
      }
   }
   return false;
}

bool EuroEnglishConverter::replaceEa(listspc::Iterator<char> iter)
{
   listspc::Iterator<char> nextIter = iter;

   string eString = "eE";
   string aString = "aA";

   if (eString.find(*iter) != string::npos)
   {
      nextIter++;
      if (nextIter != this->wholeText.end())
      {
         if (aString.find(*nextIter) != string::npos)
         {
            this->wholeText.erase(nextIter);
            return true;
         }
      }
   }
   return false;
}

bool EuroEnglishConverter::replaceDualLetter(const string currentString, 
   const char replacement, 
   listspc::Iterator<char> iter)
{
   listspc::Iterator<char> nextIter = iter;

   string possible1stLetter = string(1, currentString[0]);
   possible1stLetter += (char)toupper(currentString[0]);
   string possible2ndLetter = string(1, currentString[1]);
   possible2ndLetter += (char)toupper(currentString[1]);

   if (possible1stLetter.find(*iter) != string::npos)
   {
      nextIter++;
      if (nextIter != this->wholeText.end())
      {
         if (possible2ndLetter.find(*nextIter) != string::npos)
         {
            this->wholeText.erase(nextIter);
            this->replaceLetter(currentString[0], replacement, iter);
            return true;
         }
      }
   }
   return false;
}

bool EuroEnglishConverter::replaceC(listspc::Iterator<char> iter)
{
   listspc::Iterator<char> nextIter = iter;
   string possibleC = "cC";
   string array = "eiyEIY";
   if (possibleC.find(*iter) != string::npos)
   {
      nextIter++;
      if (nextIter != this->wholeText.end())
      {
         if (array.find(*nextIter) != string::npos)
         {
            this->replaceLetter('c', 's', iter);
            return true;
         }
         else
         { 
            this->replaceLetter('c', 'k', iter);
            return true;
         }
      }
      else
      {
         this->replaceLetter('c', 'k', iter);
         return true;
      }
   }
   return false;
}

// Always use lower case letters
bool EuroEnglishConverter::replaceLetter(char currentLetter, 
   char replacement, 
   listspc::Iterator<char> iter)
{
   if (*iter == currentLetter)
   {
      this->wholeText.replace(iter, replacement);
      return true;
   }
   else if (*iter == toupper(currentLetter))
   {
      this->wholeText.replace(iter, toupper(replacement));
      return true;
   }
   return false;
}

void EuroEnglishConverter::printWholeText() const
{
   listspc::ConstIterator<char> iter;
   listspc::ConstIterator<char> endIter = this->wholeText.end();

   for (iter = this->wholeText.begin(); iter != endIter; iter++)
   {
      cout << *iter;
   }

   cout << "\nHash: " << this->getHash(this->wholeText) << "\n";
}

bool EuroEnglishConverter::checkWordBoundary(char character) const
{
   return (!isalnum(character));
}

unsigned short EuroEnglishConverter::getHash(const listspc::List<char> &charList) const
{
   unsigned short shift, hash = 0;
   listspc::ConstIterator<char> itr;

   for (itr = charList.begin(); itr != charList.end(); itr++)
   {
      hash ^= *itr;
      shift = (hash & 15);
      hash = (hash << shift) | (hash >> (16 - shift));
   }
   return hash; 
}