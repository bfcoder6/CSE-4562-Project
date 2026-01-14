## CSE 4/562 - Checkpoint 0

In this checkpoint, you will:
- Form groups
- Ensure that you have a group GIT repository properly set up for code submission
- Ensure that you are able to compile and run code.

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
* Use "Add people" to find and add `ubodin-cse-grader` and `okenendy`.  These accounts will only need `Read` level access.

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

#### Instructions
