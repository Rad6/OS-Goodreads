#include <string.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <cmath>
#include <pthread.h>

#define BOOKS_THREADS_NUM   4
#define REVIEWS_THREADS_NUM 6

#define BOOKS_PATH   "datasets/books.csv"
#define REVIEWS_PATH "datasets/reviews.csv"

using namespace std;



vector<int> specify_boundaries(bool is_book);
