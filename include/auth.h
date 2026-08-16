#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <vector>

// A single portal account. The password is kept as a rolling checksum so
// that no plain text password sits in the source file.
struct Credential {
    std::string username;
    std::string role;
    long passwordHash;
};

// In memory account store seeded with the demo accounts used by the portal.
class AuthStore {
public:
    AuthStore();

    const std::vector<Credential> &accounts() const;
    const Credential *find(const std::string &username) const;

    // True when the username exists and the password checksum matches.
    bool verify(const std::string &username, const std::string &password) const;

    // Prompts on the console until the credentials match or the attempt
    // budget runs out. The matched role is written to roleOut on success.
    bool authenticate(std::string &usernameOut, std::string &roleOut) const;

    static long hash(const std::string &password);
    static const int maxAttempts = 3;

private:
    std::vector<Credential> accounts_;
};

#endif
