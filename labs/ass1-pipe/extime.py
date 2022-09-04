# importing required modules
import argparse
from functools import reduce
from statistics import geometric_mean
import re

# create a parser object
parser = argparse.ArgumentParser(description = "Get execution time")

# add argument
parser.add_argument("extime", nargs = '*', metavar = "fname", type = str,
                     help = "First is the nextpnr file then the result files.")

# parse the arguments from standard input
args = parser.parse_args()

print("Test summary")
# The first filename is the log file, extract the frequency
fd = open(args.extime[0], "r")
nprfile = fd.read()
freqs = re.findall(r': ([\d\.]*) MHz', nprfile)
minfreq = reduce(lambda x, y : min(float(x), float(y)), freqs) * 1.0e6
period = 1.0 / minfreq 
print('period:', period)
fd.close()

# The remaining files are result files, extract the cycles and x10
exedict = {'test1.result': 4.86223662884927e-07,
        'test2.result': 4.051863857374392e-07,
        'test3.result': 1.0804970286331712e-06,
        'test4.result': 3.5116153430578064e-06,
        'test5.result': 2.5445705024311184e-05}
lextime = []
for fname in args.extime[1:]:
    fd = open(fname, "r")
    efile = fd.read()
    m = re.search(r'x10=(.*), cycles=(.*)', efile)
    extime = float(m.group(2)) * period 
    nextime = extime / exedict[fname]
    lextime.append(nextime)
    print("{}: x10={} cycles={} extime={} normextime={}".format(
        fname, m.group(1), m.group(2), extime, nextime))
print("Geometric mean={}".format(geometric_mean(lextime)))
