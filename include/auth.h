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

    static long hash(const std::string &password);

private:
    std::vector<Credential> accounts_;
};

#endif
