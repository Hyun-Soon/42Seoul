up : 
	mkdir -p /home/hyuim/data/DB
	mkdir -p /home/hyuim/data/phps
	docker compose -f ./srcs/docker-compose.yml up -d

down :
	docker compose -f ./srcs/docker-compose.yml down

cleanNet :
	docker network rm inception

cleanVol :
	docker volume rm db_volume
	rm -rf /home/hyuim/data/DB
	docker volume rm web_volume
	rm -rf /home/hyuim/data/phps

re : down up


.PHONY : up down net cleanNet cleanVol re
