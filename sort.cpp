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
#include <algorithm>
#define mtime std::chrono::high_resolution_clock::time_point
#define N 100000010

using namespace std;

int arr[N];

int cont;

vector <int> vectorzao;

void swap(int* a, int* b) {  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  

int partition (int arr[], int low, int high) {  
    int pivot = arr[high];
    int i = (low - 1);
  
    for (int j = low; j <= high - 1; j++) {  
    
        if (arr[j] < pivot) {  
            i++;
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  

void quickSort(int arr[], int low, int high)  
{  
    if (low < high) {  
        int pi = partition(arr, low, high);  

        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
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
            string s = directory->d_name;
            string file_name;

            if ((string)s != "." && (string)s != ".."){
                cont = 0;
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
                        arr[cont] = x;
                        cont++;
                    }
                }

                mtime r_end = std::chrono::high_resolution_clock::now();
                inFile.close();
                chrono::duration<int64_t, nano> dur_read = (r_end - r_start);
                int64_t r_time = dur_read.count();


                mtime s_start = std::chrono::high_resolution_clock::now();
                quickSort(arr,0,size-1);
                mtime s_end = std::chrono::high_resolution_clock::now();

                chrono::duration<int64_t, nano> dur_sort = (s_end - s_start);
                int64_t s_time = dur_sort.count();

                cout<<s<<" "
                <<size<<" "
                <<r_time<<" "
                <<s_time<<" "
                <<"MacBookPro(13-inch,Mid_2012) "
                <<"Quick_Sort "
                <<"C++/g++7.4.0 "
                <<"macOS_High_Sierra "
                <<"64 "
                <<"Orderd"<<" "
                <<"11208238\n";
            }
        }
        closedir(dirp);
    }
}