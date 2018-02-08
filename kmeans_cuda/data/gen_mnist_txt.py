import numpy as np
from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets("/home/pi/stone/c++/kmeans_cuda/data")
images=mnist.train.images[:5000]
labels=mnist.train.labels[:5000].astype(int)
np.savetxt("/home/pi/stone/c++/kmeans_cuda/data/images.txt",images)
np.savetxt("/home/pi/stone/c++/kmeans_cuda/data/lables.txt",labels,fmt="%d")# note: must specify the datatype.
