# student-portal

A console based student portal written in C++17. This repository tracks the
overhaul of a legacy single file portal into a modular codebase.

## Scope

The portal is organised around six modules:

| Module     | Responsibility                            |
|------------|-------------------------------------------|
| calculator | marks, percentage and weighted averages   |
| grade      | GPA and letter award on the ten point scale |
| auth       | login, attempt limiting and sessions      |
| profile    | student enrollment details                |
| dashboard  | semester summary, attendance and charts   |
| settings   | grade scale and display preferences       |
| report     | printable end of semester report          |

The original implementation is preserved under `legacy/` for reference and is
not part of the build.

## Prerequisites

| Tool | Minimum version | Check with       |
|------|-----------------|------------------|
| g++  | 9 (C++17)       | `g++ --version`  |
| make | 3.81            | `make --version` |
| git  | 2.30            | `git --version`  |

Developed against Apple clang 21.0.0 and GNU Make 3.81 on macOS. Any Linux
distribution with a C++17 capable g++ builds it without changes.

## Setup

```
git clone https://github.com/adimitt/student-portal.git
cd student-portal
```

No external libraries are required, so there is no dependency install step.

## Build and execution

```
make            # optimised build, produces bin/portal
make debug      # unoptimised build with -g symbols
make run        # build and then launch the portal
make clean      # delete the bin/ directory
```

The executable is written to `bin/portal` and can also be launched directly:

```
./bin/portal
```

Sign in with roll number `2026201055` and password `portal123` to reach the
menu with the seeded data.

The grade scale unit has its own boundary test, which is not part of the
portal build:

```
g++ -std=c++17 -Iinclude tests/grade_scale_test.cpp src/grade_scale.cpp -o bin/grade_scale_test
./bin/grade_scale_test
```

## Directory layout

```
student-portal/
├── src/        implementation files, one translation unit per module
├── include/    public headers shared between modules
├── data/       plain text fixtures loaded at startup
├── docs/       notes carried over from the legacy portal
├── tests/      standalone checks, built by hand
├── legacy/     original single file portal, excluded from the build
├── Makefile    build entry point
└── README.md
```

`bin/` is produced by the build and is deliberately not tracked; see
`.gitignore`.

## Using the portal

On launch the portal asks for credentials, then prints the main menu:

```
=== Student Portal ===
1. Marks calculator
2. View and edit profile
3. Dashboard
4. Settings
5. Export semester report
0. Sign out
Select an option:
```

Enter the number of the option and press return. Option `1` prompts for
subject marks and prints the percentage together with the GPA on the ten
point scale. Option `3` renders the semester summary with an attendance
panel. Option `0` leaves the portal.

## Contributing

### Branch naming

| Prefix       | Used for                                 | Example                     |
|--------------|------------------------------------------|-----------------------------|
| `feature/`   | a new user facing module                 | `feature/dashboard`         |
| `chore/`     | restructuring with no behaviour change   | `chore/project-restructure` |
| `hotfix/`    | a correction to already merged behaviour | `hotfix/grade-boundaries`   |
| `experiment/`| exploratory work that may be dropped     | `experiment/report-export`  |

Branch off `main`, keep the branch focused on one module, and merge back with
`--no-ff` so the history keeps the shape of the work.

### Commit messages

Written as `type: imperative summary in lower case`, where type is one of
`feat`, `fix`, `docs`, `refactor`, `build`, `test`, `chore` or `merge`.
The summary states what changed and why it was needed; bare messages such as
"fix" or "update" are not accepted.

## Release notes

### v1.0

First tagged release, covering the full overhaul of the legacy portal.

- modular layout, headers under `include/` and one translation unit per module
- marks calculator with checked division, weighted averages and percentages
- grade awards on the ten point scale, including the A- and B+ half bands
- login with attempt limiting and a session carried through the menu
- profile records loaded from `data/profiles.txt`, editable with validation
- dashboard with semester totals, attendance panel, bar chart and CSV export
- settings persisted to `data/portal.conf`, including the strict grade scale
- printable semester report written to `data/report_<roll>.txt`

The strict scale and the half bands were developed on separate branches and
their grade tables were reconciled by hand when `hotfix/grade-boundaries` was
merged; a strict run now shifts the half bands too.
