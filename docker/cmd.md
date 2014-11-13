# load Dockerfile
docker build -t="fjammes/qserv:dev" - < Dockerfile

# interactive
# xrootd needs hostname which start with a string
docker run -h qserv-dev -i -t "fjammes/qserv:dev" /bin/bash

# create image
docker ps
docker commit -m="Add dependencies and qserv account" -a="Fabrice Jammes" 767c0f51938b fjammes/qserv:0.0.1
# or
docker commit qserv-dev 767c0f51938b qserv-dev
docker push fjammes/qserv:0.0.1