FROM debian:stable
RUN apt-get update && apt-get install -y git 
RUN groupadd -r qserv && useradd -r -m -g qserv qserv
USER qserv
env HOME /home/qserv
RUN mkdir "$HOME"/src;git clone git://git.lsstcorp.org/LSST/DMS/qserv "$HOME"/src/qserv
USER root
# TODO add -y and missing deps
RUN yes | "$HOME"/src/qserv/admin/bootstrap/qserv-install-deps-debian-wheezy.sh
RUN apt-get -y install bison bzip2 curl flex gettext libbz2-dev make
# development tools
RUN apt-get -y install vim byobu
USER qserv
# TODO run newinstall in batch mode and support sh 
#RUN yes | bash "$HOME"/src/qserv/admin/tools/qserv-install.sh -i "$HOME"/stack
