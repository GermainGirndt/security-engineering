### Verifing Hashes

openssl sha256 /etc/services
openssl sha1 /etc/services  
openssl sha384 /etc/services
openssl md5 /etc/services   


### Copying and checking permissions
cp /etc/services ./services_copy
ls -la services_copy 
chmod +x services_copy
ls -la services_copy 

### Adding line
echo "...line added..." >> ./services_copy  ## or open in nano and delete something

### Verifing new hash

openssl sha256 ./services_copy
openssl sha1 ./services_copy  
openssl sha384 ./services_copy
openssl md5 ./services_copy   #

### Expected output on my Mac:

#SHA256(/etc/services)= 69c6cb3537f270d9b23f77ebdec01dda91770c05e59b77cf9c4ce4b82058ab38
#SHA1(/etc/services)= 117164139ff5c7a63135ede4dc124627c98cc857
#SHA384(/etc/services)= 86140af4d74aa51ca05aff5f5b5039fe6e98c3be9f31f7b5503ef8f0f94c7f1b0e57b746058535a43b1bb3ff2607e3d0
#MD5(/etc/services)= 31f22ffc03b31343d9e756ea7284a8f6

#-rw-r--r--  1 germaingirndt  staff  677977 Apr 23 16:11 services_copy
#-rwxr-xr-x  1 germaingirndt  staff  677977 Apr 23 16:11 services_copy

#SHA256(./services_copy)= b9002672d66ab9071cb50abaa8b181f6751639e8a96312b59926916393e9db33
#SHA1(./services_copy)= c62b5c31e2d1c33945266458c03c9ae67042d325
#SHA384(./services_copy)= 7274b7ed1fedaded5602e0ce9c330e7b84f5cbfb0338e4977d67af8a6205aaab4a5b05ce13d223ac1ee9dcc25c0db67d
#MD5(./services_copy)= 53415cec68422039c987efd1011f9755