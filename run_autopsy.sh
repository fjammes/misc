DIR=$(cd "$(dirname "$0")"; pwd -P)

docker run -it --net=host \
    --user=$(id -u):$(id -g $USER) \
    --env="DISPLAY" \
    --volume="$DIR/homefs:/home/$USER" \
    --volume="/etc/group:/etc/group:ro" \
    --volume="/etc/passwd:/etc/passwd:ro" \
    --volume="/etc/shadow:/etc/shadow:ro" \
    --volume="/etc/sudoers.d:/etc/sudoers.d:ro" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    bannsec/autopsy:latest \
    bash 

# Run autopsy
# chmod 777 /opt/autopsy-4.13.0/bin/autopsy
# jdkhome=/opt/jdk1.8.0_201/ /opt/autopsy-4.13.0/bin/autopsy 
