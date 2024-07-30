# Installing Docker 2023 Semester 2 - ELEC3608 Version
Here are installation instructions for installing Docker and running the software required for 
[ELEC3608 Computer Architecture](https://cusp.sydney.edu.au/students/view-unit-page/alpha/ELEC3608).
You should record all the steps taken to complete the installation in your lab book. Explain any difficulties encountered and how you solved the problem.

## 1. Installation
 * (Windows 11 or Windows 10)
   1. Install Ubuntu (under WSL2) <https://docs.microsoft.com/en-us/windows/wsl/install> and from Windows Start, run the "Ubuntu on Windows" app. If you type     ```lsb_release -a``` in the Linux window, Release should be 22.04 or higher. 
   1. Install and run Docker Desktop <https://docs.docker.com/desktop/install/windows-install/> with the default settings. Make sure to add your user to the docker-users group if your admin account is different to your user account.
      * During installation, make sure to select the option `Use WSL 2 instead of Hyper-V`.
      * In Docker Desktop menus, ensure that `Settings > Resources > WSL Integration` is turned on.
   1. In an Ubuntu window
       ```
       $ sudo usermod -aG docker $USER
       ```
       Then close the Ubuntu terminal and reopen.

 * (MacOS - MacOS 12.4 or higher)
   1. Install and run Docker Desktop <https://docs.docker.com/desktop/install/mac-install/> 

## 2 Testing
### 2.1 Hello world
To test basic Docker functionality, type ```docker run hello-world``` in the Ubuntu window. Your output should be something like:

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
    1.  In your Ubuntu window type ```docker run -it -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY gns3/xeyes```

 * (MacOS X setup)
    1. Install homebrew (see ```https://brew.sh/```) 
    1. Use homebrew to install xquartz ```brew install --cask xquartz'''. 
    1. Run the ```Xquartz``` X Server program by clicking on the icon, an xterm window should appear. By the way if you select Xquartz -> Settings -> Input -> Emulate 3 button mouse and then using Option left click on the mouse will allow pasting.
    1. Set “Allow connections from network clients” in XQuartz -> Settings -> Security
    1. In the xterm window type (if you get an error with the xhost command, try a reboot)
    ``` bash
    $ xhost +
    access control disabled, clients can connect from any hos
    $ export DISPLAY=host.docker.internal:0
    $ docker run --rm --platform linux/amd64 -it -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY gns3/xeyes
    ```

You should see a window similar to below and the eyes should move with your mouse.

![xeyes](http://phwl.org/assets/images/2022/02/docker-xeyes.png "xeyes")

### 2.3 ELEC3608 Image
This tests the ELEC3608 image.
Make sure you have set up your X Server and can execute the
previous Xeyes example. Then in your Windows Ubuntu terminal or MacOS xterm type:

 ```docker run --rm --platform linux/amd64 -it -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY  -v `pwd`:/config phwl/elec3608-cad:latest```

If everything goes well, a prompt should appear and ```ls``` should show your local directory that was mounted.

```bash
$ docker run --rm --platform linux/amd64 -it -e DISPLAY=$DISPLAY -v `pwd`:/config -v /tmp/.X11-unix:/tmp/.X11-unix phwl/elec3608-cad:latest

Unable to find image 'phwl/elec3608-cad:latest' locally
latest: Pulling from phwl/elec3608-cad
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
Status: Downloaded newer image for phwl/elec3608-cad:latest
docker: Error response from daemon: create .: volume name is too short, names should be at least two alphanumeric characters.
See 'docker run --help'.
elec3608@079a8ca5b594:~$ ls
(your files)
 ```
Within Docker, the directory on your local home directory will be mapped 
to your local directory so you can access your files and store your outputs. 

Next, while still inside the Docker container get the ELEC3608 files using git
and exit docker:
```bash
elec3608@079a8ca5b594:~$ git clone https://github.com/phwl/elec3608-lab.git
Cloning into 'elec3608-lab'...
remote: Enumerating objects: 5151, done.
remote: Counting objects: 100% (1392/1392), done.
remote: Compressing objects: 100% (526/526), done.
remote: Total 5151 (delta 857), reused 1321 (delta 790), pack-reused 3759
Receiving objects: 100% (5151/5151), 15.78 MiB | 2.50 MiB/s, done.
Resolving deltas: 100% (3226/3226), done.
elec3608@079a8ca5b594:~$ exit
$ 
```

You should now be able to run it in the future using
```bash
$ elec3608-lab/labs/common/rundocker 
```

Verify you can also run ```xeyes```.
```bash
$ elec3608-lab/labs/common/rundocker
docker run -u 1000 --rm --platform linux/amd64 -it -e DISPLAY=/private/tmp/com.apple.launchd.RdgqlIGLhx/org.xquartz:0 -v /tmp/.X11-unix:/tmp/.X11-unix -v /tmp:/config phwl/elec3608-cad:latest
To run a command as administrator (user "root"), use "sudo <command>".
See "man sudo_root" for details.

elec3608-1000@612659ec2d3a:~$ xeyes
```

## 3 Troubleshooting
 * Windows WSL2 and Docker <https://docs.docker.com/desktop/wsl/>.
 * Update your operating system to the latest version. 
 * Check you have virtualization enabled in your BIOS
 * It is also possible to use MobaXterm and the instructions at <http://phwl.org/2022/installing-docker-2022-version/>.
