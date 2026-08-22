CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

build: processflow

processflow: main.c task.c
	$(CC) $(CFLAGS) main.c task.c -o processflow

run: processflow
	./processflow

clean:
	rm -f processflow

test: build
	@echo "Testando ProcessFlow "
	@printf "task listar /bin/ls -l\ntask pwd_teste /bin/pwd\nworkdir /tmp\nrun listar\nrun sequential listar pwd_teste\nrun parallel listar pwd_teste\nexit\n" | ./processflow
	@echo "Teste concluído"