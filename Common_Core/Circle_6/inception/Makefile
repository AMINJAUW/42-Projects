all : up

re : down up

up : 
	mkdir -p ~/data/mariadb
	mkdir -p ~/data/wordpress
	docker-compose -f ./srcs/docker-compose.yml build --no-cache
	docker-compose -f ./srcs/docker-compose.yml up

down : 
	docker-compose -f ./srcs/docker-compose.yml down -v
	rm -rf ~/data/*

stop : 
	docker-compose -f ./srcs/docker-compose.yml stop

start : 
	docker-compose -f ./srcs/docker-compose.yml start

status : 
	docker ps