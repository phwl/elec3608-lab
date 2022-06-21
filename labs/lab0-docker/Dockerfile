FROM --platform=linux/amd64 ubuntu:20.04
LABEL maintainer="PHWL <phwl@users.noreply.github.com>"

# variables
ENV TZ=Australia/Sydney

ARG VDLOAD=https://github.com/mi-g/vdhcoapp/releases/download/v1.6.3/net.downloadhelper.coapp-1.6.3-1_amd64-glibc-2.27.deb
ARG USER=elec3608

# install packages we need
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && apt-get install -y build-essential make sudo pip git
RUN apt-get install -y verilator gtkwave vim x11-apps
RUN apt-get install -y gcc-riscv64-unknown-elf srecord
RUN pip install fusesoc

# Create a user with same username and password
RUN adduser --system --group $USER && usermod -aG sudo $USER && echo "${USER}:${USER}" | chpasswd

USER $USER 
ENV HOME /config
WORKDIR /config
CMD [ "/bin/bash" ]
