#!/bin/bash

wp config create --dbname=wordpress --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --dbhost=mariadb --force

wp core install --url=hyuim.42.fr --title="Inception" --admin_user="root" --admin_password="$WP_ROOT_PASSWORD" --admin_email=asdf@naver.com

wp user create $WP_USER qwer@naver.com --user_pass="$WP_PASSWORD"

chown -R nobody:nobody /var/www/wordpress

php-fpm7 -F
