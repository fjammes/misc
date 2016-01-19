#!/bin/sh

usage() {
  cat << EOD

  Usage: $(basename "$0") image-tag

  Run a docker image containing Qserv deps and which mount source directory on
  local host.
EOD
}

if [ $# -ne 1 ] ; then
    usage
    exit 2
fi

IMAGE_TAG=$1

SRC_DIR=$HOME/src
RUN_DIR=$HOME/qserv-run
IMAGE=qserv/qserv:"$IMAGE_TAG"

docker run -it --rm -h $(hostname)-docker \
    --name my_qserv \
    -v "$SRC_DIR":/home/dev/src \
    -v "$RUN_DIR":/home/dev/qserv-run \
    -u dev \
    "$IMAGE" \
    bash 
