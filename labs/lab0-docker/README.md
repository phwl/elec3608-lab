# Installing Docker 2022 ELEC3608 version

Here are installation instructions for installing Docker and running Modelsim for my [ELEC3608 Embedded Systems](https://cusp.sydney.edu.au/students/view-unit-page/alpha/ELEC3607) 
and [ELEC3608 Computer Architecture](https://cusp.sydney.edu.au/students/view-unit-page/alpha/ELEC3607) courses.
<!-- more -->

## 1. Installation
 * (Windows)
   1. Install MobaXterm <https://mobaxterm.mobatek.net/download-home-edition>
   1. (Windows 10 all versions) Use instructions at <https://docs.docker.com/docker-for-windows/install/>
   to install Stable version of Docker Desktop for Windows (follow them carefully). 
   1. Run Docker Desktop by double-clicking the icon on the desktop

 * (MacOS)
   1. Download and install stable version from <https://docs.docker.com/docker-for-mac/install/> (or <https://docs.docker.com/docker-for-mac/apple-silicon/> for the M1 mac in which case the ```--platform linux/amd64``` in the command lines below are mandatory)
   1. Run Docker Desktop by clicking the Docker icon

## 2 Testing
### 2.1 Hello world
To test basic Docker functionality, type ```docker run hello-world``` in the command window. Your output should be something like:

```
Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (amd64)
 3. The Docker daemon created a new container from that image which runs the
    executable that produces the output you are currently reading.
 4. The Docker daemon streamed that output to the Docker client, which sent it
    to your terminal.

To try something more ambitious, you can run an Ubuntu container with:
 $ docker run -it ubuntu bash

Share images, automate workflows, and more with a free Docker ID:
 https://hub.docker.com/

For more examples and ideas, visit:
 https://docs.docker.com/get-started/
```

### 2.2 X Server
We need to use the X Server to display graphical output. This
tests X Windows basic functionality.

 * (Windows setup) 
    1. Run MobaXterm and "Start a local terminal"
    1. Type ```docker run -it fr3nd/xeyes```

 * (x86 MacOS X setup)
    1. Install homebrew (see ```https://brew.sh/```) 
    1. Use homebrew to install xquartz ```brew install --cask xquartz'''
    1. Run the ```Xquartz``` X Server program by clicking on the icon, an xterm window should appear
    1. Set “Allow connections from network clients” in XQuartz -> Preferences
    1. In the xterm window type 
``` bash
$ xhost +localhost
localhost being added to access control list
$ export DISPLAY=host.docker.internal:0
$ docker run -it -e DISPLAY=$DISPLAY fr3nd/xeyes 
```

If you get an error with the xhost command, try a reboot.
You should see the window below and the eyes should move with your mouse.

![xeyes](http://phwl.org/assets/images/2022/02/docker-xeyes.png "xeyes")

 * (M1 MacOS X setup)
The commands are the same as for x86 MacOS except you add ```--platform linux/amd64```, e.g.
``` bash
$ docker run --platform linux/amd64 -it -e DISPLAY=$DISPLAY fr3nd/xeyes 
```

### 2.3 ELEC3608 Base Image
This tests the ELEC3608 base image.
Make sure you have set up your X Server and can execute the
previous Xeyes example.

 * (Windows) First copy the ELEC3608 lab files to /cygdrive/c/elec3608:
 ```bash
 mkdir /cygdrive/c/elec3608
 cd /cygdrive/c/elec3608
 git clone https://github.com/phwl/elec3608-lab
 ```
You should now be able to run 
```docker run -it -v /c/elec3608:/config phwl/elec3608-base:latest``` 
from within a MobaXterm terminal.
 * (MacOS x86 and M1) You should now be able to do ```docker run --platform linux/amd64 -it -e DISPLAY=$DISPLAY:0 -v `pwd`:/config phwl/elec3608-base:latest```.

If everything works, a prompt should appear and ```ls``` should show your local directory that was mounted.

``` bash
% docker run --platform linux/amd64 -it -e DISPLAY=$DISPLAY -v `pwd`:/config phwl/elec3608-base
To run a command as administrator (user "root"), use "sudo <command>".
See "man sudo_root" for details.

elec3608@c29f67b9ffb6:~$ ls
README.md
```

Within Docker, the directory on your local home directory will be mapped 
to your local directory. Use this to access your files and store your outputs. Verify you can also run ```xeyes```.

## 3 Troubleshooting
 * Update your operating system to the latest version. My Windows 10 Pro installation was available <https://www.microsoft.com/en-us/software-download/windows10ISO>.
 * Check you have virtualization enabled in your BIOS
