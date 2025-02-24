#!/bin/bash

echo "CREATE DATABASE IF NOT EXISTS $SQL_DATABASE; " > /tmp/db1.sql
echo "CREATE USER IF NOT EXISTS '$SQL_USER'@'$MYSQL_HOST' IDENTIFIED BY '$SQL_PASSWORD';" >> /tmp/db1.sql
echo "GRANT ALL PRIVILEGES ON $SQL_DATABASE.* TO '$SQL_USER'@'%' IDENTIFIED BY '$SQL_PASSWORD';" >> /tmp/db1.sql
echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';" >> /tmp/db1.sql
echo "FLUSH PRIVILEGES;" >> /tmp/db1.sql
echo "SHOW GRANTS FOR '${SQL_USER}';" >> /tmp/db1.sql

mysqld_safe --init-file=/tmp/db1.sql
