#include <iostream>
#include<fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <map>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_2.h>
#include <fstream>


using namespace std;

#define SIZE 1000

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_2<K>      Triangulation;
typedef Triangulation::Vertex_handle  Vertex_handle;
typedef Triangulation::Point          Point;
typedef Triangulation::Finite_vertex_handles   Finite_vertex_handles;
typedef Triangulation::Finite_vertices_iterator Finite_vertices_iterator;
typedef Finite_vertex_handles::iterator         Finite_vertex_handles_iterator;


struct pixel_hydro
{
    int x;
    int y;
    long double z;
};

void read_file(string filename, Triangulation* t, vector<vector<long double>>* data, double* zoom, map<Point, double long>* depth);
void write_ppm(string filename);
void add_pixel_ppm(string filename, pixel_hydro p);


int main() 
{

    Triangulation t;
    vector<vector<long double>> data;
    map<Point, double long> depth;

    double zoom = 1;

    read_file("rade_1m_IM.txt", &t, &data, &zoom, &depth);

    ofstream f("map.ppm", ios::out | ios::binary);

    if(!f.is_open())
    {
        cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
    }
    else
    {
        f.write("P6\n", 3);
        f.write("1000", 4);
        f.write(" ", 1);
        f.write("1000", 4);
        f.write("\n", 1);
        f.write("255\n", 4);

        for(int i = 0; i < SIZE; i++)
        {
            for(int j=0; j < SIZE; j++)
            {
                Triangulation::Face_handle face = t.locate(Point(i*zoom, j*zoom));
                long double z = 0;
                for(Finite_vertices_iterator it = t.finite_vertices_begin(); it != t.finite_vertices_end(); ++it)
                {
                    //std::cout << it->point() << std::endl;
                }
                
                char r = i%254;
                char g = j%254;
                char b = 0;
                f.write((char*)&r, sizeof(char));
                f.write((char*)&g, sizeof(char));
                f.write((char*)&b, sizeof(char));
            }

        }

   
        
    }

    f.close();


    return EXIT_SUCCESS;
}

void read_file(string filename, Triangulation* t, vector<vector<long double>>* data, double* zoom, map<Point, double long>* depth)
{
    string line;
    ifstream myfile(filename);

    if (myfile.is_open())
    {
        int i = 0;
        vector<long double> coords(3);
        long double x = 0;
        long double y = 0;
        long double z = 0;

        long double x_max = -1000000;
        long double x_min = 1000000;
        long double y_max = -100000;
        long double y_min = 1000000;
        long double z_max = -1000000;
        long double z_min = 1000000;

        vector<Point> data_t;
        


        while ( getline(myfile,line) )
        {

            istringstream iss(line); 
            string donnee; 
            getline(iss, donnee, ' ');
            x = stold(donnee);
            if (x > x_max){x_max = x;}
            else if (x < x_min){x_min = x;}

            getline(iss, donnee, ' ' );
            y = stold(donnee);
            if (y > y_max){y_max = y;}
            else if (y < y_min){y_min = y;}

            getline(iss, donnee, ' ' );
            z = stold(donnee);
            if (z > z_max){z_max = z;}
            else if (z < z_min){z_min = z;}
        
            data_t.push_back(Point(x, y));
            depth->insert(pair<Point, double long>(Point(x, y), z));

            coords[0] = x;
            coords[1] = y;
            coords[2] = z;
            data->push_back(coords);


            i++;

        }


        t->insert(data_t.begin(), data_t.end());

        *zoom = max((x_max - x_min), (y_max - y_min))/SIZE;

        cout << "Fichier lu : " << i << " lignes, x -> (" << x_min << ";" << x_max << ") y -> (" << y_min << ";" << y_max << ") z -> (" << z_min << ";" << z_max << ") Zoom : " << *zoom << endl;

        myfile.close();
    }
   

    else cout << "Unable to open file"; 
}


void add_pixel_ppm(string filename, pixel_hydro p)
{

}

void write_ppm(string filename)
{
    ofstream f(filename, ios::out | ios::binary);

    if(!f.is_open())
    {
        cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
    }
    else
    {
        f.write("P6\n", 3);
        f.write("2", 1);
        f.write(" ", 1);
        f.write("2", 1);
        f.write("\n", 1);
        f.write("255\n", 4);

        char r = 0;
        char g = 0;
        char b = 255;
        f.write((char*)&r, sizeof(char));
        f.write((char*)&g, sizeof(char));
        f.write((char*)&b, sizeof(char));
        
    }

    f.close();

}