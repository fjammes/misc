#!/bin/sh

DOCKER_USER=dev

usage() {
  cat << EOD

  Usage: $(basename "$0") image-tag

  Run a docker image containing Qserv deps and which mount source directory on
  local host.
EOD
}

while getopts hu: c ; do
    case $c in
        h) usage ; exit 0 ;;
        u) DOCKER_USER="$OPTARG" ;;
        \?) usage ; exit 2 ;;
    esac
done
shift "$((OPTIND-1))"

if [ $# -ne 1 ] ; then
    usage
    exit 2
fi

IMAGE_TAG=$1

SRC_DIR=$HOME/src
RUN_DIR=$HOME/qserv-run
IMAGE=qserv/qserv:"$IMAGE_TAG"

docker run -it --rm -h "$(hostname)-docker" \
    --name my_qserv \
    -v "$SRC_DIR":/home/"$DOCKER_USER"/src \
    -v "$RUN_DIR":/home/"$DOCKER_USER"/qserv-run \
    -u "$DOCKER_USER" \
    "$IMAGE" \
    bash 
