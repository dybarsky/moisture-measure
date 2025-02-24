# Created at: 24.02.2025
# Created by: Maksym Dybarskyi

# === Base image ===
FROM ubuntu:24.04 AS base
# Install dependencies
RUN apt-get update
RUN apt-get install -y bzip2 unzip curl tree make
# Install msp430 toolchain
RUN mkdir /msp430tools
RUN curl --output /msp430tools/msp430gcc.tar.bz2 https://dr-download.ti.com/software-development/ide-configuration-compiler-or-debugger/MD-LlCjWuAbzH/9.3.1.2/msp430-gcc-9.3.1.11_linux64.tar.bz2
RUN curl --output /msp430tools/support-files.zip https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/9_3_1_2/export/msp430-gcc-support-files-1.212.zip
RUN tar xvf /msp430tools/msp430gcc.tar.bz2 -C /msp430tools/
RUN unzip /msp430tools/support-files.zip -d /msp430tools/
ENV GCC_HOME=/msp430tools/msp430-gcc-9.3.1.11_linux64
RUN mv /msp430tools/msp430-gcc-support-files/include/*.h $GCC_HOME/msp430-elf/include/
RUN mv /msp430tools/msp430-gcc-support-files/include/*.ld $GCC_HOME/msp430-elf/lib/
RUN ln -s $GCC_HOME/bin/msp430-elf-gcc /usr/bin/msp430-gcc
ENV PATH="$PATH:$GCC_HOME/bin"
# Setup workdir
RUN mkdir /firmware
WORKDIR /firmware
# Setup machine
RUN useradd -m user
RUN chown user /firmware
RUN chmod u+rw /firmware
USER user

# === Buidler image ===
FROM base AS builder
# Add source files
COPY --chown=user src src
COPY --chown=user Makefile Makefile
# Print workdir
RUN tree --dirsfirst
# Build firmware
ENTRYPOINT ["make", "clean", "build"]