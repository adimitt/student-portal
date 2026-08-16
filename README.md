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

## Directory layout

```
student-portal/
├── src/        implementation files, one translation unit per module
├── include/    public headers shared between modules
├── data/       plain text fixtures loaded at startup
├── docs/       notes carried over from the legacy portal
├── legacy/     original single file portal, excluded from the build
├── Makefile    build entry point
└── README.md
```

`bin/` is produced by the build and is deliberately not tracked; see
`.gitignore`.
