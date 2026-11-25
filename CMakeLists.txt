cmake_minimum_required(VERSION 3.20)
project(Tpsitt_Lab_26_27 C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(client1 Esercizi-named-pipe/Es1/client.c)
add_executable(server1 Esercizi-named-pipe/Es1/server.c)

add_executable(client2 Esercizi-named-pipe/Es2/client.c)
add_executable(server2 Esercizi-named-pipe/Es2/server.c)

add_executable(chat_a Esercizi-named-pipe/Es3/chat_a.c)
add_executable(chat_b Esercizi-named-pipe/Es3/chat_b.c)

add_executable(crea_fifo Esercizi-named-pipe/EsA/crea_fifo.c)

add_executable(reader Esercizi-named-pipe/EsB/reader.c)
add_executable(writer Esercizi-named-pipe/EsB/writer.c)

add_executable(ping Esercizi-named-pipe/EsC/ping.c)
add_executable(pong Esercizi-named-pipe/EsC/pong.c)     


add_executable(veicoli Funzioni-virtuali/Es1/veicoli.cpp)
add_executable(documento Funzioni-virtuali/Es2/documento.cpp)
add_executable(libro_paga Funzioni-virtuali/Es3/libro_paga.cpp)
add_executable(strumenti Funzioni-virtuali/Es4/strumenti.cpp)
add_executable(costr_distr Funzioni-virtuali/Es5/costr_distr.cpp)
add_executable(biblioteca Funzioni-virtuali/Es6/biblioteca.cpp)
add_executable(centralina Funzioni-virtuali/Es7/centralina.cpp)

add_executable(vf_es01 Esercizi-Verifica-Fork/es01_quanti_processi.c)
add_executable(vf_es02 Esercizi-Verifica-Fork/es02_memoria_separata.c)
add_executable(vf_es03 Esercizi-Verifica-Fork/es03_exit_status.c)
add_executable(vf_es04 Esercizi-Verifica-Fork/es04_ordine_terminazione.c)
add_executable(vf_es05 Esercizi-Verifica-Fork/es05_waitpid_wnohang.c)
add_executable(vf_es06 Esercizi-Verifica-Fork/es06_somma_parallela_pipe.c)
add_executable(vf_es07 Esercizi-Verifica-Fork/es07_buffer_printf.c)
add_executable(vf_es08 Esercizi-Verifica-Fork/es08_orfano_zombie.c)
add_executable(vf_es09 Esercizi-Verifica-Fork/es09_terminazione_segnale.c)
add_executable(vf_es10 Esercizi-Verifica-Fork/es10_simulazione_verifica.c)

add_executable(poli_veicoli Polimorfismo/Es1/veicoli.cpp)
add_executable(poli_personaggi Polimorfismo/Es2/personaggi.cpp)
add_executable(poli_pagamenti Polimorfismo/Es3/pagamenti.cpp)
add_executable(poli_notifiche Polimorfismo/Es4/notifiche.cpp)


add_executable(lezione_12_11 "Lezione 12-11/main.cpp")
