FROM --platform=linux/amd64 ubuntu:22.04 as builder

ENV RISCV "/opt/riscv"

# RISCV toolchain
RUN apt-get update && \
	apt-get -y install autoconf automake autotools-dev curl \
	python3 libmpc-dev libmpfr-dev libgmp-dev gawk \
	build-essential bison flex texinfo gperf libtool \
	patchutils bc zlib1g-dev libexpat-dev git

ENV PATH="$RISCV/bin:${PATH}"
WORKDIR /tmp
RUN git clone https://github.com/riscv/riscv-gnu-toolchain && cd riscv-gnu-toolchain && ./configure --prefix=$RISCV --with-arch=rv32i --with-abi=ilp32 && make

# RUN apt-get install -y autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev libusb-1.0-0-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev device-tree-compiler pkg-config libexpat-dev && git clone https://github.com/riscv-software-src/riscv-tools.git && cd riscv-tools && git submodule update --init --recursive && ./build-rv32ima.sh

RUN apt-get install -y autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev libusb-1.0-0-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev device-tree-compiler pkg-config libexpat-dev && git clone https://github.com/riscv/riscv-isa-sim.git && cd riscv-isa-sim && mkdir build && cd build &&  ../configure --prefix=$RISCV --with-isa=RV32I && make && make install

RUN git clone https://github.com/riscv/riscv-pk.git && cd riscv-pk && mkdir build && cd build &&  ../configure --prefix=$RISCV --host=riscv32-unknown-elf --with-arch=rv32i --with-abi=ilp32  && make && make install

FROM --platform=linux/amd64 ubuntu:22.04 as image
LABEL maintainer="PHWL <phwl@users.noreply.github.com>"

# variables
ENV TZ=Australia/Sydney

ENV RISCV "/opt/riscv"
ARG VDLOAD=https://github.com/mi-g/vdhcoapp/releases/download/v1.6.3/net.downloadhelper.coapp-1.6.3-1_amd64-glibc-2.27.deb
ARG USER=elec3608

# install packages we need
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && apt-get install -y build-essential make sudo pip git cmake
RUN apt-get install -y verilator gtkwave vim x11-apps ghostscript python3-tk dbus-x11
RUN apt-get install -y gcc-riscv64-unknown-elf srecord device-tree-compiler

# OSS CAD Suite
RUN apt-get install -y yosys nextpnr-ice40

# pyverilator
RUN ln /usr/bin/python3 /usr/bin/python && cd /usr/src && git clone https://github.com/phwl/pyverilator && cd /usr/src/pyverilator && pip install -e .

# setup vim
COPY vimrc.local /etc/vim/vimrc.local

# Verilator v4.020 from source
# RUN apt-get install -y git perl python3 make g++ libfl2 libfl-dev zlibc zlib1g zlib1g-dev autoconf bison
# RUN cd /usr/src && git clone https://github.com/verilator/verilator.git && chown -R ${USER}.${USER} verilator 
# RUN cd /usr/src && git clone https://github.com/csail-csg/pyverilator.git && chown -R ${USER}.${USER} pyverilator
# RUN cd /usr/src/verilator && git checkout v4.020 && autoconf && ./configure && make

RUN mkdir -p /opt/riscv
WORKDIR /opt/riscv
COPY --from=builder /opt/riscv ./

# Create a user with same username and password
RUN adduser --system --group $USER && usermod -aG sudo $USER && echo "${USER}:${USER}" | chpasswd

RUN chown -R ${USER}.${USER} /usr/src/pyverilator

USER $USER 
ENV HOME /config
ENV PATH="/opt/riscv/bin:${PATH}"
WORKDIR /config
CMD [ "/bin/bash" ]
