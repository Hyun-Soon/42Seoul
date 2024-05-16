FROM alpine:3.18.6

RUN apk upgrade && apk add mariadb mariadb-client
RUN mariadb-install-db --user=root --datadir=/var/lib/mysql --skip-test-db
RUN mkdir /run/mysqld/
COPY tools/mariadb-init.sql tools/exec_mariadb.sh /etc/.

CMD ["sh", "/etc/exec_mariadb.sh"]
