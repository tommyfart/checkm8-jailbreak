#!/bin/sh

BOOTSTRAP_DIR="/bootstrap"
TARGET_DIR="/"

if [ "$(id -u)" -ne 0 ]; then
    echo "checkm8-jailbreak should be runned as root, exiting."
    exit 1
fi

echo "copying bootstrap files..."
cp -R $BOOTSTRAP_DIR/etc $TARGET_DIR
cp -R $BOOTSTRAP_DIR/usr $TARGET_DIR
cp -R $BOOTSTRAP_DIR/Library $TARGET_DIR
cp -R $BOOTSTRAP_DIR/var $TARGET_DIR

echo "Setting file permissions..."
chmod -R 755 /usr/bin
chmod -R 755 /usr/sbin
chmod -R 755 /Library/LaunchDaemons
chmod -R 700 /var/root
chmod -R 775 /var/mobile

echo "loading launch daemons..."
for plist in /Library/LaunchDaemons/*.plist; do
    launchctl load -w "${plist}"
done

echo "initializing dpkg..."
touch /var/lib/dpkg/status
mkdir -p /var/lib/dpkg/info

echo "bootstrap process complete! reboot recommended."

exit 0
