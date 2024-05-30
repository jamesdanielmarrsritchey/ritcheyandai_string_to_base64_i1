#include <iostream>
#include <string>
#include <vector>

/*
To compile and install the program on Debian, you can follow these steps:

1. Install the g++ compiler if it's not already installed. You can do this by running the following command in your terminal:
   sudo apt-get install g++

2. Navigate to the directory containing the source code file (let's call it base64.cpp) using the cd command.

3. Compile the source code file using the g++ compiler. You can do this by running the following command in your terminal:
   g++ -o base64 base64.cpp

4. Now, you can run the program using the following command:
   ./base64 --string "Your string here"

Please replace "Your string here" with the string you want to convert to Base64.
*/

const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

std::string base64_encode(const std::string &input) {
    std::string ret;
    int i = 0;
    int val = 0;
    int valb = -6;

    for (auto c : input) {
        val = (val<<8) + c;
        valb += 8;
        while (valb >= 0) {
            ret.push_back(base64_chars[(val>>valb)&0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) ret.push_back(base64_chars[((val<<8)>>(valb+8))&0x3F]);
    while (ret.size() % 4) ret.push_back('=');
    return ret;
}

int main(int argc, char* argv[]) {
    std::string input;
    for(int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if(arg == "--string" && i + 1 < argc) {
            input = argv[++i];
        }
    }
    std::cout << base64_encode(input);

    return 0;
}