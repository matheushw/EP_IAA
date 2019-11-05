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

// #define INF 1000000000

using namespace std;

int arr[N];

int cont;

vector <int> vectorzao;

void swap(int* a, int* b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  
  
/* This function takes last element as pivot, places  
the pivot element at its correct position in sorted  
array, and places all smaller (smaller than pivot)  
to left of pivot and all greater elements to right  
of pivot */
int partition (int arr[], int low, int high)  
{  
    int pivot = arr[high]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
  
/* The main function that implements QuickSort  
arr[] --> Array to be sorted,  
low --> Starting index,  
high --> Ending index */
void quickSort(int arr[], int low, int high)  
{  
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}  

// string merge_sort(vector<int> &v){
//     if(v.size()==1) return "Vetor_de_tamanho_1";

//     vector<int> u1, u2;

//     for(int i=0;i<v.size()/2;i++) u1.push_back(v[i]);
//     for(int i=v.size()/2;i<v.size();i++) u2.push_back(v[i]);

//     merge_sort(u1);
//     merge_sort(u2);

//     u1.push_back(INF);
//     u2.push_back(INF);

//     int ini1=0, ini2=0;

//     for(int i=0;i<v.size();i++){    
//         if(u1[ini1]<u2[ini2]){
//             v[i]=u1[ini1];
//             ini1++;
//         }

//         else{
//             v[i]=u2[ini2];
//             ini2++;
//         }
//     }

//     return "Ordenado";
// }

int main (int argc, char **argv) {

    if (argc != 2) {
      cout<<("Digite o comando com nome da pasta onde se localizam os arquivos \".txt\" ex: \"./sort 1K\" \n");
      return 0;
   }

   srand(time(NULL)); 
  
    // to measure time taken by qsort and sort 
    clock_t begin, end; 
    double time_spent; 

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

                // mtime r_start = std::chrono::high_resolution_clock::now();

                while (inFile >> x) {
                    if (firstline == false) {
                        size = x;
                        firstline = true;
                    } else {
                        arr[cont] = x;
                        //vectorzao.push_back(x);
                        cont++;
                    }
                }

                // mtime r_end = std::chrono::high_resolution_clock::now();
                inFile.close();

                // chrono::duration<int64_t, nano> dur_read = (r_end - r_start);
                // int64_t r_time = dur_read.count();


                mtime s_start = std::chrono::high_resolution_clock::now();
                // string orderd = merge_sort(vectorzao);
                //sort (vectorzao.begin(), vectorzao.end());
                // sort (arr, arr+size);
                quickSort(arr,0,size-1);
                mtime s_end = std::chrono::high_resolution_clock::now();

                chrono::duration<int64_t, nano> dur_sort = (s_end - s_start);
                int64_t s_time = dur_sort.count();

                cout<<s<<" "
                <<vectorzao.size()<<" "
                <<"r_time"<<" "
                <<s_time<<" "
                <<"MacBookPro_(13-inch,Mid_2012) "
                <<"Merge Sort "
                <<"C++/g++7.4.0 "
                <<"macOS High Sierra "
                <<"64-bits "
                <<"orderd"<<" "
                <<"N° USP: 11208238\n";
                // vectorzao.clear();

                // for (int i = 0; i < N; i++){
                //     int b = rand()%100000;
                //     vectorzao.push_back(b); 
                // } 

                // begin = clock(); 
                // sort(vectorzao.begin(), vectorzao.end()); 
                // end = clock(); 
            
                // // calculate time taken by C++ sort 
                // time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 

                // cout<<"aaaaaaaaaaaaaaaaaaaaaa: "<<time_spent<<"\n";
                // vectorzao.clear();
            }
        }
        closedir(dirp);
    }
}