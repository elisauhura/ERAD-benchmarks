FROM ubuntu:latest

# Setup apt & timezone
RUN apt-get update && \
    apt-get install -yq tzdata && \
    ln -fs /usr/share/zoneinfo/America/New_York /etc/localtime && \
    dpkg-reconfigure -f noninteractive tzdata

# Install programs
RUN apt -y install golang-go
RUN apt -y install python3
RUN apt -y install pip
RUN pip install numpy
RUN pip install matplotlib
RUN pip install pandas
RUN apt -y install micro
RUN apt -y install make
RUN apt -y install gccgo
RUN apt -y install gcc  
RUN apt -y install zsh
RUN apt -y install nano
RUN apt -y install pypy

# Para compilar o binary-trees em C
RUN apt -y install libapr1 libapr1-dev

# Dependência para a execução do perf
RUN apt -y install linux-tools-generic
RUN apt -y install linux-tools-common

WORKDIR /Minicurso_ERAD_Sul
COPY . /Minicurso_ERAD_Sul