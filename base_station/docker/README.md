# Docker

This directory provides the user with a method to quickly build and test the Micro-ROS tutorials in a docker container.  Scripts are provided to create the docker image and to start, stop and attach to the docker container.

## Basic operation

The script `./build.bash` creates the docker container.  Do this just once!  This process took about 5 minutes on my PC, so get on with something else while the image is built.

To start the container, use `./start.bash`.  This script starts the container and leaves it running until `./stop.bash` is called. The script `./start.bash` also mounts an external directory on to the container directory `/home/build/ws`.  The external directory can be specified when calling `./start.bash`, e.g.

```bash
cd ~/my-workspace
~/git/raspi-robot-esp32/base_station/docker/start.bash `pwd`
```

If no path is given on the command line, the `start.bash` script will create a workspace directory using the pattern `$HOME/<docker container name>_ws`.

If you need to change the mounted directory on the container, you need to destroy the current container by stopping the container using `./stop.bash`, remove the container using `./rm_container.bash` and then start a new container using `.start.bash`.

When the container is running, you can get a Bash user prompt attached to the container using `./attach.bash`.  The `./attach.bash` script can be used to open multiple terminal sessions on the docker container by calling the script as many times as needed.

## Building the agent

The script `setup_ws.bash` clones the Micro-ROS setup repo and builds the micro-ROS agent. To run, attach a terminal shell to the docker and then run:

```bash
cd ~/ws
./setup_ws.bash
```

To verify that the agent has been build correctly, run the command:

```bash
./install/micro_ros_agent/lib/micro_ros_agent/micro_ros_agent udp4 -p 8888
```

## Development work flow

### Setup

This is what you need to do every time you start your day.

TODO

### Building and testing the rover code

TODO