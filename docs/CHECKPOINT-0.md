## CSE 4/562 - Checkpoint 0

Welcome to CSE462/562. In this semester long course project, you will build a
mini database systems in the TDB (Taco-DB) framework. This readme contains
a brief description of how to set up the build environment, compile and test
the system. Please refer to the [course
website](https://odin.cse.buffalo.edu/teaching/cse-4562/) for
lab-specific instructions.

We have extensively tested the source code in the lab distribution but there
could inevitably be bugs as in any project. To report a BUG, please post a
**private** message in the Piazza to all TA and the
instructor. It will made public once validated. Please refer to the course
website for the policy of getting extra credit for successful reporting of
bugs.

#### Overview

In this checkpoint, you will:
- Form groups
- Ensure that you have a group GIT repository properly set up for code submission
- Ensure that you are able to compile and run code.

#### Links

* [This Readme](https://git.odin.cse.buffalo.edu/CSE-4562/2026-sp-project/src/branch/main/docs/CHECKPOINT-0.md)
* [Autolab Submission](https://autolab.cse.buffalo.edu/courses/cse462-s26/assessments/Checkpoint-0-Setup)

#### Initial Setup

**One** of your team should follow the initial setup instructions.  You may use *either* [Codeberg](https://codeberg.org) *or* [GitHub](https://github.com) to share code within your project group.  You will need to set up a new repository in either one and ensure that it is private except for your team, and that the accounts `ubodin-cse-grader` and `okennedy` have read access.

**Codeberg**
* In the `+` menu at the top-right, choose "New repository".  Give the repository a descriptive name, and **ensure that the "Make repository private"** checkbox is checked before creating the repository.
* Once the repository is created, take a note of your `SSH_URL` (needed later) is in the box to the upper left of the file list.  This is the string starting with `ssh://git@codeberg.org/...`.  Make sure it starts with `ssh` and not `https`
* Click "Settings" in the upper right, and then "Collaborators" from the menu at the left.
* Use "Add collaborator" to add each of your team members.
* Also use "Add collaborator" to add `ubodin-cse-grader` and `okennedy`.  These accounts will only need `Read` level access.

**Github**
* In the `+` menu at the top, choose "New repository".  Give the repository a descriptive name.  Under "Configuration", under "Choose visibility", make sure to choose "Private".
* Once the repository is created, take a note of your `SSH_URL` (needed later) is in the box to the upper left of the file list.  This is the string starting with `ssh://git@github.org/...`.  Make sure it starts with `ssh` and not `https`
* Go to the "Settings" tab and the "Collaborators" item (below "Access").
* Use "Add people" to find and add each of your team members.
* Use "Add people" to find and add `ubodin-cse-grader` and `okennedy`.  These accounts will only need `Read` level access.

Regardless of which hosting service you use, the following steps will prepare the repository you created for use with this project.  As before **one** of your team should follow these steps.

Start by cloning the project repository and configuring for use as a branch.

```bash
git clone https://git.odin.cse.buffalo.edu/CSE-4562/2026-sp-project.git CSE-4562-Project
cd CSE-4562-Project
```

The setup script will perform the necessary configuration.  You will need to replace `SSH_URL` below with the url you noted earlier.
```bash
./setup_repo.sh SSH_URL
```

Once the script completes, a copy of the repository should now be mirrored into the repository you set up.  Everyone else on your team should now be able to fetch the *Github* or *Codeberg* repository you created.  From now on, you will be able to just use this repository.

#### Dependencies and system requirements

git, cmake >= 3.13, pkg-config (0.29 recommended; <= 0.25 will make the build
extremely slow), c11 and c++17 compilers, e.g., gcc >= 7 or clang,
make, autoconf (for jemalloc), python3, and gtest

We recommend using recent Linux distributions on x86_64 platform. It's known to
work on Ubuntu 20.04 (and above) and Fedora 35 (and above) with gcc/clang.  It
might not work as intended or is known to not work on other systems even if it
compiles. The following is a non-exhaustive list:

- OS: Mac OS, Windows WSL1, Cygwin, MSYS, Win32
- Non-x86_64: Apple laptops with M1 processor,
  Microsoft Surface Pro X with SQ1 or SQ2

On a recent Debian-based linux distribution (including Debian, Ubuntu, Mint, PopOS, and WSL-Ubuntu), you can install the necessary dependencies with:
```bash
sudo apt install cmake libjemalloc-dev libabsl-dev pkg-config cmake-data build-essential
```

#### How to build

To create a debug build in build/ directory, run

```bash
cmake -B build
```

Once you've used cmake to configure your project, you can use make to compile your project:
```bash
make -C build taco
```
The binary will be deposited in `build/bin/taco`

As we get further into the project, you will want to also build in release mode.  The resulting binaries and tests will not include debug symbols (they'll be harder to debug), but will be more representative of the performance you will get when uploading to autolab.  To create a release build, run 

```bash
cmake -DCMAKE_BUILD_TYPE=Release -B build.release
```

Now, you will be able to compile tacodb with
```bash
make -C build.release taco
```

#### How to test your implementation

We use the [GoogleTest](http://google.github.io/googletest/) framework with its
community supported integration
[ctest](https://cmake.org/cmake/help/latest/manual/ctest.1.html). For advanced usages,
please review those documentations.

To run all tests, in your root directory, run:
```bash
make -C build test
```
Replace `build` with `build.release`, as before, to test a release build.

You can also run tests one at a time with
```bash
./build/tests/path-to-some-test
```

To list the project specific flags, run

```bash
./build/tests/path-to-some-test --help
```

#### Submission

Make sure that *all* of your team members are able to compile and run the test case provided with checkpoint 0.  Once
you have done this, you should make sure that the repository is properly committed and run:

```bash
make -C build taco
./build/bin/taco
```

This will generate a file `submission.json` in your directory.  Upload this file to autolab.  Once autolab confirms that
it is able to access your repository, you have completed checkpoint 0.
