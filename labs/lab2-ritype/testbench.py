import pyverilator
import random
from ctypes import c_int32, c_uint32

def r(tb, reset):
    tb.io.reset = reset
    tb.clock.tick()

tb = pyverilator.PyVerilator.build('testbench.sv')
tb.start_gtkwave()
#print(tb.io)
#print(tb.internals)
tb.send_to_gtkwave(tb.io)
tb.send_to_gtkwave(tb.internals)
for i in range(14):
    r(tb, i < 2)

# check return value is correct
rr = int(tb.internals['return_reg'])
if (rr == 0xe1ec3608):
    print('Correct return_reg') 
else:
    print('Wrong return_reg {}'.format(hex(rr)))
input("Press Enter to exit...")
tb.stop_gtkwave()

