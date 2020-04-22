#include "utils.h"

#define BOOKS_PATH   "datasets/books.csv"
#define REVIEWS_PATH "datasets/reviews.csv"


int main(int argc, const char* argv[]) {
    Books b(BOOKS_PATH, argv[1]);
    Reviews r(REVIEWS_PATH);
    b.read_csv();
    r.read_csv();
    b.parse_books();
    r.parse_reviews();
    return 0;
}