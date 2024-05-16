FROM alpine:3.18.6

RUN echo "http://dl-cdn.alpinelinux.org/alpine/v3.13/community" >> /etc/apk/repositories
RUN apk update && apk upgrade
RUN apk add dumb-init fcgi curl php7 php7-fpm php7 php7-fpm php7-opcache php7-gd php7-mysqli php7-zlib php7-curl php7-phar php7-json php7-mbstring

COPY conf/www.conf /etc/php7/php-fpm.d/www.conf
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
	chmod +x wp-cli.phar && \
	mv wp-cli.phar /usr/local/bin/wp
RUN mkdir -p /var/www/wordpress
WORKDIR /var/www/wordpress
RUN wp core download --path="/var/www/wordpress"

COPY ./tools/exec_php-fpm.sh /etc/.
CMD ["sh", "/etc/exec_php-fpm.sh"]
