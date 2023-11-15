# syntax=docker/dockerfile:1
FROM ubuntu
WORKDIR /code
RUN apt-get update
RUN apt-get install cmake -y
RUN apt-get install g++ -y
RUN apt-get install git -y
RUN apt-get install default-jre -y
RUN apt-get install curl -y
