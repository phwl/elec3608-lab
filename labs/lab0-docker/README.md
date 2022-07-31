# Installing Docker 2022 Semester 2 - ELEC3608 Version
Here are installation instructions for installing Docker and running the software required for 
[ELEC3608 Computer Architecture](https://cusp.sydney.edu.au/students/view-unit-page/alpha/ELEC3608).

## 1. Installation
 * (Windows 10)
   1. I would urge Win10 users to upgrade to Win11. Follow instructions in Section 3 otherwise.

 * (Windows 11 - Version 21H2 OS Build 22000.795 or higher)
   1. Install and run Docker Desktop <https://docs.docker.com/desktop/install/windows-install/>. In Settings, make sure "Use the WSL 2 based engine" is selected.
   1. Install WSL2 (Ubuntu) <https://docs.microsoft.com/en-us/windows/wsl/install> and from Windows Start, run the "Ubuntu on Windows" app. If you type ```lsb_release -a``` in the Linux window, Release should be 20.04 or higher.

 * (MacOS - MacOS 12.4 or higher)
   1. Install and run Docker Desktop <https://docs.docker.com/desktop/install/mac-install/> 

## 2 Testing
### 2.1 Hello world
To test basic Docker functionality, type ```docker run hello-world``` in the command window. Your output should be something like:

```bash
$ docker run hello-world
Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
7050e35b49f5: Pull complete 
Digest: sha256:53f1bbee2f52c39e41682ee1d388285290c5c8a76cc92b42687eecf38e0af3f0
Status: Downloaded newer image for hello-world:latest

Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (arm64v8)
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
    1.  In your Ubuntu window type ```docker run -it -v /tmp/X11-unix:/tmp/.X11-unix fr3nd/xeyes``` 

 * (x86 MacOS X setup)
    1. Install homebrew (see ```https://brew.sh/```) 
    1. Use homebrew to install xquartz ```brew install --cask xquartz'''
    1. Run the ```Xquartz``` X Server program by clicking on the icon, an xterm window should appear
    1. Set “Allow connections from network clients” in XQuartz -> Preferences
    1. In the xterm window type (if you get an error with the xhost command, try a reboot)
    ``` bash
    $ xhost +
    access control disabled, clients can connect from any hos
    $ export DISPLAY=host.docker.internal:0
    $ docker run --platform linux/amd64 -it -e DISPLAY=$DISPLAY fr3nd/xeyes 
    ```

You should see a window similar to below and the eyes should move with your mouse.

![xeyes](http://phwl.org/assets/images/2022/02/docker-xeyes.png "xeyes")

### 2.3 ELEC3608 Base Image
This tests the ELEC3608 base image.
Make sure you have set up your X Server and can execute the
previous Xeyes example.

 * (Windows) From your Ubuntu window type \
 ```docker run -it -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY  -v `pwd`:/config phwl/elec3608-base:latest```
 * (MacOS x86 or M1) From xterm type \
 ```docker run --platform linux/amd64 -it -e DISPLAY=$DISPLAY -v `pwd`:/config phwl/elec3608-base:latest```

If everything works, a prompt should appear and ```ls``` should show your local directory that was mounted.

```bash
$ ls
Dockerfile	Makefile	README.md
$ docker run --platform linux/amd64 -it -e DISPLAY=$DISPLAY -v `pwd`:/config phwl/elec3608-base:latest
Unable to find image 'phwl/elec3608-base:latest' locally
latest: Pulling from phwl/elec3608-base
d7bfe07ed847: Pull complete
40dcc342278c: Pull complete
74c28b8c2172: Pull complete
313047efccdd: Pull complete
82301e1dbf3f: Pull complete
1a94c54f608c: Pull complete
65c59d4242d2: Pull complete
f53da11c4abc: Pull complete
60b18815e8a2: Pull complete
c6175c8df07c: Pull complete
18c69afe1063: Pull complete
Digest: sha256:29c813a7f39a3f9e153bf92b9967acfadae4ee930380b75bf2e573620c9b2f00
Status: Downloaded newer image for phwl/elec3608-base:latest
docker: Error response from daemon: create .: volume name is too short, names should be at least two alphanumeric characters.
See 'docker run --help'.
elec3608@079a8ca5b594:~$ ls
Dockerfile  Makefile  README.md
 ```
Within Docker, the directory on your local home directory will be mapped 
to your local directory. Use this to access your files and store your outputs. Verify you can also run ```xeyes```.

## 3 MobaXterm (for Win10 Systems and if the instructions above don't work under Win11)
 1. Install MobaXterm Home Edition (Installer edition) <https://mobaxterm.mobatek.net/download-home-edition.html>
 1. Install Docker <https://docs.docker.com/desktop/install/windows-install/> (follow instructions carefully)
 1. Run Docker Desktop by double-clicking the icon on the desktop
 1. Follow instructions in Section 2.1 to check docker "Hello world" application.
 1. Run MobaXterm and “Start a local terminal”. Type ```docker run -it fr3nd/xeyes``` in the MobaXterm terminal. This should bring up ```xeyes``` as described in Section 2.2.
 1. Type 
     ```bash
     mkdir /cygdrive/c/elec3608
     docker run -it -v /cygdrive/c/elec3608:/config phwl/elec3607-base:latest
     ``` 
     from within the MobaXterm terminal. If it returns an error, try 
     ```bash
     mkdir /c/elec3608
     docker run -it -v /c/elec3608:/config phwl/elec3607-base:latest
     ``` 
     The first command creates the /c/elec3608 directory on your host machine. Running docker should bring up the ELEC3608 base image as described in Section 2.3, and any files in /c/elec3608 on the host system should be visible inside the docker container in /config.

## 4 Troubleshooting
 * Update your operating system to the latest version. 
 * Check you have virtualization enabled in your BIOS
 * It is also possible to use MobaXterm and the instructions at <http://phwl.org/2022/installing-docker-2022-version/>.
