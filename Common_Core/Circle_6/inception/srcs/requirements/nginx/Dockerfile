FROM debian:bullseye

RUN apt-get update -y
RUN apt-get upgrade -y

RUN apt-get install nginx -y

RUN apt-get install openssl -y

#Create certificate selfsigned(x509) with private key not cripted (nodes) fill with the info (-subj)
RUN openssl req -x509 -nodes \
    -out /etc/ssl/certs/nginx-selfsigned.crt \
    -keyout /etc/ssl/private/nginx-selfsigned.key\
    -subj "/C=BE/ST=BXL/L=BXL/O=19/OU=student/CN=aminjauw.s19.be/UID=aminjauw" 

#Add Configuration file
COPY conf/conf.conf /etc/nginx/conf.d/nginx.conf

RUN chmod 755 /var/www/html
RUN chown -R www-data:www-data /var/www/html

ENTRYPOINT [ "nginx", "-g", "daemon off;" ]