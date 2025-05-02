all: ts tc us uc

ts: tcp_server.c
	gcc $< -o $@

tc: tcp_client.c
	gcc $< -o $@

us: udp_server.c
	gcc $< -o $@

uc: udp_client.c
	gcc $< -o $@

clean:
	$(RM) ts tc us uc

