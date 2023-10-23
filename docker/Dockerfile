
# This Dockerfile may be used to create an Ubuntu 22.04 image, configured for Swift development.
# From this file's home directory, run: docker build -t swift-build:latest .

FROM swift:focal

USER root

RUN apt update && apt install -y emacs build-essential devscripts debhelper dh-make
RUN mkdir /root/telemetry

COPY libpl.deb /root/telemetry

RUN dpkg --install /root/telemetry/libpl.deb
