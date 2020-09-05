#!/bin/sh

avrdude -c usbasp -p attiny45 -v -U lfuse:w:0xE2:m
