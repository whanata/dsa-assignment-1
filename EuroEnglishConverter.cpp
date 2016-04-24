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
   char lastChar = '0';
   // int charCount = 0;

   for (endWord = this->goToFirstLetter(iter); endWord != this->wholeText.end(); endWord++)
   {
      cout << *endWord << "\n";
      if (!(this->checkWordBoundary(*endWord)))
      {
         // charCount++;
         endWord++;
         if (this->checkWordBoundary(lastChar) || endWord == this->wholeText.end())
         {
            // cout << charCount << "\n";
            endWord--;
            endWord--;
            this->conversionLoop(iter, endWord);
            endWord++;
            // charCount = 0;
            iter = endWord;
         }
      }
      lastChar = *endWord;
   }
}

void EuroEnglishConverter::conversionLoop(listspc::Iterator<char> &iter, listspc::Iterator<char> &endWord)
{
   int charCount = 0;
   while (iter != endWord)
   {
      this->replaceWToV(iter);
      charCount++;
      iter++;
   }
   // cout << charCount << "\n";
   charCount = 0;
}

void EuroEnglishConverter::replaceWToV(listspc::Iterator<char> iter)
{
   if (*iter == 'w')
   {
      this->wholeText.replace(iter, 'v');
   }
}

listspc::Iterator<char> EuroEnglishConverter::goToFirstLetter(listspc::Iterator<char> &iter)
{
   listspc::Iterator<char> endWord;

   for (endWord = this->wholeText.begin(); endWord != this->wholeText.end(); endWord++)
   {
      if (!(this->checkWordBoundary(*endWord)))
      {
         iter = endWord;
         break;
      }
   }

   return endWord;
}

listspc::Iterator<char> EuroEnglishConverter::resetToStartWord(listspc::Iterator<char> iter) const
{
   while (!(this->checkWordBoundary(*iter)))
   {
      iter--;
   }
   iter++;

   return iter;
}

void EuroEnglishConverter::printWholeText() const
{
   listspc::ConstIterator<char> iter;
   listspc::ConstIterator<char> endIter = this->wholeText.end();

   for (iter = this->wholeText.begin(); iter != endIter; iter++)
   {
      cout << *iter;
   }

   cout << "\n\nHash: " << this->getHash(this->wholeText) << "\n";
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