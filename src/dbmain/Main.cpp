#include <iostream>
#include <cstdlib>


int main(int argc, char **args) {
  
  std::cout << "Welcome to TacoDB." << std::endl << std::endl;

  std::cout << "Retrieving git URL ..." << std::endl;
  if (std::system("git remote get-url origin > submission.txt") == 0) {
    std::cout << "  ... success!" << std::endl << std::endl;
    std::cout << "The file `submission.txt` has been created.  Now upload it to autolab to test whether your repository is set up properly and complete checkpoint 0." << std::endl;
  } else {
    std::cout << "  ... error!" << std::endl << std::endl;
    std::cout << "A problem occurred retrieving your git URL.  You should see debugging output above that will help you diagnose the problem." << std::endl;
  }

  return 0;  
}
