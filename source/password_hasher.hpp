#ifndef PASSWORD_HASHER_HPP
#define PASSWORD_HASHER_HPP

#include <string>
#include <vector>

struct HashedResult {
    std::string hash;
    std::string salt;
};

HashedResult create_password_hash(const std::string& password);

bool verify_password(const std::string& password, const std::string& stored_hash, const std::string& stored_salt);

#endif // PASSWORD_HASHER_HPP