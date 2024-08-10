//
// Created by 付聪 on 2017/6/21.
//

#include <efanna2e/index_graph.h>
#include <efanna2e/index_random.h>
#include <efanna2e/util.h>
#include "utils.h"

int main(int argc, char** argv){
  if(argc!=8){std::cout<< argv[0] <<" data_file save_graph K L iter S R"<<std::endl; exit(-1);}
  float* data_load = NULL;
  unsigned points_num, dim;
  load_data(argv[1], data_load, points_num, dim);
  char* graph_filename = argv[2];
  unsigned K = (unsigned)atoi(argv[3]);
  unsigned L = (unsigned)atoi(argv[4]);
  unsigned iter = (unsigned)atoi(argv[5]);
  unsigned S = (unsigned)atoi(argv[6]);
  unsigned R = (unsigned)atoi(argv[7]);
  //data_load = efanna2e::data_align(data_load, points_num, dim);//one must align the data before build
  efanna2e::IndexRandom init_index(dim, points_num);
  efanna2e::IndexGraph index(dim, points_num, efanna2e::L2, (efanna2e::Index*)(&init_index));

  efanna2e::Parameters paras;
  paras.Set<unsigned>("K", K);
  paras.Set<unsigned>("L", L);
  paras.Set<unsigned>("iter", iter);
  paras.Set<unsigned>("S", S);
  paras.Set<unsigned>("R", R);

  auto s = std::chrono::high_resolution_clock::now();
  index.Build(points_num, data_load, paras);
  auto e = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = e-s;
  std::cout <<"Time cost: "<< diff.count() << "\n";

  index.Save(graph_filename);

  return 0;
}
