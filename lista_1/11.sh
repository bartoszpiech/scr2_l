#!/bin/sh

find /etc/ \( -size -1k -mtime -3d \) -o \( -size -250k -mtime +30d -mtime -90d \)
