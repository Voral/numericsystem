#!/bin/sh
NAME=basetest_1.1
git archive --format=tar --prefix=$NAME/ HEAD | gzip >$NAME.tar.gz
