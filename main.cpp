#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>

std::string downloadText(std::string fileName);
std::string encrypt(std::string &textToEncrypt, std::string &base, std::string &key);
std::string decrypt(std::string &textToDecrypt, std::string &base, std::string &key);

int main(){


    std::string allLetters = downloadText("LettersInput.txt");
    std::string randomizeLetters = allLetters;
    std::random_shuffle(randomizeLetters.begin(),randomizeLetters.end());

    std::string textToEncode = downloadText("TextToBeEncoded.txt");

    std::string encodedText;
    encodedText.reserve(textToEncode.length());

    encodedText = encrypt(textToEncode, allLetters, randomizeLetters);

    std::string textToCheckDecryption;
    textToCheckDecryption.reserve(encodedText.length());

    textToCheckDecryption = decrypt(encodedText, allLetters, randomizeLetters);

    std::cout << textToEncode << std::endl;
    std::cout << encodedText << std::endl;
    std::cout << textToCheckDecryption << std::endl;

    return 0;

}

std::string downloadText(std::string fileName)
{
    std::ifstream in(fileName);
    std::string tempString((std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());

    return tempString;
}

std::string encrypt(std::string &textToEncrypt, std::string &base, std::string &key)
{
    std::string tempText;
    tempText.reserve(textToEncrypt.length());

    std::transform(textToEncrypt.begin(), textToEncrypt.end(),
                   std::back_inserter(tempText),
                   [&base, &key](char a){
                    std::size_t found = base.find(a);
                    if (found!=std::string::npos)
                        a = key.at(found);

                   return a;
    });

    return tempText;
}
std::string decrypt(std::string &textToDecrypt, std::string &base, std::string &key)
{
    return encrypt(textToDecrypt, key, base);
}
