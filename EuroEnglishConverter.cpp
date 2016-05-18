#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include <list>

using namespace std;

#include "EuroEnglishConverter.h"

void EuroEnglishConverter::loadFile(string file)
{
   ifstream fin;
   char character = 0;

   fin.open(file.c_str(), ios::in);
   if (!fin) 
   {
      throw runtime_error("Can't open " + file);
   }

   try
   {
      while (fin.get(character)) 
      {
         this->wholeText.push_back(character);
      }
   }
   catch (exception &ex)
   {
      cout << "\nERROR - Exception thrown\n" << ex.what() << "\n";
      fin.close();
   }

   fin.close();
}

void EuroEnglishConverter::convert()
{
   list<char>::iterator iter;
   list<char>::iterator endWord;

   this->wholeText.push_front(' ');
   this->wholeText.push_back(' ');

   for (endWord = this->wholeText.begin(); endWord != this->wholeText.end(); endWord++)
   {
      this->conversionLoop(endWord);
   }

   this->wholeText.pop_front();
   this->wholeText.pop_back();
}

void EuroEnglishConverter::conversionLoop(list<char>::iterator iter)
{
   bool changesMade;
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
   } while (changesMade == true);
}

bool EuroEnglishConverter::removeE(list<char>::iterator iter)
{
   // Remove e if the word is longer than 3 letters
   list<char>::iterator lastIter = iter;
   string eString = "eE";
   int wordCount = 0;

   iter--;
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
         if (eString.find(*iter) != string::npos)
         {
            this->wholeText.erase(iter);
            return true;
         }
      }
   }
   return false;
}

bool EuroEnglishConverter::endOfWord(const list<char>::iterator iter)
{
   list<char>::iterator nextIter = iter;
   if (!(this->checkWordBoundary(*iter)))
   {
      nextIter++;
      if (nextIter != this->wholeText.end() && this->checkWordBoundary(*nextIter))
      {
         return true;
      }
   }
   return false;
}

bool EuroEnglishConverter::replaceEd(list<char>::iterator iter)
{
   // Replace ed in the end of the word to d
   list<char>::iterator nextIter = iter;
   string eString = "eE";
   string dString = "dD";

   if (eString.find(*iter) != string::npos)
   {
      nextIter++;
      if (nextIter != this->wholeText.end() && this->endOfWord(nextIter))
      {
         if (dString.find(*nextIter) != string::npos)
         {
            this->wholeText.erase(nextIter);
            this->replaceLetter('e', 'd', iter);
            return true;
         }
      }
   }
   return false;
}

bool EuroEnglishConverter::replaceDoubleToSingle(list<char>::iterator iter)
{
   // Replace double letters with a single letter
   list<char>::iterator nextIter = iter;

   nextIter++;
   if (nextIter != this->wholeText.end() && !(this->checkWordBoundary(*iter)))
   {
      if (isalpha(*iter) && tolower(*iter) == tolower(*nextIter))
      {
         this->wholeText.erase(nextIter);
         return true;
      }
   }
   return false;
}

bool EuroEnglishConverter::replaceEa(list<char>::iterator iter)
{
   // Replace ea to e
   list<char>::iterator nextIter = iter;

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
   list<char>::iterator iter)
{
   // Replace 2 letter in the first parameter with 2 letters in the second parameter
   list<char>::iterator nextIter = iter;

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

bool EuroEnglishConverter::replaceC(list<char>::iterator iter)
{
   // Replace c with s if there is e, i or y after it
   // Else replace c with k
   list<char>::iterator nextIter = iter;
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
   list<char>::iterator iter)
{
   if (*iter == currentLetter)
   {
      *iter = replacement;
      return true;
   }
   else if (*iter == toupper(currentLetter))
   {
      *iter = toupper(replacement);
      return true;
   }
   return false;
}

void EuroEnglishConverter::printWholeText() const
{
   list<char>::const_iterator iter;
   list<char>::const_iterator endIter = this->wholeText.end();

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

unsigned short EuroEnglishConverter::getHash(const list<char> &charList) const
{
   unsigned short shift, hash = 0;
   list<char>::const_iterator itr;

   for (itr = charList.begin(); itr != charList.end(); itr++)
   {
      hash ^= *itr;
      shift = (hash & 15);
      hash = (hash << shift) | (hash >> (16 - shift));
   }
   return hash; 
}