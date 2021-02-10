FROM gitpod/workspace-full-vnc
RUN sudo apt update && sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev libxrandr-dev xorg-dev wget -y
RUN wget https://dist.ipfs.io/go-ipfs/v0.7.0/go-ipfs_v0.7.0_linux-amd64.tar.gz && tar xf go-ipfs_v0.7.0_linux-amd64.tar.gz && cd go-ipfs && sudo ./install.sh
# Install custom tools, runtimes, etc.
# For example "bastet", a command-line tetris clone:
# RUN brew install bastet
#
# More information: https://www.gitpod.io/docs/config-docker/
