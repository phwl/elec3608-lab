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
if "-h" in opts:
    print('Usage: testbench.py [-t] [-s]')
    exit(1)


tb = pyverilator.PyVerilator.build('testbench.sv')
if (tkmode):
    tb.start_gtkwave()
    print(tb.io)
    tb.send_to_gtkwave(tb.io)
    tb.send_to_gtkwave(tb.internals)
i = 0
while True:
    r(tb, i < 2)
    i = i + 1
    if (int(tb.internals['dut'].trapped)):
        break
    if (stepmode):
        input()

# check return value is correct
rr = int(tb.internals['x10'])
print('Return_reg {} ({} cycles)'.format(rr, i)) 

if tkmode:
    input("Press Enter to exit...")
    tb.stop_gtkwave()

