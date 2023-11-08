#!/usr/bin/env bash

# This script may be used to repackage our Libpl debian package for older debian distributions
# that don't support the dpkg-deb archiving algorithm.

progname="$(basename $0)"

set -o pipefail -o nounset

usage() {
    cat <<EOF
Usage: $progname [OPTIONS] PACKAGE

This script may be used to repackage our Libpl debian package for older debian
distributions that don't support the dpkg-deb archiving algorithm.

Options:
  -h   Show this message and exit.
EOF

    exit 1
}

_error() {
    local msg="$@"

    >&2 echo "$progname: error: $msg" && exit 1
}

_warn() {
    local msg="$@"

    >&2 echo "$progname: warning: $msg"

    return 0
}

_info() {
    local msg="$@"

    echo "$progname: info: $msg"

    return 0
}

repackage() {
    local pkg="$1"
    
    ar x $pkg
    zstd -d < control.tar.zst | xz > control.tar.xz
    zstd -d < data.tar.zst | xz > data.tar.xz
    ar -m -c -a sdsd ${pkg}_repacked.deb debian-binary control.tar.xz data.tar.xz

    ls -l

    rm debian-binary control.tar.xz data.tar.xz control.tar.zst data.tar.zst

    return 0
}

# --- main() ----

while getopts "h" opt ; do
    case $opt in
        h) usage ;;
        *) usage ;;
    esac
done

shift $((OPTIND - 1))

[[ $# == 1 ]] || _error "improper positional arguments: $@"

package="$1"

repackage $package

exit 0

# -*- mode: shell-script; sh-shell: bash -*-
