FROM debian:stable
MAINTAINER Fabrice Jammes <fabrice.jammes@in2p3.fr>
RUN apt-get update
RUN apt-get install -y git
RUN groupadd -r qserv
RUN useradd -r -m -g qserv qserv
USER qserv
ENV HOME /home/qserv
# Using $HOME below require Docker 1.3
WORKDIR /home/qserv
RUN mkdir src
RUN git clone git://git.lsstcorp.org/LSST/DMS/qserv src/qserv
RUN cd src/qserv; git checkout u/fjammes/DM-1497
USER root
RUN src/qserv/admin/bootstrap/qserv-install-deps-debian-wheezy.sh
# development tools
RUN apt-get -y install vim byobu
USER qserv
# Running newinstall in batch mode should remove above line: DM-1495
RUN GIT=yes; ANACONDA=no; printf "$GIT\n$ANACONDA\n" > answers.txt
# LSST stack require bash
RUN bash src/qserv/admin/tools/qserv-install.sh -i ${HOME}/stack < answers.txt
RUN rm answers.txt
