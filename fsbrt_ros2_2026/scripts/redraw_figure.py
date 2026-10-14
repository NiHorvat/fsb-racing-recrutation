import pickle
import sys
import matplotlib.pyplot as plt
 

"""
Author: Luka Bradarić-Lisić

FSBRT Autonomous - Recruitment task

Plots saved figure from .matfig file.  
"""

#only 1 input parameter must be given (pay attention to put that argument under "")
if len(sys.argv) != 1 + 1:
    raise Exception("Invalid number of arguments! Only 1 argument needed (path to '.matfig' file to be drawn).")

path = sys.argv[1]

try:
    mat_file = open(path, "rb")
except:
    raise Exception("Cannot open file... maybe invaild path...")

fig = plt.figure()
plt.close()

fig = pickle.load(mat_file)

plt.show()