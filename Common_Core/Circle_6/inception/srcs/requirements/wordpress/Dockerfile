FROM debian:bullseye

RUN apt update -y 

RUN apt install php7.4-fpm php7.4-mysql -y

RUN apt install curl -y


COPY ./conf/script.sh /
COPY ./conf/wp-config.php /wp-config.php

RUN chmod +x ./script.sh

ENTRYPOINT [ "./script.sh" ]