#!/bin/sh
NAME=basetest_1.3
git archive --format=tar --prefix=$NAME/ HEAD | gzip >$NAME.tar.gz
