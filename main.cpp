#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>

int main(){

    std::ifstream inLeaters("LettersInput.txt");
    std::string allLetters((std::istreambuf_iterator<char>(inLeaters)),
        std::istreambuf_iterator<char>());
    inLeaters.close();

    allLetters.erase(allLetters.end() - 1,allLetters.end());
    std::string randomizeLetters = allLetters;
    std::random_shuffle(randomizeLetters.begin(),randomizeLetters.end());

    std::ifstream input("TextToBeEncoded.txt");
    std::string textToEncode((std::istreambuf_iterator<char>(input)),
        std::istreambuf_iterator<char>());
    input.close();

    std::string encodedText;

    encodedText.reserve(textToEncode.length());

    std::transform(textToEncode.begin(), textToEncode.end(),
                   std::back_inserter(encodedText),
                   [&allLetters, &randomizeLetters](char a){
                    std::size_t found = allLetters.find(a);
                    if (found!=std::string::npos)
                        a = randomizeLetters.at(found);

                   return a;
    });

    std::string textToCheckDecryption;
    textToCheckDecryption.reserve(encodedText.length());

    std::transform(encodedText.begin(), encodedText.end(),
                   std::back_inserter(textToCheckDecryption),
                   [&allLetters, &randomizeLetters](char a){
                    std::size_t found = randomizeLetters.find(a);
                    if (found!=std::string::npos)
                        a = allLetters.at(found);

                   return a;
    });

    std::cout << textToEncode << std::endl;
    std::cout << encodedText << std::endl;
    std::cout << textToCheckDecryption << std::endl;

}


