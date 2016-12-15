#include <string>
#include <fstream>

#include "libstream.hpp"
#include "cxxopts/cxxopts.hpp"

struct Options {
  int size;
  std::string algorithm;
  std::string input;
};


Options parse_options(int argc, char* argv[]) {
  
  Options res;

  cxxopts::Options options(argv[0]);
  
  options.add_options()
    ("a,algorithm", "recordinality, kmv, hyperloglog", cxxopts::value<std::string>()
      ->default_value("recordinality"))
    ("s,size", "Aveilable memory", cxxopts::value<int>()
      ->default_value("64"))
    ("i,input", "Input file", cxxopts::value<std::string>())
    ("help", "Print help")
  ;



  options.parse(argc, argv);

  
  res.size = options["size"].as<int>();
  res.algorithm = options["algorithm"].as<std::string>();
  
  if (options.count("input") != 1) {
    std::cout << "You need to specify an input file" << std::endl; 
    exit(1);
  } else {
    res.input = options["input"].as<std::string>();
  }

  return res;
}


ls::stream::ICardinality* create_estimator(std::string algorithm, int size) {
  ls::stream::ICardinality* estimator;

  if (algorithm == "recordinality") {
    estimator = new ls::stream::Recordinality(size);
  } else if (algorithm == "kmv") {
    estimator = new ls::stream::KMV(size);
  } else {
    // TODO: Exit with error, call --help
    exit(1);
  }

  return estimator;
}


int main(int argc, char* argv[]) {
  Options options = parse_options(argc, argv);

  ls::stream::ICardinality* estimator = 
    create_estimator(options.algorithm, options.size);

  std::ifstream file(options.input);

  if (!file) {
    std::cout << "Error: file " << options.input  <<
       " does not exist" << std::endl;
    exit(1);
  }

  std::string line;
  while (!file.eof()) {
    std::getline(file, line);
    estimator->offer(line);
  }

  std::cout << "Cardinality (Aprox): " << estimator->cardinality() << std::endl;
  std::cout << "Total elements: " << estimator->elementsOffered() << std::endl;
}