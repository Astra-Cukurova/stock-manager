#ifndef PASSWORD_HASHER_HPP
#define PASSWORD_HASHER_HPP

#include <string>
#include <vector>

struct HashedPassword {
    std::string hash;
    std::string salt;
};

HashedPassword create_password_hash(const std::string& password);

bool verify_password(const std::string& password, HashedPassword hashed_password);

#endif // PASSWORD_HASHER_HPP