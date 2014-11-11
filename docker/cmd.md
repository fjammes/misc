# load Dockerfile
docker build - < Dockerfile

# interactive
docker run -i -t 93da0c9fbff1 /bin/bash

# create image
docker ps
docker commit -m="Add dependencies and qserv account" -a="Fabrice Jammes" 767c0f51938b fjammes/qserv:0.0.1
docker push fjammes/qserv:0.0.1
