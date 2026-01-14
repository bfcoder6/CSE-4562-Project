#!/bin/bash

GITHUB_ACCOUNT=ubodin-cse-grader
PROJECT_URL=https://git.odin.cse.buffalo.edu/CSE-4562/2026-sp-project.git
PROJECT_UPSTREAM=project

if [ $# -lt 1 ]; then
    echo "Script for setting up your git repository."
    echo "usage: $0 <your-git-repo-address>"
    echo "You must first create a private repository on Github or Codeberg and give "
    echo "**READ** access to the Github user ${GITHUB_ACCOUNT}."
    echo "<your-git-repo-address> can be found when you click on the green "
    echo "\"code\" button. Make sure you use the SSH link in the form: "
    echo "git@github.com:<your-username>/<your-repository-name>.git"
    echo "or"
    echo "ssh://git@codeberg.org:<your-username>/<your-repository-name>.git"
    exit 1
fi

# The script for setting up the repository for the whole project.
GITADDR=$1

BASEDIR="$(cd "`dirname "$0"`" && pwd)"
cd "$BASEDIR"

if [ ! -d .git ]; then
  echo "Error: git repo is not yet initialized"
  exit 1
fi

if [ "$(git remote get-url origin)" != "$GITADDR" ]; then
  echo "Setting the repository up for $GITADDR ..."
  git remote set-url origin $GITADDR || exit 1
  git push -u origin main || exit 1
else
  echo "Repository already configured for $GITADDR"
fi

if git remote get-url $PROJECT_UPSTREAM > /dev/null 2>&1 ; then
  if [ "$(git remote get-url $PROJECT_UPSTREAM)" != "$PROJECT_URL" ]; then
    echo "Setting upstream url..."
    git remote set-url $PROJECT_UPSTREAM $PROJECT_URL || exit 1
  else
    echo "Repository already configured for upstream"
  fi
else
  echo "Configuring repository for upstream..."
  git remote add $PROJECT_UPSTREAM $PROJECT_URL || exit 1
fi

echo ""
echo "Repo setup is finished. Here are a few post-setup steps to follow:"
echo "1. Push the main branch to remote"
echo "      git push -u origin main"
echo "2. Run"
echo "      git status"
echo "   and make sure it outputs something like the following:"
echo "      On branch main"
echo "      Your branch is up to date with 'origin/main'."
echo "      nothing to commit, working tree clean"
echo ""
echo "If you've completed all the above steps, you've successfully set up your"
echo "repository."

