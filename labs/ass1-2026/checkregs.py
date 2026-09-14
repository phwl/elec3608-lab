import argparse
import re

#######
## A script to extract the expected ending register values for comparison
##
## You simply put a text list in a comment inside each source file (*.s file)
## fill in the expected end-state registers
##
## Example (note the assembler comment style is c-style, not c++)
##        /* expected result:
##            expect h0:x2 = 0xc0 (core 0)
##            expect h0:x3 = 1200
##            expect h0:x5 = 1 (fail)
##            expect h0:x6 = 0xc1 (core 1)
##        */
## @author Rich Rademacher

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

# This regex parses the output log file
result = re.findall(r'\s*(h[01])\s*:\s*([^= ]+)\s*=\s*(\S+)', logdat)

# This regex parses the expected values from the assembly source file
expected = re.findall(r' expect (h[01])\s*:\s*([^= ]+)\s*=\s*(\S+)', expdat)

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