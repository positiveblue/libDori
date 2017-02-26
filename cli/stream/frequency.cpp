#include <string>
#include <fstream>
#include <algorithm>


#include "dori.hpp"
#include "cxxopts/cxxopts.hpp"

struct Options {
  bool print;
  int size;
  std::string algorithm;
  std::string input;
};


Options parse_options(int argc, char* argv[]) {
  
  Options res;

  cxxopts::Options options(argv[0]);
  
  options.add_options()
    ("a,algorithm", "dummy", cxxopts::value<std::string>()
      ->default_value("dummy"))
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

  dori::stream::IFrequency* estimator = 
    new dori::stream::DummyFrequency();

  std::ifstream file(options.input);

  if (!file) {
    std::cout << "Error: file " << options.input  <<
       " does not exist" << std::endl;
    exit(1);
  }

  std::string word;
  while (file >> word) {
    estimator->offer(word, 1);
  }

  std::cout << "Total elements offered: " << estimator->elementsOffered() << std::endl;

  
  auto frequencies = estimator->topK();
  std::vector<std::string> topK;

  for(auto const& imap: frequencies)
      topK.push_back(imap.first);

  std::sort(topK.begin(), topK.end(), 
    [&frequencies] (const std::string& a, const std::string& b) {
    
    return frequencies[a] > frequencies[b];
  });


  for(int i = 0; i < options.size && i < topK.size(); ++i) {
    std::cout << topK[i] << ' ' << frequencies[topK[i]] << std::endl;
  }

}
