SRC_DIR=$HOME/src/qserv
RUN_DIR=$HOME/qserv-run

docker run -it --rm -h $(hostname)-docker \
    -v "$SRC_DIR":/home/dev/src/qserv \
    -v "$RUN_DIR":/home/dev/qserv-run \
    -u dev \
    fjammes/qserv:dev-uid \
    bash 
