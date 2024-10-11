CC = riscv32-unknown-elf-gcc
CFLAGS = -march=rv32i -w
TIME = time

dhrystone: dhrystone.c
	$(CC) $(CFLAGS) dhrystone.c -o dhrystone

run:
	spike --isa=rv32i --ic=2:4:8 --dc=2:4:8  /opt/riscv/riscv32-unknown-elf/bin/pk dhrystone

clean:
	(set nonomatch;rm -f dhrystone dhrystoneR dhrystoneO dhrystoneRO *.o)
