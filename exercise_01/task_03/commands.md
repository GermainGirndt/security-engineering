# Usefull Commands

```
ssh ggirndt@stl-s-stud.htwsaar.de

# After logging in the server as ggirndt@stl-s-stud.htwsaar.de:
ssh-keygen -t rsa -b 2048
ssh-copy-id ggirndt@isl-l-01.htwsaar.de
ssh 'ggirndt@isl-l-01.htwsaar.de'
```

### Note:

```
cat .ssh/authorized_keys
```

Has a line with the public key .ssh/id_rsa.pub in the client server
ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQC1YmOaevU7Iduv7ewagwiTc/pcU9ucgIHAN4J2h30hrPz+p7FRcSfH2ZQmfv3tKEBDU9MeDcl8JGw612vIbx9oF30lCIfj6Rb+MwTrFFmy65KwlL7TcOYq6Z4lYgJ6aLfZ/+7LOHcAe9jwm3gd0qIFqjlgu9iZ+09FNv9BNj8ult0GotfkZm21Bhp2SQ4mAZYCEkxdR1ujL/QYYYYa8whvveVRSmiz5iYkkL0zRAckJO2Dc+XrpZZ7+DGm3smTglPEfbhpnzxHrmxGLE+VMlCohwQfMgnZKxlcPQtMAeaBkM2pqLYuG/LG7N1ZIKRpjeCqxPnfksPw/fC2EnCAeSVv ggirndt@stl-s-stud-neu.htw-saarland.de
