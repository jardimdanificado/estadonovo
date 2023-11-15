module util;

import std.stdio;
import std.file;
import std.string;
import std.conv;

import raylib;


float deg2rad(float deg)
{
    return (deg * PI / 180);
}

string readTxt(string filePath) 
{
    try 
    {
        // Use a função std.file.read para ler o conteúdo do arquivo
        string fileContent = cast(string)std.file.read(filePath);
        return fileContent;
    } 
    catch (FileException e) 
    {
        // Trate qualquer exceção que possa ocorrer durante a leitura do arquivo
        // Por exemplo, você pode imprimir uma mensagem de erro
        writeln("Erro ao ler o arquivo: ", e.msg);
        return "";  // Retorna uma string vazia em caso de erro
    }
}

Model[] bulkLoadModel(string filePath, int length, string extension = ".obj")
{
    Model[] models;
    for (int i = 0; i < length; i++)
    {
        string path = filePath ~ to!string(i) ~ extension;
        Model model = LoadModel(path.toStringz());
        models ~= model;
    }
    return models;
}

BoundingBox[] bulkLoadHitbox(string filePath, int length, string extension = ".obj")
{
    BoundingBox[] hitboxes;
    for (int i = 0; i < length; i++)
    {
        string path = filePath ~ to!string(i) ~ extension;
        BoundingBox hb = GetModelBoundingBox(LoadModel(path.toStringz()));
        hitboxes ~= hb;
    }
    return hitboxes;
}