#!/usr/bin/python

from subprocess import call
import os

def generate_cmd(m_file, algorithm, memory, iterations):
  # ./exp_cardinality data/100.txt recordinality 16 500
  data_path = "datasets/"
  file_path = data_path + m_file + ".txt"
  
  cmd = "./exp_cardinality " + file_path 
  cmd = cmd + " " + algorithm 
  cmd = cmd + " " + memory
  cmd = cmd + " " + iterations

  return cmd

def generate_output_file(m_file, algorithm, memory):
  # 100_recordinality_64.out
  
  out_path = "results/" + algorithm + "/" + m_file + "/"
  out_file_name =  m_file + "_" + algorithm + "_" + memory + ".out"
  final_file = out_path + out_file_name
  
  if not os.path.exists(out_path):
    os.makedirs(out_path)

  if os.path.exists(final_file):
    os.remove(final_file)
  return final_file
  
def main():
  
  iterations = "100"
  algorithms = ["recordinality", "kmv", "hll"]
  memory = ["16", "32", "64", "128"]
  list_of_files = ["1000", "5000", "10000", "25000", "50000", "100000", "250000", \
  "500000", "1000000"]

  for m_file in list_of_files:
    for algorithm in algorithms:
      for m_memory in memory:
        cmd = generate_cmd(m_file, algorithm, m_memory, iterations)
        out_file_path = generate_output_file(m_file, algorithm, m_memory)
        print("Executing " + cmd)
        with open(out_file_path, "w+") as outfile:
          outfile.write(m_file + ".txt \n")
          outfile.flush()
          call(cmd, shell=True, stdout=outfile)

if __name__ == "__main__":
  main()

