
void MQLoadGame(DATA *data)
{
    FILE *file;
    file = fopen("data/save/savegame", "r+b");
    fread(&data->game, sizeof(struct DATA_GAME), 1, file);
    fclose(file);
}

void MQSaveGame(DATA data)
{
    remove("data/save/savegame");
    FILE *file = fopen("data/save/savegame", "w+b");
    fwrite(&data.game, sizeof(struct DATA_GAME), 1, file);
    fclose(file);
}
