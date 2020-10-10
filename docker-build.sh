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

info() {
	printf "[info]\t%s\n" "$1"
}

print_usage() {
	info "usage $0 [target: dll | so | firmware]"
	exit 1
}

check_image_exists() {
	docker image inspect $1 >/dev/null 2>&1
}

build() {
	if ! check_image_exists $IMAGE_TAG; then
		info "image $IMAGE_TAG is not exists, creating..."
		docker build -t $IMAGE_TAG scripts/
	fi

	info "using username '$LOGNAME' to obtain uid and gid..."

	case $1 in
	dll)
		info "building windows dll..."
		docker run \
			--mount "type=bind,src=$(pwd),dst=/tmp/build" \
			--env "BOARD=stm32_demo" \
			--env "HOSTCC=x86_64-w64-mingw32-gcc" \
			--env "HOSTLD=x86_64-w64-mingw32-gcc" \
			--workdir /tmp/build \
			--user "$(id -u $LOGNAME):$(id -g $LOGNAME)" \
			$IMAGE_TAG library
		;;
	so)
		info "building linux dl is not supported for now"
		;;
	firmware)
		info "building firmware is not supported for now"
		;;
	*)
		print_usage
		;;
	esac
}

[ $# -ne 1 ] && print_usage
[ $(id -u) -ne 0 ] && info "please, execute as root!" && exit 1 
build $1

