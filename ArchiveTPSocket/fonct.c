
char * get_mot(const char * name){
  FILE *file;
  int numero_ligne;
  int numero_ligne_max;
  int i=0;
  char *mot;

  file = fopen(name,"r");
  fscanf(file, "%d", &numero_ligne_max);
  numero_ligne = rand() % numero_ligne_max;

  while (fscanf(file, "%s",mot) != EOF && i<numero_ligne_max){
    i++;
  }
    fclose(file);
    return mot;
}
