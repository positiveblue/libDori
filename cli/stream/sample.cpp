#include <string>
#include <fstream>

#include "dori.hpp"
#include "cxxopts/cxxopts.hpp"

struct Options {
  int size;
  std::string algorithm;
  bool print;
  std::string input;
};


Options parse_options(int argc, char* argv[]) {
  
  Options res;

  cxxopts::Options options(argv[0]);
  
  options.add_options()
    ("a,algorithm", "recordinality", cxxopts::value<std::string>()
      ->default_value("recordinality"))
    ("s,size", "Aveilable memory", cxxopts::value<int>()
      ->default_value("64"))
    ("p,print", "print sample")
    ("i,input", "Input file", cxxopts::value<std::string>())
    ("help", "Print help")
  ;

  options.parse(argc, argv);

  res.size = options["size"].as<int>();
  res.algorithm = options["algorithm"].as<std::string>();
  res.print = options.count("print") > 0;
  
  if (options.count("input") != 1) {
    std::cout << "You need to specify an input file" << std::endl; 
    exit(1);
  } else {
    res.input = options["input"].as<std::string>();
  }

  return res;
}

int main(int argc, char* argv[]) {
  Options options = parse_options(argc, argv);

  dori::stream::RecordSet* sampler = 
    new dori::stream::RecordSet(options.size, true);

  std::ifstream file(options.input);

  if (!file) {
    std::cout << "Error: file " << options.input  <<
       " does not exist" << std::endl;
    exit(1);
  }

  std::string word;
  while (file >> word) {
    sampler->offer(word);
  }

  std::cout << "Sample of " << sampler->size() << " elements."<< std::endl;

  if (options.print) {
    for (auto element : sampler->sample())
      std::cout << element << std::endl;
  }

}
