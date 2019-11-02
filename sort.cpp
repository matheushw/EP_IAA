/*
*    EP1 Introdução a Análise de Algoritmos
*    Aluno: Matheus Barcellos de Castro Cunha
*    N° USP: 11208238
*/

#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <dirent.h> 
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <unistd.h>
#include <chrono>
#define mtime std::chrono::high_resolution_clock::time_point

#define INF 1000000000

using namespace std;

vector <int> vectorzao;
long long int cont;

string merge_sort(vector<int> &v){
    if(v.size()==1) return "Vetor de tamanho 1";

    vector<int> u1, u2;

    for(int i=0;i<v.size()/2;i++) u1.push_back(v[i]);
    for(int i=v.size()/2;i<v.size();i++) u2.push_back(v[i]);

    merge_sort(u1);
    merge_sort(u2);

    u1.push_back(INF);
    u2.push_back(INF);

    int ini1=0, ini2=0;

    for(int i=0;i<v.size();i++){    
        if(u1[ini1]<u2[ini2]){
            v[i]=u1[ini1];
            ini1++;
        }

        else{
            v[i]=u2[ini2];
            ini2++;
        }
    }

    return "Sim";
}

int main (int argc, char **argv) {

    if (argc != 2) {
      cout<<("Digite o comando com nome da pasta onde se localizam os arquivos \".txt\" ex: \"./sort 1K\" \n");
      return 0;
   }

    DIR           *dirp;
    struct dirent *directory;

    dirp = opendir(argv[1]);
    if (dirp)
    {
        while ((directory = readdir(dirp)) != NULL)
        {
            cont = 0L;
            string s = directory->d_name;
            string file_name;

            if ((string)s != "." && (string)s != ".."){
                file_name = (string)argv[1]+ "/" + s;
                int sum = 0;
                int x;
                ifstream inFile;

                inFile.open(file_name);

                if (!inFile) {
                    cout << "Unable to open file";
                    continue;
                }

                bool firstline = false;

                int size = 0;

                mtime r_start = std::chrono::high_resolution_clock::now();

                while (inFile >> x) {
                    if (firstline == false) {
                        size = x;
                        firstline = true;
                    } else {
                        cont++;
                        vectorzao.push_back(x);
                    }
                }

                mtime r_end = std::chrono::high_resolution_clock::now();
                inFile.close();

                chrono::duration<int64_t, nano> dur_read = (r_end - r_start);
                int64_t r_time = dur_read.count();


                mtime s_start = std::chrono::high_resolution_clock::now();
                string orderd = merge_sort(vectorzao);
                mtime s_end = std::chrono::high_resolution_clock::now();

                chrono::duration<int64_t, nano> dur_sort = (s_end - s_start);
                int64_t s_time = dur_sort.count();

                cout<<"Nome do arquivo de entrada: "<<s<<" ||"
                <<" Tamanho do problema: "<<cont<<" ||"
                <<" Tempo de leitura: "<<r_time<<" ||"
                <<" Tempo de algoritmo: "<<s_time<<" ||"
                <<" Modelo do computador: MacBook Pro (13-inch, Mid 2012) ||"
                <<" Nome do algoritmo: Merge Sort ||"
                <<" Linguagem/Versão: C++ ||"
                <<" Sistema operacional: macOS High Sierra ||"
                <<" Largura de dados: 64 bits ||"
                <<" Arquivo ordenado: "<<orderd<<" ||"
                <<" N° USP: 11208238\n";
            }
        }
        closedir(dirp);
    }
}