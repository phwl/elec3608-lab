FROM --platform=linux/amd64 ubuntu:20.04
LABEL maintainer="PHWL <phwl@users.noreply.github.com>"

# variables
ENV TZ=Australia/Sydney

ARG VDLOAD=https://github.com/mi-g/vdhcoapp/releases/download/v1.6.3/net.downloadhelper.coapp-1.6.3-1_amd64-glibc-2.27.deb
ARG USER=elec3608

# install packages we need
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && apt-get install -y build-essential make sudo pip git
RUN apt-get install -y verilator gtkwave vim x11-apps ghostscript python3-tk dbus-x11
RUN apt-get install -y gcc-riscv64-unknown-elf srecord
RUN pip install fusesoc 

# pyverilator
RUN ln /usr/bin/python3 /usr/bin/python && cd /usr/src && git clone https://github.com/phwl/pyverilator && cd /usr/src/pyverilator && pip install -e .

# setup vim
COPY vimrc.local /etc/vim/vimrc.local

# Verilator v4.020 from source
# RUN apt-get install -y git perl python3 make g++ libfl2 libfl-dev zlibc zlib1g zlib1g-dev autoconf bison
# RUN cd /usr/src && git clone https://github.com/verilator/verilator.git && chown -R ${USER}.${USER} verilator 
# RUN cd /usr/src && git clone https://github.com/csail-csg/pyverilator.git && chown -R ${USER}.${USER} pyverilator
# RUN cd /usr/src/verilator && git checkout v4.020 && autoconf && ./configure && make

# Create a user with same username and password
RUN adduser --system --group $USER && usermod -aG sudo $USER && echo "${USER}:${USER}" | chpasswd

RUN chown -R ${USER}.${USER} /usr/src/pyverilator

USER $USER 
ENV HOME /config
WORKDIR /config
CMD [ "/bin/bash" ]
