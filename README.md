# libDori


### Overview

libStream is a C++ library for sketching data streams. 
Given a data stream we are interested in answering questions like count distinct, quantiles, most frequent items,
and sampling.

A naive algorithm can sometimes not be the solution because the data streams is to large to be stored (e.g. Network traffic).
However, if approximate results are acceptable, there are probabilistic algorithms that can answer to these questions.

Usually the constractions of the algorithm are:
- It has to use constant/log(n) amount of memory
- It has to 