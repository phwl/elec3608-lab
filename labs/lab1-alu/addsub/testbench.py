import pyverilator
from ctypes import c_int32, c_uint32

ALU_ADD = 1
ALU_SUB = 2
ALUSYM = { ALU_ADD: '+', ALU_SUB: '-' }

def uint32(v):
    return c_uint32(v).value

# This is the function we are trying to emulate in our system verilog 
def addsub(alu_function, a, b):
    if alu_function == ALU_ADD:
        r = a + b
    elif alu_function == ALU_SUB:   
        r = a - b
    else:
        r = 0
    return uint32(r)

def test_addsub(tb, alu_function, a, b):
    tb.io.alu_function = alu_function
    tb.io.op_a = a
    tb.io.op_b = b

    cresult = addsub(alu_function, a, b)    # computer result
    vresult = uint32(tb.io.result)             # verilog result
    ok = cresult == vresult
    print("{:08x} {} {:08x}\tresult={:08x} (cresult={:08x}) {}".\
            format(a, ALUSYM[alu_function], b, vresult, cresult, ok));
    return ok

tb = pyverilator.PyVerilator.build('addsub.sv')
ok = test_addsub(tb, ALU_ADD, 1, 2); 
ok = test_addsub(tb, ALU_ADD, 0xffffffff, 2); 
ok = test_addsub(tb, ALU_ADD, 0x7fffffff, 0xFF); 
ok = test_addsub(tb, ALU_SUB, 0xdeadbeef, 0xdeadbeef); 
ok = test_addsub(tb, ALU_SUB, 0xdeadbeef, 2); 
ok = test_addsub(tb, ALU_SUB, 0xe1e10, 0xdeadbeef); 

