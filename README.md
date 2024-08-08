# NSGFlex: Navigating Spread-out Graph for Approximate Nearest Neighbor Search with Enhanced Flexibility

Table of Contents
=================
<!--ts-->
* [Introduction](#introduction)
* [Building Instruction](#building-instruction)
     * [Prerequisites](#prerequisites)
     * [Compile On Ubuntu/Debian](#compile-on-ubuntudebian)
* [Usage](#usage)
     * [Building NSG Index](#building-nsg-index)
     * [Searching via NSG Index](#searching-via-nsg-index)
* [Parameters Setting](#parameters-setting)
     * [NSG Building](#nsg-building)
* [Reference](#reference)
* [TODO](#todo)
* [License](#license)
<!--te-->

## Introduction

**NSGFlex** is an efficient open-source library uniquely designed for cross-architecture vectorization, enabling high-performance approximate nearest neighbor search (ANNS) on any platform equipped with a G++ compiler, be it x86, ARM, or others. It implements the algorithm described in our PVLDB paper - [Fast Approximate Nearest Neighbor Search With The Navigating Spread-out Graphs](http://www.vldb.org/pvldb/vol12/p461-fu.pdf). This implementation is notable for its portability and flexibility, designed to operate seamlessly across different computing environments without requiring any external dependencies.

NSGFlex is built to be a stand-alone solution that integrates easily into existing systems, promoting an easier setup and immediate usability. By eliminating the need for additional dependencies, NSGFlex ensures a straightforward installation process and reduces potential conflicts or compatibility issues with other software, making it an ideal choice for developers seeking an efficient and reliable ANNS tool.

### Highlights of NSGFlex:
- **Cross-Platform Efficiency**: Optimized for both x86 and ARM architectures, NSGFlex delivers high-speed performance and precision in nearest neighbor calculations across different hardware setups.
- **No External Dependencies**: NSGFlex does not rely on any external libraries or frameworks, simplifying its integration into any project.

With its comprehensive documentation and active community support, NSGFlex aims to provide a versatile and powerful solution for developers and researchers involved in high-dimensional data analysis and related fields.

## Building Instruction

### Prerequisites

+ GCC 11+
+ CMake 3.22+


### Compile On Ubuntu/Debian

1. Install Dependencies:

```shell
$ sudo apt-get install g++ cmake
```

2. Compile NSGFlex:

```shell
$ git clone https://github.com/GatePara/NSGFlex.git
$ cd NSGFlex/
$ mkdir build/ && cd build/
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make -j
```

## Usage

The main interfaces and classes have its respective test codes under directory `tests/`

### Building NSG Index

To use NSG for ANNS, an NSG index must be built first. Here are the instructions for building NSG.

#### Step 1. Build kNN Graph

Firstly, we need to prepare a kNN graph.

We suggest you use our [efanna\_graph](https://github.com/ZJULearning/efanna\_graph) to build this kNN graph. But you can also use any alternatives you like, such as KGraph or faiss.

#### Step 2. Convert kNN Graph to NSG

Secondly, we will convert the kNN graph to our NSG index.

You can use our demo code to achieve this converstion as follows:
```shell
$ cd build/tests/
$ ./test_nsg_index DATA_PATH KNNG_PATH L R C NSG_PATH
```

+ `DATA_PATH` is the path of the base data in `fvecs` format.
+ `KNNG_PATH` is the path of the pre-built kNN graph in *Step 1.*.
+ `L` controls the quality of the NSG, the larger the better.
+ `R` controls the index size of the graph, the best R is related to the intrinsic dimension of the dataset.
+ `C` controls the maximum candidate pool size during NSG contruction.
+ `NSG_PATH` is the path of the generated NSG index.

### Searching via NSG Index

Here are the instructions of how to use NSG index for searching.

You can use our demo code to perform kNN searching as follows:
```shell
$ cd build/tests/
$ ./test_nsg_optimized_search DATA_PATH QUERY_PATH NSG_PATH SEARCH_L SEARCH_K RESULT_PATH
```

+ `DATA_PATH` is the path of the base data in `fvecs` format.
+ `QUERY_PATH` is the path of the query data in `fvecs` format.
+ `NSG_PATH` is the path of the pre-built NSG index in previous section.
+ `SEARCH_L` controls the quality of the search results, the larger the better but slower. The `SEARCH_L` cannot be samller than the `SEARCH_K`
+ `SEARCH_K` controls the number of result neighbors we want to query.
+ `RESULT_PATH` is the query results in `ivecs` format.

There is another program in `tests/` folder named `test_nsg_search`. The parameters of `test_nsg_search` are exactly same as `test_nsg_optimized_search`. `test_nsg_search` is slower than `test_nsg_optimized_search` but requires less memory. In the situations memory consumption is extremely important, one can use `test_nsg_search` instead of `test_nsg_optimized_search`.

***NOTE:** Only data-type int32 and float32 are supported for now.*

> HINT: The `data_align()` function we provided is essential for the correctness of our procedure, because we use SIMD instructions for acceleration of numerical computing such as AVX and SSE2.
You should use it to ensure your data elements (feature) is aligned with 8 or 16 int or float.
For example, if your features are of dimension 70, then it should be extend to dimension 72. And the last 2 dimension should be filled with 0 to ensure the correctness of the distance computing. And this is what `data_align()` does.

> HINT: Please refer [here](http://yael.gforge.inria.fr/file_format.html) for the desciption of `fvecs/ivecs` format.

## Parameters Setting

### NSG Building

We use [efanna_graph](https://github.com/ZJULearning/efanna_graph) to build the kNN graph.

#### Step 1. Build kNN Graph

+ Tool: [efanna_graph](https://github.com/ZJULearning/efanna_graph)
+ Parameters:

| Dataset |  K  |  L  | iter |  S |  R  |
|:-------:|:---:|:---:|:----:|:--:|:---:|
|  SIFT1M | 200 | 200 |  10  | 10 | 100 |
|  GIST1M | 400 | 400 |  12  | 15 | 100 |

+ Commands:
```shell
$ efanna_graph/tests/test_nndescent sift.fvecs sift_200nn.graph 200 200 10 10 100    # SIFT1M
$ efanna_graph/tests/test_nndescent gist.fvecs gist_400nn.graph 400 400 12 15 100    # GIST1M
```

#### Step 2. Convert kNN Graph to NSG

+ Parameters:

| Dataset |  L |  R |  C  |
|:-------:|:--:|:--:|:---:|
|  SIFT1M | 40 | 50 | 500 |
|  GIST1M | 60 | 70 | 500 |

+ Commands:
```shell
$ NSGFlex/build/tests/test_nsg_index sift.fvecs sift_200nn.graph 40 50 500 sift.nsg        # SIFT1M
$ NSGFlex/build/tests/test_nsg_index gist.fvecs gist_400nn.graph 60 70 500 gist.nsg        # GIST1M
```

## Reference

```
@article{FuNSG17,
  author    = {Cong Fu and Chao Xiang and Changxu Wang and Deng Cai},
  title     = {Fast Approximate Nearest Neighbor Search With The Navigating Spreading-out Graphs},
  journal   = {{PVLDB}},
  volume    = {12},
  number    = {5},
  pages     = {461 - 474},
  year      = {2019},
  url       = {http://www.vldb.org/pvldb/vol12/p461-fu.pdf},
  doi       = {10.14778/3303753.3303754}
}
```

## TODO

- [ ] Add arm neon support

## License

NSGFlex is MIT-licensed.
