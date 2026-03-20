#!/bin/bash

# Fix permissions for user carlos
# This script resolves the "mkdir: cannot create directory '/home/carlos/.cache': Permission denied"
# error that occurs when carlos opens a new zsh session.

set -e

USER_NAME="carlos"
HOME_DIR="/home/${USER_NAME}"

# Create the user if it doesn't exist
if ! id "${USER_NAME}" &>/dev/null; then
    echo "Creating user ${USER_NAME}..."
    useradd -m -s /bin/zsh "${USER_NAME}"
fi

# Ensure the home directory exists
if [ ! -d "${HOME_DIR}" ]; then
    echo "Creating home directory ${HOME_DIR}..."
    mkdir -p "${HOME_DIR}"
fi

# Fix ownership and permissions so carlos can write to their home directory
echo "Fixing ownership and permissions for ${HOME_DIR}..."
chown -R "${USER_NAME}:${USER_NAME}" "${HOME_DIR}"
chmod 700 "${HOME_DIR}"

echo "Done. User ${USER_NAME} can now write to ${HOME_DIR}."
