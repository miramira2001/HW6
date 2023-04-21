#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;
using namespace std;

struct MyStringHash {
    HASH_INDEX_T rValues[5]{ 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
			long long size = k.length();
      long long convStr[30];
      int j = 0;
        while (j < 30) {
          convStr[j] = 0;
          j++;
}
			for (int i = size - 1, steps = 0; i >= 0; i--, steps++) {
    convStr[steps] = letterDigitToNumber(k[i]);
}

unsigned int finalAmount = 0;
unsigned int w[5];
int stepsW = 4;

for (int i = 5; i < 30 + 5; i++) {
    switch (i % 6) {
        case 5:
             finalAmount = convStr[i-5] + 36 * (convStr[i-4] + 36 * (convStr[i-3] + 36 * (convStr[i-2] + 36 * (convStr[i-1] + 36 * convStr[i]))));
            w[stepsW--] = finalAmount;
            break;
        default:
            break;
    }
}
			unsigned long long endVal = 0;
			for(int i = 0; i < 5; i++){
				endVal = endVal + ( rValues[i] * w[i] );
			}
			return endVal;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const {
    switch (letter) {
        case '0' ... '9':
            return letter - 22;
        case 'A' ... 'Z':
            return letter - 65;
        case 'a' ... 'z':
            return letter - 97;
        default:
            return 0;  // some default value 
    }
}

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif