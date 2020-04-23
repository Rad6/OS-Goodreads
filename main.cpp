#include "utils.h"


pthread_t book_threads  [BOOKS_THREADS_NUM];
pthread_t review_threads[REVIEWS_THREADS_NUM];

pthread_mutex_t mutex_sum;

Books   books   [BOOKS_THREADS_NUM];
Reviews reviews [REVIEWS_THREADS_NUM];

int book_bounds[BOOKS_THREADS_NUM - 1] = {0};
int review_bounds[REVIEWS_THREADS_NUM - 1] = {0};


int main(int argc, const char* argv[]) {
    
    vector <int> book_bounds_vec   = specify_boundaries(true);
    vector <int> review_bounds_vec = specify_boundaries(false);

    for (int i = 0; i < BOOKS_THREADS_NUM - 1; i++)
        book_bounds[i] = book_bounds_vec[i];

    for (int i = 0; i < REVIEWS_THREADS_NUM - 1; i++)
        review_bounds[i] = review_bounds_vec[i];

    
    return 0;
}