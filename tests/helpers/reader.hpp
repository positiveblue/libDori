#include <iostream>
#include <string>
#include <fstream>


std::ifstream openFile(std::string fname) {
  std::ifstream file(fname);
  if (file.is_open()) {
    return file;
  } else {
    std::cout << "SHIT" << std::endl;
  }
}