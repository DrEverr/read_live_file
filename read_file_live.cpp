#include <iostream>
#include <string>
#include <fstream>

int main() {
  std::string FILE{ "PATH_TO_YOUR_FILE" };
  std::ifstream ifs{ FILE };
  
  if (ifs.is_open()) {
    std::string line{ "" };
    
    while (true) {
      while (std::getline(ifs, line)) {
        // CODE TO PERFORM OPERATIONS WITH DATA FROM FILE, READ LINE BY LINE
        std::cout << line << std::endl;
      }
      
      if (!ifs.eof()) break; //Ensure this is the end of the file
      ifs.clear(); //Clear all flags
      
      /* Makes some sleep function here to not use too much CPU power
      * e.g. std::this_thread::sleep_for(std::chrono::seconds(2));
      * there for you need to include <chrono> and <thread>
      */
    }
  }
  return 0;
}
