### Execute

```
make
./print_file_info /dev/random /bin/sh /usr/bin/tar /var/spool /etc/services /tmp/.X11-unix/X0
```

### Clean the build artifacts:

```
make clean
```

### Note

The code behaviours similarly as the stat command:

```
stat -x /dev/random /bin/sh /usr/bin/tar /var/spool /etc/services /tmp/.X11-unix/X0 > output-stat.txt 2>&1
```
