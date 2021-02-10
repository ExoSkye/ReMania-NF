FROM gitpod/workspace-full-vnc
RUN apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev libxrandr-dev xorg-dev

# Install custom tools, runtimes, etc.
# For example "bastet", a command-line tetris clone:
# RUN brew install bastet
#
# More information: https://www.gitpod.io/docs/config-docker/
