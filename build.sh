#!/bin/bash
#!/usr/bin/env bash
set -e
cmake -S . -B build-unix -G "Unix Makefiles"
cmake --build build-unix