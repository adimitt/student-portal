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

// Who is currently signed in. An inactive session means the portal should
// fall back to the login prompt rather than showing the menu.
struct Session {
    std::string username;
    std::string role;
    bool active = false;

    bool isFaculty() const { return role == "faculty" || role == "admin"; }
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
    // budget runs out. Returns an inactive Session when it runs out.
    Session authenticate() const;

    static long hash(const std::string &password);
    static const int maxAttempts = 3;

private:
    std::vector<Credential> accounts_;
};

#endif
