typedef struct visit{
	const char* key;
	size_t value;	
};

char* copy_str(char* str){
	size_t largo= strlen(str);
	char* str_aux= malloc(sizeof(char)* (largo+1));
	if(!str_aux){
		return NULL;
	}
	strcpy(str_aux,str);
	return str_aux;
}

visit_t* new_visit(const char* key, size_t value){
	visit_t* visit= malloc(sizeof(visit_t));
	if(!visit){
		return NULL;
	}
	const char* key_aux= copy_str(key);
	if(!key_aux){
		free(visit);
		return NULL;
	}
	visit->key= key; //copiar clave
	visit->value= value;
	return visit
}

visit_t* add_visit(hash_t* hash, hash_iter_t* iter){
	const char* key= hash_iter_ver_actual(iter);
	size_t value= hash_obtener(hash, key);
	visit_t* visit= new_visit(key, value);
	if(!visit){
		return NULL;
	}
	return visit;
}

int compare_visits(visit_t* visit1, visit_t* visit2){
    if (visit1->value == visit2->value) {
        return 0;
    }
    if (visit1->value < visit2->value) {
        return -1;
    }
return 1;

}
//la funcion de comparacion del heap se fija por cantidad de visitas

void most_visited(size_t n, hash_t* visited ){
	heap_t* n_visited= heap_crear(cmp);
	hash_iter_t iter= hash_iter_crear(visited);
	for (int i=0; i<n; i++){
		visit_t* visit= add_visit(visited,iter)//verificar que se crea
		heap_encolar(n_visited, visit);
		hash_iter_avanzar(iter);
	}

	while(!hash_iter_al_final(visited)){
		const char* key= hash_iter_ver_actual(iter);
		size_t value= hash_obtener(visited, key);

		if(heap_ver_min(n_visited)<value){
			heap_desencolar(n_visited);
			visit_t* visit= new_visit(key, value);//verificar que se crea
			heap_encolar(n_visited,visit);
			hash_iter_avanzar(iter);
		}
	}
	fprintf(stderr, "%s\n","Sitios más visitados:");
	//desencolar e imprimir

}

void find_attack(){
	hash_t* hash= hash_crear(destruir_dato);
	// chequear si se crea el hash?


}

time_t iso8601_to_time(const char* iso8601)
{
    struct tm bktime = { 0 };
    strptime(iso8601, TIME_FORMAT, &bktime);
    return mktime(&bktime);
}

int start(hash_t* visited) {
	hash_t* attack= hash_crear(destruir_dato);
    char *line = NULL;
    size_t length = 0;
    ssize_t read; //combo getline
    while ((read = getline(&line, &length, stdin)) > 0) {
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        char** splited= split(line);
        const char* ip= splited[0];
        time_t time= iso8601_to_time(splited[1]);
        const char* resourse= splited[3]; //numero magico


        if(hash_pertenece(visited,resourse)){
        	size_t visits= hash_obtener(visited,resourse);
        	visits++;
        }
        if(!hash_pertenece(visited,resourse)){
        	hash_guardar(visited, resourse, 1); //tipo
        }

        if(hash_pertenece(attack,ip)){
        	lista_t* times= hash_obtener(attack,ip);
        	lista_insertar_ultimo(times, time);
        }
        else{
        	lista_t* times= lista_crear();
        	lista_insertar_ultimo(times, time);
        	hash_guardar(attack, times);
        }

    }
    free(splited);
    free(line);
    return attack;
}