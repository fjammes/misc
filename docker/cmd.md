# load Dockerfile
docker build -t="fjammes/qserv:dev" - < Dockerfile

# interactive
docker run -i -t "fjammes/qserv:dev" /bin/bash

# create image
docker ps
docker commit -m="Add dependencies and qserv account" -a="Fabrice Jammes" 767c0f51938b fjammes/qserv:0.0.1
docker push fjammes/qserv:0.0.1
