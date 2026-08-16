# student-portal

A console based student portal written in C++17. This repository tracks the
overhaul of a legacy single file portal into a modular codebase.

## Scope

The portal is organised around five modules:

| Module     | Responsibility                            |
|------------|-------------------------------------------|
| calculator | marks, percentage and GPA computation     |
| auth       | login and session handling                |
| profile    | student enrollment details                |
| dashboard  | semester summary and attendance view      |
| settings   | grade scale and display preferences       |

The original implementation is preserved under `legacy/` for reference and is
not part of the build.
