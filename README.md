## Important!!1!
Rename your remote repo from **origin** to something else!
ANTLR4 also uses *origin* for it's repo and it otherwise causes errors. 

## Running Docker
Docker can be used to run the project on any machine having Docker.
To do it we need to build the container and run it in detached mode:
```bash
$ docker compose up --build -d
```
Then we need to connect to Docker:
```bash
$ docker compose run compiler
```

## Getting started
```bash
$ mkdir build
$ cd build
$ cmake ../
$ make
```
Default target is `driver`, it produces `driver` binary file in current (build) directory
