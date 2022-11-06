// Image Handling with SOA implementation
#include "../common/progargs.hpp"
#include "../soa/imagesoa.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cmath>

using namespace std;

void push_color(colors &clrs, vector <unsigned char> &color_bytes, int val){
    clrs.b.push_back(color_bytes[val]);  
    clrs.g.push_back(color_bytes[val+1]);
    clrs.r.push_back(color_bytes[val+2]);  
}


int read(string file_name, colors &clrs){
    auto load_start = chrono::high_resolution_clock::now(); 
    int start, width, height, padding;
    get_dimensions(file_name, start, width, height);
    padding = (4 - (width * 3) % 4) % 4;
    int size_arr = height*((3*width)+padding);
    vector <uint8_t> color_bytes(size_arr); 
    FILE *fp = fopen(file_name.c_str(), "rb");
    fseek(fp, start, SEEK_SET);
    fread(static_cast<void*>(&color_bytes[0]), 1, size_arr, fp);
    fclose(fp);
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++)  
            push_color(clrs, color_bytes, y*((3*width)+padding) + 3*x);
    }
    auto load_stop = chrono::high_resolution_clock::now(); 
    auto load_t = duration_cast<chrono::microseconds>(load_stop - load_start);
    return static_cast<int>(load_t.count());
}


void write(string file_name, string src, string dst, colors &clrs){
    unsigned char header[58];                                   
    int start, width, height, padding;
    ofstream file_path(dst + "/" + file_name.substr(src.size(),file_name.size()));
    FILE *fp = fopen(file_name.c_str(), "rb");
    fread(header, sizeof(header), 1, fp);
    fclose(fp);
    get_dimensions(file_name, start, width, height); 
    padding = (4 - (width * 3) % 4) % 4;
    for(int h = 0; h < 58; h++)
        file_path << header[h];
    for(int i = 0; i < start - 58; i++)
        file_path << static_cast<char>(0x00);
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++)
            file_path << clrs.b[y*width + x] << clrs.g[y*width + x] << clrs.r[y*width + x];
        for(int i = 0; i < padding; i++)    
            file_path << static_cast<char>(0x00);
    }
    file_path.close();
}


int copy(string file_name, string src, string dst, colors &clrs){
    auto write_start = chrono::high_resolution_clock::now(); 
    write(file_name, src, dst, clrs);
    auto write_stop = chrono::high_resolution_clock::now(); 
    auto write_t = duration_cast<chrono::microseconds>(write_stop - write_start);
    return static_cast<int>(write_t.count());
}


void main_copy(string file_name, string src, string dst, colors &clrs){
    int read_t = read(file_name,clrs);
    auto oper_start = chrono::high_resolution_clock::now();
    int  write_t = copy(file_name, src, dst, clrs);
    auto oper_stop = chrono::high_resolution_clock::now();
    auto oper = duration_cast<chrono::microseconds>(oper_stop - oper_start);
    int oper_and_write_t = static_cast<int>(oper.count());
    int oper_t = oper_and_write_t - write_t;
    int total_t = oper_and_write_t + read_t;
    cout << "File: " << src << "/" << file_name << "(time: " << total_t << ")\n";
    cout << "\tLoad Time: " << read_t << endl;
    cout << "\tCopy Time: " << oper_t << endl;
    cout << "\tStore Time: " << write_t << endl;
}


void gauss_helper(colors &cls, colors &blur_img, int width, int height){
    int m[5][5] = {{1,4,7,4,1}, {4,16,26,16,4}, {7,26,41,26,7}, {4,16,26,16,4}, {1,4,7,4,1}};
    for(int y = 2; y < height-2; y++){
        for(int x = 2; x < width-2; x++){
            long sum_b = 0, sum_g = 0, sum_r = 0;
            for(int s = -3; s < 2; s++){
                for(int t = -3; t < 2; t++){
                    sum_b += m[s+3][t+3]*static_cast<int>(cls.b[(y+1+s)*width + x+1+t]);
                    sum_g += m[s+3][t+3]*static_cast<int>(cls.g[(y+1+s)*width + x+1+t]);
                    sum_r += m[s+3][t+3]*static_cast<int>(cls.r[(y+1+s)*width + x+1+t]);
                }
            }
            blur_img.b.push_back(sum_b/273);
            blur_img.g.push_back(sum_g/273);
            blur_img.r.push_back(sum_r/273);
        }
    }
}   


void gauss_add_border(colors &clrs, int size){
    clrs.b.resize(size,0x00);
    clrs.g.resize(size,0x00);
    clrs.r.resize(size,0x00);
}


