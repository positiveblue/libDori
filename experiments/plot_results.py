import sys
import matplotlib.pyplot as plt
import numpy as np


def get_path(elements, algorithm, memory):
  return algorithm + "/" + elements + "/" + elements + "_" + algorithm + "_" + memory + ".out"

def get_data(file_path):
  with open(file_path, "r") as in_file:
    file_name = in_file.readline().rstrip()
    n_words = int(in_file.readline().rstrip().split(" ")[0])
    (algorithm, memory, n) = tuple(in_file.readline().rstrip().split(" "))
    memory = int(memory)
    n = int(n)
    values = []

    load_values = min(n, 100)
    for i in xrange(load_values):
      values.append(int(in_file.readline().rstrip()))
    
    return (file_name, n_words, algorithm, memory, values)

def draw_simple_plot(file_name, n_words, algorithm, memory, values):
  x_values = range(len(values))
  y_values = map(lambda y: (1.0*y)/n_words, values)
  
  (x_min, x_max) = (0, len(values))
  (y_min, y_max) = (min(y_values)-0.3, max(y_values)+0.3)

  mean = np.mean(y_values)
  sd = np.std(y_values)

  plt.plot(x_values, y_values, 'ro')
  plt.axis([x_min, x_max, y_min, y_max])
  
  plt.xlabel("mean=" + str(mean) + "  sd=" + str(sd))
  plt.ylabel("Normalized error")
  plt.title(algorithm + " " + str(memory) + " " + file_name)
  plt.show()


def draw_complex_plot(elements, memory):
  (file_name, n_words, _, _, r_values) = get_data (get_path(elements, "recordinality", memory))
  (_, _, _, _, kmv_values) = get_data (get_path(elements, "kmv", memory))
  (_, _, _, _, hll_values) = get_data (get_path(elements, "hll", memory))

  plt.title(file_name + " with memory " + str(memory))
  
  # Ploting Recordinality
  x_values = range(len(r_values))
  y_values = map(lambda y: (1.0*y)/n_words, r_values)

  mean = round(np.mean(y_values), 2)
  sd = round(np.std(y_values), 2)
  r_legend = "recordinality " + str(mean) + " " + str(sd)
  plt.plot(x_values, y_values, 'ro', label=r_legend)

  # Ploting kmv
  x_values = range(len(kmv_values))
  y_values = map(lambda y: (1.0*y)/n_words, kmv_values)

  mean = round(np.mean(y_values), 2)
  sd = round(np.std(y_values), 2)
  kmv_legend = "kmv " + str(mean) + " " + str(sd)
  plt.plot(x_values, y_values, 'bs', label=kmv_legend)

  # Ploting hll
  x_values = range(len(kmv_values))
  y_values = map(lambda y: (1.0*y)/n_words, hll_values)

  mean = round(np.mean(y_values), 2)
  sd = round(np.std(y_values), 2)
  hll_legend = "hll " + str(mean) + " " + str(sd)
  plt.plot(x_values, y_values, 'g^', label=hll_legend)
  
  plt.legend()
  plt.show()

def main(argv):
  if len(argv) == 2:
    file_path = argv[1]
    (file_name, n_words, algorithm, memory, values) = get_data (file_path)
    draw_simple_plot(file_name, n_words, algorithm, memory, values)
  elif len(argv) == 3:
    (elements, memory) = (argv[1], argv[2])
    draw_complex_plot(elements, memory)
  else:
    print "error: sys.argv does not have the correct format"




if __name__ == "__main__":
    main(sys.argv)