FROM ubuntu:latest

# Setup apt & timezone
RUN apt-get update && \
    apt-get install -yq tzdata && \
    ln -fs /usr/share/zoneinfo/America/New_York /etc/localtime && \
    dpkg-reconfigure -f noninteractive tzdata

# Install programs
RUN apt -y install golang-go
RUN apt -y intall micro
RUN apt -y install make
RUN apt -y install gccgo
RUN apt -y intall gcc  
COPY . /app
WORKDIR /app