#include<iostream>
#include <string>
#include <fstream>

#include "dori.hpp"


dori::stream::ICardinality* create_estimator(std::string algorithm, int size=64) {
  dori::stream::ICardinality* estimator;

  if (algorithm == "recordinality") {
    estimator = new dori::stream::Recordinality(size);
  } else if (algorithm == "kmv") {
    estimator = new dori::stream::KMV(size);
  } else if (algorithm == "hll") {
    estimator = new dori::stream::HyperLogLog(size);
  } else if (algorithm == "dummy") {
    estimator = new dori::stream::DummyCounter();  
  } else {
    // TODO: Exit with error, call --help
    std::cout << "Error: algorithm " << algorithm  <<
      " does not exist" << std::endl;
    exit(1);
  }

  return estimator;
}

void preprocessing(std::string file_name, std::string algorithm, int memory) {
  auto estimator = create_estimator("dummy");
  
  std::ifstream file(file_name);

  if (!file) {
    std::cout << "Error: file " << file_name  <<
       " does not exist" << std::endl;
    exit(1);
  }

  std::string word;
  
  while (file >> word) {
    estimator->offer(word);
  }

  std::cout << file_name << ' ' << estimator->cardinality() << ' '
    << estimator ->elementsOffered() << std::endl;
  
  std::cout << algorithm << ' ' << memory << std::endl;
}

void processing(std::string file_name, std::string algorithm, int memory) {
  auto estimator = create_estimator(algorithm, memory);
  
  std::ifstream file(file_name);

  std::string word;
  
  while (file >> word) {
    estimator->offer(word);
  }

  std::cout << estimator->cardinality() << std::endl;

}

int main(int argc, char* argv[]) {
  
  std::string file_name = argv[1];
  std::string algorithm = argv[2];
  int memory = strtol(argv[3], NULL, 10);

  preprocessing(file_name, algorithm, memory);

  int N = 100;

  for (int i = 0; i < N; ++i) {
    processing(file_name, algorithm, memory);
  }
}