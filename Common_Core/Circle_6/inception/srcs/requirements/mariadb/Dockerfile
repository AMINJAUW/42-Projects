FROM debian:bullseye

RUN apt-get update -y

RUN apt-get install mariadb-server -y

COPY conf/50-server.cnf	/etc/mysql/mariadb.conf.d/

COPY conf/mysql_script.sh /tmp/mysql_script.sh

RUN chmod +x /tmp/mysql_script.sh
ENTRYPOINT	["/tmp/mysql_script.sh"]
