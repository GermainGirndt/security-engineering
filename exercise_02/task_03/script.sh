make
./print_file_info /dev/random /bin/sh /usr/bin/tar /var/spool /etc/services /tmp/.X11-unix/X0 > output-c.txt 2>&1
stat -x /dev/random /bin/sh /usr/bin/tar /var/spool /etc/services /tmp/.X11-unix/X0 > output-stat.txt 2>&1

make clean


