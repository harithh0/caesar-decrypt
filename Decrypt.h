#include <iostream>

#ifndef DECRYPT_H
#define DECRYPT_H



class Decrypt {

private:
    std::string encryptedText;
    bool showAccurate;;

public:
    Decrypt(const std::string& encryptedText, const bool& showAccurate);
    void decryptText();
    std::string work(const std::string& text, int key);

};


#endif 