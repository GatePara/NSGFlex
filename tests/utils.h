#include <iostream> // std::cout, std::endl
#include <fstream>  // std::ifstream
#include <cstdlib>  // std::exit

void load_data(char *filename, float *&data, unsigned &num, unsigned &dim)
{ // load data with sift pattern
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << " for reading" << std::endl;
        exit(-1);
    }
    in.read((char *)&dim, 4);
    std::cout << "data dimension: " << dim << std::endl;
    in.seekg(0, std::ios::end);
    std::ios::pos_type ss = in.tellg();
    size_t fsize = (size_t)ss;
    num = (unsigned)(fsize / (dim + 1) / 4);
    data = new float[num * dim * sizeof(float)];

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