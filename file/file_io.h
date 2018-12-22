#ifndef FILE_IO_H
#define FILE_IO_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>

extern std::string FILEPATH;

class file_io
{
public:
    file_io();
    template <class T> static std::vector<T> load_from_disk(std::string file);
    template <class T> static void save_data_to_disk(std::string file, std::vector<T> data);
};


template <class T> std::vector<T> file_io::load_from_disk(std::string file)
{
    std::string filename = std::string(FILEPATH) + "/" + file;
    std::vector<T> res;
    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp) {
        std::cout << ">>file_io::load_from_disk - file '" << filename << "' not found." << std::endl;
        return res;
    }

    int n = 0;
    while (!feof(fp) && !ferror(fp)) {
        T out;
        int res_read = fread(&out, sizeof(T), 1, fp);


        //std::cout << ">>file_io::load_from_disk - res_read '" << res_read << "'." << std::endl;
        if (res_read == -1) {
            std::cout << ">>file_io::load_from_disk - Error reading data from scenes_list file '" << filename << "'." << std::endl;
            fclose(fp);
            //exception_manager::throw_general_exception(std::string("fio_common::load_from_disk - Error reading data from file."), filename);
        } else if (res_read == 1) {
            res.push_back(out);
        }

        n++;
    }
    fclose(fp);
    return res;
}

template <class T> void file_io::save_data_to_disk(std::string file, std::vector<T> data)
{
    std::string filename = std::string(FILEPATH) + "/" + file;
    //std::cout << ">> file_io::save_data_to_disk - filename: '" << filename << "'." << std::endl;
    FILE *fp = fopen(filename.c_str(), "wb");
    if (!fp) {
        std::cout << ">> file_io::save_data_to_disk - file '" << filename << "' not found." << std::endl;
        return;
    }

    //std::cout << ">>file_io::save_data_to_disk - size: " << data.size() << std::endl;

    for (unsigned int i=0; i<data.size(); i++) {
        int block_size = sizeof(T);
        T data_in = data.at(i);
        fwrite(&data_in, block_size, 1, fp);
    }
    fclose(fp);
}

#endif // FILE_IO_H
