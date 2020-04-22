#include <string.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>

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
    int get_book_id();
};


class Books
{
public:
    string                    path;
    string                    genre;
    char                      *buffer;
    int                       buffer_length;
    unordered_map<int, Book*> books;

    Books(string path, string genre);
    ~Books();
    void read_csv();
    void parse_books();
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
    string          path;
    char            *buffer;
    int             buffer_length;
    vector<Review*> reviews;

    Reviews(string path);
    ~Reviews();
    void read_csv();
    void parse_reviews();
};

void print_result(unordered_map<int, Book*> &books, vector<Review*> &reviews);