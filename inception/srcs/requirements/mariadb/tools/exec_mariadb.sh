sed -i "s/\$MYSQL_ROOT_PASSWORD/$MYSQL_ROOT_PASSWORD/" /etc/mariadb-init.sql
sed -i "s/\$MYSQL_USER/$MYSQL_USER/" /etc/mariadb-init.sql
sed -i "s/\$MYSQL_PASSWORD/$MYSQL_PASSWORD/" /etc/mariadb-init.sql

cat /etc/mariadb-init.sql > /dev/stderr

mysql_install_db --user=root --datadir=/var/lib/mysql

exec mariadbd --no-defaults --user=root --datadir=/var/lib/mysql --init-file=/etc/mariadb-init.sql
