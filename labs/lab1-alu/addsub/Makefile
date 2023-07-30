test: 
	python testbench.py

clean:
	rm -rf testbench testbench.vcd gtkwave.log *.vcd
	rm -rf obj_dir

rundocker:
	docker run --platform linux/amd64 -it -e DISPLAY=host.docker.internal:0 -v `pwd`:/config phwl/elec3608-cad:latest
