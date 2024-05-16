FROM alpine:3.18.6

RUN apk add nginx
RUN apk add openssl
RUN mkdir ssl_files
RUN openssl req \
        -newkey rsa:2048 -nodes -keyout /ssl_files/my_ssl.key \
        -x509 -days 365 -out /ssl_files/my_ssl.crt \
        -subj "/C=KO/ST=Seoul/L=Gaepo/O=42Seoul/OU=hyuim/CN=hyuim.42.fr"

COPY ./conf/nginx.conf /etc/nginx/nginx.conf
COPY ./tools/exec_nginx.sh .

EXPOSE 443

CMD ["sh", "exec_nginx.sh"]

