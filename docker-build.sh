#!/usr/bin/env sh

#
# Part of the Conic project - robot arm controller
#
# Runs make in docker container. Useful for cross-compiling
# library to windows or building without native arm / avr toolchain
#
# See LICENSE.md for licensing information
# Roman Luitko, 2020
#

IMAGE_TAG=conic_docker_image
LOGNAME=$(logname)

check_image_exists() {
	docker image inspect $1 >/dev/null 2>&1
}

print_help() {
	echo "usage: $0 <make arguments>"
}

[ $# -lt 1 ] && print_help && exit 1
[ $(id -u) -ne 0 ] && echo "please, execute as root!" && exit 1

if ! check_image_exists $IMAGE_TAG; then
	echo "image $IMAGE_TAG is not exist, creating..."
	docker build -t $IMAGE_TAG scripts/
fi

echo "using username '$LOGNAME' to obtain uid and gid..."

docker run \
	--mount "type=bind,src=$(pwd),dst=/tmp/build" \
	--workdir /tmp/build \
	--user "$(id -u $LOGNAME):$(id -g $LOGNAME)" $IMAGE_TAG \
	make "$@"

