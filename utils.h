#include <string.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>

using namespace std;


class Book
{
private:
    int     book_id;
    string  book_title;
    string  genre_1;
    string  genre_2;
    int     pages;
    string  author_name;
    float   author_average_rating;
public:
    Book(vector<string> &input);
    int get_book_id();
};


class Books
{
private:
    string                   path;
    string                   genre;
    unordered_map<int, Book> books;
    char                     *buffer;
    int                      buffer_length;
public:
    Books(string path, string genre);
    ~Books();
    void insert_book(Book new_book);
    void read_csv();
    void parse_books();
};


class Review
{
private:
    int book_id; // which is not an ID though
    int rating;
    int number_of_likes;
public:
    Review(vector<string> &input);
};


class Reviews
{
private:
    string         path;
    vector<Review> reviews;
    char           *buffer;
    int            buffer_length;
public:
    Reviews(string path);
    ~Reviews();
    void insert_review(Review new_review);
    void read_csv();
    void parse_reviews();
};


