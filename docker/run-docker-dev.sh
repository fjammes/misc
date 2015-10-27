SRC_DIR=$HOME/src
RUN_DIR=$HOME/qserv-run

docker run -it --rm -h $(hostname)-docker \
    --name my_qserv \
    -v "$SRC_DIR":/home/dev/src \
    -v "$RUN_DIR":/home/dev/qserv-run \
    -u dev \
    fjammes/qserv:dev-uid \
    bash 
