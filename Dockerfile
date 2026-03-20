FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    zsh \
    git \
    && rm -rf /var/lib/apt/lists/*

# Create user carlos with a proper home directory and zsh as login shell
RUN useradd -m -s /bin/zsh carlos

# Ensure carlos owns their home directory so zsh can create ~/.cache and other dirs
RUN chown -R carlos:carlos /home/carlos && chmod 700 /home/carlos

USER carlos

WORKDIR /home/carlos

CMD ["zsh"]
