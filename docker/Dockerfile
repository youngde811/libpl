#-*- mode: Dockerfile -*-

# This Dockerfile may be used to create an Ubuntu 22.04 arm64 image, configured for Swift
# development and with our new Libpl library, that offers an attempt to emulate small parts
# of Apple's os.activity library, which is required by opentelemetry-swift.
#
# From this file's home directory, run: docker build -f Dockerfile_arm64 -t swift-build_arm64.

FROM swift:latest

ARG arch=aarch64
USER root

RUN apt update && apt install -y emacs build-essential devscripts debhelper dh-make dpkg-dev
RUN mkdir /root/telemetry

COPY libpl_1.0-1_${arch}.deb /root/telemetry
RUN dpkg --remove libpl &> /dev/null
RUN dpkg --install --force-architecture /root/telemetry/libpl_1.0-1_${arch}.deb
