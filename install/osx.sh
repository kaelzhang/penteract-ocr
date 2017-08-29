#!/usr/bin/env bash

# Log <type> <msg>
log() {
  local label=$1
  shift
  printf "\x1B[36m>>> %s\x1B[0m :" $label
  printf " \x1B[90m$@\x1B[0m\n"
}

#
# Exit with the given <msg ...>
abort() {
  printf "\n\x1B[31mError: $@\x1B[0m\n\n"
  exit 1
}


log brew --version
brew --version || abort "brew is not installed"

log update brew
brew update || abort "fails to update brew"


# make sure a brew package is installed
make_sure_packge() {
  local package=$1

  if brew ls --versions "$package" > /dev/null; then
    log check "the version of $package"

    if brew outdated "$package" &> /dev/null; then
      log "$package" "is up to date"
    else
      log updating "$package"
      brew upgrade "$package"
    fi

  else
    log install "$package"
    brew install "$package" || abort "fails to install $package"
  fi
}


make_sure_packge pkg-config
make_sure_packge tesseract

log pkg-config --version
pkg-config --version || abort "pkg-config is not installed"

log tesseract --version
tesseract --version || abort "tesseract is not installed"


log npm "install -g node-gyp@latest"
npm install -g node-gyp@latest || abort "fails to install node-gyp"

log node-gyp --version
node-gyp --version || abort "node-gyp is not installed"
