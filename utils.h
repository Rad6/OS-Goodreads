#include <string.h>
#include <vector>
#include <unordered_map>

using namespace std;


class Books
{
private:
    unordered_map<int, Book> books;
public:
    Books(/* args */);
    ~Books();
    void insert_book(Book new_book);
};


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
    Book(vector<string> input);
    int get_book_id();
};


class Reviews
{
private:
    vector<Review> reviews;
public:
    Reviews(/* args */);
    ~Reviews();
    void insert_review(Review new_review);
};

class Review
{
private:
    int book_id; // which is not an ID though
    int rating;
    int number_of_likes;
public:
    Review(vector<string> input);
};

