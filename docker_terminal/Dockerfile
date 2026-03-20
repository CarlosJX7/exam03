FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    zsh \
    sudo \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -M -d /home -s /bin/zsh carlos \
    && echo "carlos ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN mkdir -p /home/docker_terminal \
    && chown root:root /home/docker_terminal \
    && chmod 755 /home/docker_terminal

WORKDIR /home

CMD ["zsh"]
