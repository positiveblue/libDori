#include <string>
#include <fstream>

#include "dori.hpp"
#include "cxxopts/cxxopts.hpp"

struct Options {
  int size;
  std::string fnameOne;
  std::string fnameTwo;
};


std::ifstream openFile(std::string fname) {
  std::ifstream file(fname);
  if (file.is_open()) {
    return file;
  } else {
    std::cout << "File " << '\'' << fname << "\' " << " can't be opened. " << fname << std::endl;
  }
}

Options parse_options(int argc, char* argv[]) {
  
  if (argc < 3) {
    std::cout << "You need to specify two input files" << std::endl; 
    exit(1);
  }

  Options res;

  cxxopts::Options options(argv[0]);
  
  options.add_options()
    ("s,size", "Aveilable memory", cxxopts::value<int>()
      ->default_value("9"))
    ("help", "Print help")
  ;



  options.parse(argc, argv);

  
  res.size = options["size"].as<int>();
  res.fnameOne = argv[argc-2];
  res.fnameTwo = argv[argc-1];
  
  return res;
}

int main(int argc, char* argv[]) {
  Options options = parse_options(argc, argv);

  dori::sketches::MinHash<std::string> MHFileOne {(std::uint64_t) options.size, 16};
  dori::sketches::MinHash<std::string> MHFileTwo {(std::uint64_t) options.size, 16};

  std::string word;

  // MinHash fnameOne
  std::ifstream file = openFile(options.fnameOne);
  while (file >> word) {
    MHFileOne.offer(word);
  }
  
  // MinHash fnameTwo
  file = openFile(options.fnameTwo);
  while (file >> word) {
    MHFileTwo.offer(word);
  }

  //std::cout << MHFileOne.compare(MHFileTwo) << std::endl;
}