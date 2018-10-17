FROM ubuntu:16.04

#Install dependencies
RUN dpkg --add-architecture i386 && \
    apt-get update && \
    apt-get -y install gcc-avr binutils-avr avr-libc gdb-avr avrdude make git
    
#Create and select workdir
RUN mkdir ttk4115_byggern
WORKDIR ttk4115_byggern 
