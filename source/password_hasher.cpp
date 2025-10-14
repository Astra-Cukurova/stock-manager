#include "password_hasher.hpp"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace {
    const int ITERATIONS = 600000;
    const int SALT_LEN = 16;
    const int KEY_LEN = 32;

    std::string to_hex(const std::vector<unsigned char>& data) {
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        for (unsigned char c : data) {
            ss << std::setw(2) << static_cast<int>(c);
        }
        return ss.str();
    }

    std::vector<unsigned char> from_hex(const std::string& hex) {
        std::vector<unsigned char> bytes;
        for (unsigned int i = 0; i < hex.length(); i += 2) {
            std::string byteString = hex.substr(i, 2);
            unsigned char byte = static_cast<unsigned char>(strtol(byteString.c_str(), nullptr, 16));
            bytes.push_back(byte);
        }
        return bytes;
    }

    std::string hash_internal(const std::string& password, const std::vector<unsigned char>& salt) {
        std::vector<unsigned char> hash(KEY_LEN);
        int result = PKCS5_PBKDF2_HMAC(
            password.c_str(), password.length(),
            salt.data(), salt.size(),
            ITERATIONS,
            EVP_sha256(),
            KEY_LEN, hash.data()
        );
        if (result != 1) {
            throw std::runtime_error("PBKDF2 hashing failed.");
        }
        return to_hex(hash);
    }
}

HashedPassword create_password_hash(const std::string& password) {
    std::vector<unsigned char> salt_bytes(SALT_LEN);
    if (RAND_bytes(salt_bytes.data(), salt_bytes.size()) != 1) {
        throw std::runtime_error("Salt generation failed.");
    }

    std::string hashed_password = hash_internal(password, salt_bytes);

    return { hashed_password, to_hex(salt_bytes) };
}

bool verify_password(const std::string& password, HashedPassword hashed_password) {
    try {
        std::vector<unsigned char> salt_bytes = from_hex(hashed_password.salt);
        std::string new_hash = hash_internal(password, salt_bytes);
        return new_hash == hashed_password.hash;
    }
    catch (const std::exception& e) {
        std::cerr << "Verification error: " << e.what() << std::endl;
        return false;
    }
}