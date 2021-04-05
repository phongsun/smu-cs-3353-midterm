# follio - A Quantitative Comparison on Insert and Delete Operations between folly::fbvector and std:vector

# What is this?
This program quantitatively compares performance between FBVector and std:Vector on the push_back and erase operations. It is
intended to evaluate the claim that folly::fbvector has better performance than std::vector.

# How do I install it?
0. make sure you have facebook folly installed on your computer and cd $install_dir
1. clone https://github.com/smu-cs-3353/smu-cs-3352-midterm.git
2. cd smu-cs-3352-midterm
3. mkdir build
4. cd build
5. cmake ..
6. make
7. cd ..
8. ls follio
You should find follio in the directory.

# How do I try it out?
1. cd $install_dir/smu-cs-3352-midterm
2. ./follio
3. ls output.csv
You should find measurement data in output.csv 

# How do I learn more?
1. examine details of output.csv and folly_vs_stl.xlsx in the source directory
2. visit the medium.com blog post

# Which versions of C++ does it work with?
C++ 17

# What is the license?
GPL
