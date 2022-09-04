import pyverilator
import random
import sys
from ctypes import c_int32, c_uint32

def r(tb, reset):
    tb.io.reset = reset
    tb.clock.tick()

opts = [opt for opt in sys.argv[1:] if opt.startswith("-")]
if "-t" in opts:
    tkmode = True
else:
    tkmode = False
if "-s" in opts:
    stepmode = True
else:
    stepmode = False
svfile = sys.argv[-1]
if "-h" in opts or ("-" in svfile):
    print('Usage: testbench.py [-t] [-s] filename.sv')
    exit(1)

tb = pyverilator.PyVerilator.build(svfile)
if (tkmode):
    tb.start_gtkwave()
    print(tb.io)
    tb.send_to_gtkwave(tb.io)
    tb.send_to_gtkwave(tb.internals)

i = 0
while i < 5000:
    r(tb, i < 4)
    i = i + 1
    if (int(tb.internals['dut'].trapped)):
        break
    if (stepmode):
        input()
rr = int(tb.internals['x10'])
print('x10={}, cycles={}'.format(rr, i)) 

if tkmode:
    input("Press Enter to exit...")
    tb.stop_gtkwave()

