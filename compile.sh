#!/bin/bash
gcc -Wall com.c rcv_mdd.c env_mdd.c main.c tache_ap.c tache_bp.c tache_a.c tache_b.c -lpthread -o main
