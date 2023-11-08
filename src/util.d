module util;

import std.stdio;
import std.file;
import std.string;
import std.conv;

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
