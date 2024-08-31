#include <iostream>
#include "Decrypt.h"



int main()
{

    std::cout << R"(


  ____                                 _                            _   
 / ___|__ _  ___  ___  __ _ _ __    __| | ___  ___ _ __ _   _ _ __ | |_ 
| |   / _` |/ _ \/ __|/ _` | '__|  / _` |/ _ \/ __| '__| | | | '_ \| __|
| |__| (_| |  __/\__ \ (_| | |    | (_| |  __/ (__| |  | |_| | |_) | |_ 
 \____\__,_|\___||___/\__,_|_|     \__,_|\___|\___|_|   \__, | .__/ \__|
                                                        |___/|_|        
                                                                    by harith
                                                                          )" << std::endl;

    std::string cipherText;
    char showAccurateAnswer = false;

    std::cout << "Enter cipher text: ";
    std::getline(std::cin, cipherText);

    if(cipherText.length() > 10){
        std::cout << "Show most accurate result at the end?(takes time) (y/n): ";
        std::cin >> showAccurateAnswer;
        if(std::tolower(showAccurateAnswer) == 'y'){
            showAccurateAnswer = true;
        }else{
            showAccurateAnswer = false;
        }
    }


    Decrypt dec = Decrypt(cipherText, showAccurateAnswer);
    dec.decryptText();


    return 0;
}
