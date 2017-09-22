///Code used here is mostly written by carykh

#include "../headers/names.h"
#include<stdlib.h>

const int MIN_NAME_SIZE=4;
const int MAX_NAME_SIZE=10;
std::string vowels="aeiouy";
std::string consonants="bcdfghjklmnpqrstvxzw";
double random(double l, double r)
{
    return l+(rand()%1000/1000.0)*(r-l);
}
char getRandomChar()
{
    if (rand()%2) return vowels[rand()%vowels.size()];
    else return consonants[rand()%consonants.size()];
}
bool isVowel(char ch)
{
    return ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u' || ch=='y';
}
std::string mutateName(std::string input)
{
    std::string output;
    int affix;
    if (rand()%10==0)
    {
        affix=rand()%13;
        if (affix==0) //english
        {
            output=input+"son";
        }
        else if (affix==1) //slavic
        {
            output=input+"ski";
        }
        else if (affix==2) //bulgarian
        {
            if (input[input.size()-1]=='o' || input[input.size()-1]=='e') output=input+"v";
            else if (rand()%2) output=input+"ov";
            else output=input+"ev";
        }
        else if (affix==3) //irish/scottish
        {
            if (rand()%2) output="mac";
            else output="mc";
            output+=input;
        }
        else if (affix==4) //hebrew
        {
            output="ben";
            output+=input;
        }
        else if (affix==5) //armaic
        {
            output="bar";
            output+=input;
        }
        else if (affix==6) //armaic
        {
            output=input+"zoon";
        }
        else if (affix==7) //portuguese
        {
            output=input+"es";
        }
        else if (affix==8) //norse
        {
            output=input+"sen";
        }
        else if (affix==9) //armenian
        {
            output=input+"i";
        }
        else if (affix==10) //azeri
        {
            output=input+"ogly";
        }
        else if (affix==11) //hungarian
        {
            if (rand()%2) output=input+"fi";
            else if (rand()%2) output=input+"fy";
            else output=input+"ffy";
        }
        else if (affix==12) //romanian
        {
            if (rand()%2) output=input+"escu";
            else output=input+"eanu";
        }
    }
    else
    {
        output=input;
        if (output.size()>=3)
        {
            if (random(0,1)<0.2)
            {
                int removeIndex=rand()%output.size();
                output=output.substr(0,removeIndex)+output.substr(removeIndex+1,output.size()-removeIndex-1);
            }
        }
        if (output.size()<=9)
        {
            if (random(0,1)<0.2)
            {
                int insertIndex=rand()%(output.size()+1);
                output=output.substr(0,insertIndex)+getRandomChar()+output.substr(insertIndex,output.size()-insertIndex);
            }
        }
        int changeIndex=rand()%output.size();
        output=output.substr(0,changeIndex)+getRandomChar()+output.substr(changeIndex+1,output.size()-changeIndex-1);
        output=sanitizeName(output);
    }
    return output;
}
std::string createNewName()
{
    std::string nameSoFar="";
    int chosensize=random(MIN_NAME_SIZE,MAX_NAME_SIZE);
    for(int i=0;i<chosensize;i++)
    {
        nameSoFar+=getRandomChar();
    }
    return sanitizeName(nameSoFar);
}
std::string sanitizeName(std::string input)
{
    std::string output="";
    int vowelsSoFar=0;
    int consonantsSoFar=0;
    for (int i=0; i < input.size(); i++)
    {
        char ch=input[i];
        if (isVowel(ch))
        {
            consonantsSoFar=0;
            vowelsSoFar++;
        }
        else
        {
            vowelsSoFar=0;
            consonantsSoFar++;
        }
        if(vowelsSoFar<=2 && consonantsSoFar<=2)
        {
            output=output+ch;
        }
        else
        {
            double chanceOfAddingChar=0.5;
            if (input.size()<=MIN_NAME_SIZE)
            {
                chanceOfAddingChar=1.0;
            }
            else if (input.size()>=MAX_NAME_SIZE)
            {
                chanceOfAddingChar=0.0;
            }
            if (random(0,1)<chanceOfAddingChar)
            {
                char extraChar=' ';
                while (extraChar==' ' || (isVowel(ch)==isVowel(extraChar)))
                {
                    extraChar=getRandomChar();
                }
                output=output+extraChar+ch;
                if (isVowel(ch))
                {
                    consonantsSoFar=0;
                    vowelsSoFar=1;
                }
                else
                {
                    consonantsSoFar=1;
                    vowelsSoFar=0;
                }
            }
        }
    }
    return output;
}
