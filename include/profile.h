#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <vector>

// Enrollment record shown on the profile screen.
struct StudentProfile {
    std::string rollNumber;
    std::string name;
    std::string programme;
    std::string email;
    int semester = 1;
};

// Collection of profiles known to the portal.
class ProfileBook {
public:
    ProfileBook();

    const std::vector<StudentProfile> &all() const;
    const StudentProfile *findByRoll(const std::string &rollNumber) const;
    size_t size() const;

private:
    std::vector<StudentProfile> profiles_;
};

#endif
