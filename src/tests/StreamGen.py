import numpy as np

def createDictionary(n, mu, sd):
    list_of_lengths = map(int, np.random.normal(mu, sigma, n))

    return list_of_lengths

def genStingStream(n=4096, m=16384, mu=7, sd=3):
    words = createDictionary(n, mu, sd)
    print words[:30]

if __nam__ == '__main__':
    main()