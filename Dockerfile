FROM amd64/ubuntu:22.04

RUN apt update -y
RUN apt upgrage -y

# intall c++ dependencies
RUN apt install -y clang lldb lld make cmake git gdb curl wget vim 

WORKDIR /potion

ENV TERM=xterm-256color
ENV SHELL=/bin/bash
ENV Lang=C.UTF-8



