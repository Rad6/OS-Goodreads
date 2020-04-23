#include <string.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <cmath>
#include <pthread.h>

#define BOOKS_THREADS_NUM   2
#define REVIEWS_THREADS_NUM 4

#define BOOKS_PATH   "datasets/books.csv"
#define REVIEWS_PATH "datasets/reviews.csv"

using namespace std;


class Book
{
public:
    int     book_id;
    string  book_title;
    string  genre_1;
    string  genre_2;
    int     pages;
    string  author_name;
    float   author_average_rating;
    int     totol_book_reviews_likes;
    float   score;

    Book(vector<string> &input);
};

class Books
{
public:
    string                    genre;
    char                      *buffer;
    int                       buffer_length;
    unordered_map<int, Book*> books;
};

class Review
{
public:
    int book_id; // which is not an ID though
    int rating;
    int number_of_likes;

    Review(vector<string> &input);
};

class Reviews
{
public:
    char            *buffer;
    int             buffer_length;
    vector<Review*> reviews;
};


vector<long> specify_boundaries(bool is_book);