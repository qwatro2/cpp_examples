#include "caesar_cipher.h"

std::string Decipher(const std::string& cipher, size_t shift) {
    const int a_code = 65;
    const int alph_size = 26;
    std::string deciphered_message;
    for (auto c : cipher) {
        deciphered_message.push_back(
            static_cast<char>((static_cast<int>(c) - a_code + alph_size - shift) % alph_size + a_code));
    }
    return deciphered_message;
}
