#include "Decrypt.h"
#include <vector>


#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <iterator>



// basically this function calculates the percentage of meaningful words in a sentence to give best accurate answer (kinda slow though)
double calculate_meaningful_percentage(const std::string& sentence, const std::string& file_path) {

    std::set<std::string> dictionary;
    
    std::ifstream file(file_path);
    std::string word;
    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        dictionary.insert(word);
    }
    
    std::string lower_sentence = sentence;
    std::transform(lower_sentence.begin(), lower_sentence.end(), lower_sentence.begin(), ::tolower);
    
    std::vector<std::string> words;
    std::istringstream iss(lower_sentence);
    std::string current_word;
    while (iss >> current_word) {
        current_word.erase(std::remove_if(current_word.begin(), current_word.end(), ::ispunct), current_word.end());
        words.push_back(current_word);
    }
    
    if (words.empty()) {
        return 0.0;
    }
    
    int meaningful_words = 0;
    for (const auto& w : words) {
        if (dictionary.find(w) != dictionary.end()) {
            ++meaningful_words;
        }
    }
    
    double percentage = (static_cast<double>(meaningful_words) / words.size()) * 100;
    return percentage;
}



Decrypt::Decrypt(const std::string& text, const bool& showAccurate) {
    this->encryptedText = text;
    if (this->encryptedText.empty()) {
        throw std::invalid_argument("Text cannot be empty");
    }
    this->showAccurate = showAccurate;
    
}


// this func checks if the a character is inside the letter array or not
bool isCharInArray(char c, const char* array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (array[i] == c) {
            return true;
        }
    }
    return false;
}




std::string Decrypt::work(const std::string& text, int key) {
    char lowerLetters[] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z'
    };

    char upperLetters[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'
};

    std::string decryptedText = "";
    std::vector<char> decryptedIndexes;


    for(int i =0; i  < text.length(); i++){
        if (isCharInArray(std::tolower(text[i]), lowerLetters, 26) == false)  {
            decryptedText += text[i];
        }else{

            if(std::isupper(text[i])){
                decryptedText += upperLetters[(text[i] - 'A' - key + 26) % 26];
            }else{
                decryptedText += lowerLetters[(text[i] - 'a' - key + 26) % 26];

            }
        }

    };

    return decryptedText;
}





void Decrypt::decryptText() {
    
    std::string decrypted_messages[26];
    double percentages[26];
    
    // goes through each key
    for(int i = 0; i < 26; i++){
        decrypted_messages[i] = work(this->encryptedText, i);
        if(this->showAccurate){
            percentages[i] = calculate_meaningful_percentage(decrypted_messages[i], "words.txt");
        }
        if(i == 0){
            std::cout  << "\033[32m" << "Original Message: " << "\033[0m" << decrypted_messages[i] << std::endl;
        }else{
            std::cout << "\033[31m" << "Key: " << "\033[0m" << i  <<  " | " <<  "\033[33m" << "Message: "  << "\033[0m" << decrypted_messages[i] << std::endl;
        }


    }

    // if user wants accurate result
    if(this->showAccurate){
        // gets the max percentage
        double max = *std::max_element(std::begin(percentages), std::end(percentages));
        int index;
        // since both arrays are same size and correspond to each sentence, we can just get the index of the max and then use that index to get the exact sentence
        for (int i = 0; i < 26; ++i) {
            if (percentages[i] == max) {
                index = i;
            }
        }
        std::cout << "\033[32m" << "Sentence is most likely (key:" << index << "): "  << "\033[0m" << decrypted_messages[index] << std::endl;

    }

}