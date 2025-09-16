import argparse
import re

# create parser object

# create a parser object
parser = argparse.ArgumentParser(description = "Check registers")

parser.add_argument("logfile", metavar="logfilename", type=str, 
    help="Input log file")
parser.add_argument("truthfile", metavar="truthfilename", type=str, 
    help="Expected truth file")

args=parser.parse_args()

logfd=open(args.logfile)
logdat = logfd.read()

expfd=open(args.truthfile)
expdat = expfd.read()

result = re.findall(r'\s*(h[01])\s*:\s*(x[0-9]+)\s*=\s*(\S+)', logdat)

expected = re.findall(r' expect (h[01])\s*:\s*(x[0-9]+)\s*=\s*(\S+)', expdat)

# create map
rmap = dict()
for entry in result:
    rmap[str(entry[0])+":"+entry[1]] = int(entry[2], 0)

print("Source file:", args.truthfile, "   Sim file:", args.logfile)

# check result
nwrong = 0    
for e in expected:
    key = e[0]+":"+e[1]
    val = int(e[2],0)

    if(val != rmap[key]):
        print(" ", key, "expected", val, " got ", rmap[key])
        nwrong += 1

print("Total failures =", nwrong, "of", len(expected), "tests")
print()