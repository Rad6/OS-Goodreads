#include "utils.h"


// -------------------- Books --------------------
Books::Books(/* args */)
{
}

void Books::insert_book(Book new_book)
{
    this->books.insert({new_book.get_book_id(), new_book});
}

Books::~Books()
{
}


// ------------------ Reviews --------------------
Reviews::Reviews(/* args */)
{
}

void Reviews::insert_review(Review new_review)
{
    this->reviews.push_back(new_review);
}

Reviews::~Reviews()
{
}


// ------------------ Book --------------------
Book::Book(vector<string> input)
{
    this->book_id = stoi(input[0]);
    this->book_title = input[1];
    this->genre_1 = input[2];
    this->genre_2 = input[3];
    this->pages = stoi(input[4]);
    this->author_name = input[5];
    this->author_average_rating = stof(input[6]);
}

int Book::get_book_id()
{
    return this->get_book_id;
}


// ------------------ Review --------------------
Review::Review(vector<string> input)
{
    this->book_id = stoi(input[0]);
    this->rating = stoi(input[1]);
    this->number_of_likes = stoi(input[2]);
}