int gauss_read(string file_name, colors &clrs){
    auto load_start = chrono::high_resolution_clock::now(); 
    int start, width, height, padding;
    get_dimensions(file_name, start, width, height);
    padding = (4 - (width * 3) % 4) % 4;
    int size_arr = height*((3*width)+padding);
    vector <unsigned char> color_bytes(size_arr); 
    FILE *fp = fopen(file_name.c_str(), "rb");
    fseek(fp, start, SEEK_SET);
    fread(static_cast<void*>(&color_bytes[0]), 1, size_arr, fp);
    fclose(fp);                                     
    gauss_add_border(clrs,2*(width+4));
    for(int y = 0; y < height; y++){
        gauss_add_border(clrs, clrs.b.size() + 2);              // left border
        for(int x = 0; x < width; x++){             
            push_color(clrs, color_bytes, y*((3*width)+padding) + 3*x);          
        }
        gauss_add_border(clrs, clrs.b.size() + 2);  
    }
    gauss_add_border(clrs, clrs.b.size() + (2*(width+4)));
    auto load_stop = chrono::high_resolution_clock::now(); 
    auto load_t = duration_cast<chrono::microseconds>(load_stop - load_start);
    return static_cast<int>(load_t.count());
}


int gauss(string file_name, string src, string dst, colors &clrs){
    int start, width, height;
    get_dimensions(file_name, start, width, height);                                   
    colors blur_img;
    gauss_helper(clrs, blur_img, width+4, height+4);
    auto write_start = chrono::high_resolution_clock::now(); 
    write(file_name, src, dst, blur_img);
    auto write_stop = chrono::high_resolution_clock::now(); 
    auto write_t = duration_cast<chrono::microseconds>(write_stop - write_start);
    return static_cast<int>(write_t.count());
}


void main_gauss(string file_name, string src, string dst, colors &clrs){
    int read_t = gauss_read(file_name,clrs);
    auto oper_start = chrono::high_resolution_clock::now();
    int  write_t = gauss(file_name, src, dst, clrs);
    auto oper_stop = chrono::high_resolution_clock::now();
    auto oper = duration_cast<chrono::microseconds>(oper_stop - oper_start);
    int oper_and_write_t = static_cast<int>(oper.count());
    int oper_t = oper_and_write_t - write_t;
    int total_t = oper_and_write_t + read_t;
    cout << "File: " << src << "/" << file_name << "(time: " << total_t << ")\n";
    cout << "\tLoad Time: " << read_t << endl;
    cout << "\tGauss Time: " << oper_t << endl;
    cout << "\tStore Time: " << write_t << endl;
}


void mono_helper(colors &mono_clr,  int val){
    double norm[3], g;
    norm[0] = mono_clr.b[val] / 255.0;
    norm[1] = mono_clr.g[val] / 255.0;
    norm[2] = mono_clr.r[val] / 255.0;
    for(int i = 0; i < 3; i++){
        if (norm[i] > 0.04045) {norm[i] = pow((norm[i] + 0.055)/(1.055),2.4);}
        else {norm[i] = norm[i] / 12.92;}
        }
    g = (0.2126 * norm[2] + 0.7152 * norm[1] + 0.0722 * norm[0]);
    if (g <= 0.0031308) g = 12.92 * g;
    else g = (1.055*pow(g,(1.0/2.4)))-0.055;
    g = floor(g * 255);
    mono_clr.b[val] = mono_clr.g[val] = mono_clr.r[val] = g;
}


int mono(string file_name, string src, string dst, colors &clrs){
    int start, width, height;
    get_dimensions(file_name, start, width, height);
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++)
            mono_helper(clrs, y*width + x);
    }
    auto write_start = chrono::high_resolution_clock::now(); 
    write(file_name, src, dst, clrs);
    auto write_stop = chrono::high_resolution_clock::now(); 
    auto write_t = duration_cast<chrono::microseconds>(write_stop - write_start);
    return static_cast<int>(write_t.count());
}


void main_mono(string file_name, string src, string dst, colors &clrs){
    int read_t = read(file_name,clrs);
    auto oper_start = chrono::high_resolution_clock::now();
    int  write_t = mono(file_name, src, dst, clrs);
    auto oper_stop = chrono::high_resolution_clock::now();
    auto oper = duration_cast<chrono::microseconds>(oper_stop - oper_start);
    int oper_and_write_t = static_cast<int>(oper.count());
    int oper_t = oper_and_write_t - write_t;
    int total_t = oper_and_write_t + read_t;
    cout << "File: " << src << "/" << file_name << "(time: " << total_t << ")\n";
    cout << "\tLoad Time: " << read_t << endl;
    cout << "\tMono Time: " << oper_t << endl;
    cout << "\tStore Time: " << write_t << endl;
}
