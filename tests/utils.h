#include <iostream> // std::cout, std::endl
#include <fstream>  // std::ifstream
#include <cstdlib>  // std::exit
#include <iomanip>

void load_data(char *filename, float *&data, unsigned &num, unsigned &dim)
{ // load data with sift pattern
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << " for reading" << std::endl;
        exit(-1);
    }
    in.read((char *)&dim, 4);
    // std::cout << "data dimension: " << dim << std::endl;
    in.seekg(0, std::ios::end);
    std::ios::pos_type ss = in.tellg();
    size_t fsize = (size_t)ss;
    num = (size_t)(fsize / (dim + 1) / 4);
    data = new float[num * dim];

    in.seekg(0, std::ios::beg);
    for (size_t i = 0; i < num; i++)
    {
        in.seekg(4, std::ios::cur);
        in.read((char *)(data + i * dim), dim * 4);
    }
    in.close();
}

void save_result(char *filename, std::vector<std::vector<unsigned>> &results)
{
    std::ofstream out(filename, std::ios::binary | std::ios::out);
    if (!out.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        exit(-1);
    }
    for (unsigned i = 0; i < results.size(); i++)
    {
        unsigned GK = (unsigned)results[i].size();
        out.write((char *)&GK, sizeof(unsigned));
        out.write((char *)results[i].data(), GK * sizeof(unsigned));
    }
    out.close();
}

void print_csv_header() {
    std::cout << std::left;
    std::cout << std::setw(12) << "L" << ","
              << std::setw(12) << "time" << ","
              << std::setw(12) << "querynum" << ","
              << std::setw(12) << "qps" << ","
              << std::setw(12) << "recall"
              << std::endl;
}

void print_csv_row(unsigned L, double time, unsigned query_num, double qps, double recall) {
    std::cout << std::fixed << std::setprecision(6);
    std::cout << std::setw(12) << L << ","
              << std::setw(12) << time << ","
              << std::setw(12) << query_num << ","
              << std::setw(12) << qps << ","
              << std::setw(12) << recall
              << std::endl;
}