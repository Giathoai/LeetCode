#include <iostream>
#include <vector>
using namespace std;
class Author{
    private:
    string name;
    string email;
    public:
    Author(string name, string email){
        this->name = name;
        this->email = email;
    }
    void setName(string name){
        this->name = name;
    }
    void setEmail(string email){
        this->email = email;
    }
    string getName(){
        return name;
    }
    string getEmail(){
        return email;
    }
};
class Book : public Author{
    private:
    string name;
    double price;
    vector<Author> authors;
    public:
    Book(string name, vector<Author> authors, double price){
        this->name = name;
        this->price = price;
        this->authors = authors;
    }
    void setName(string name){
        this->name = name;
    }
    void setPrice(double price){
        this->price = price;
    }
    string getName(){
        return name;
    }
    double getPrice(){
        return price;
    }
    string getAuthorNames(){
        string authorname = "";
        for(int i = 0; i < authors.size() - 1; i++){
            authorname += authors[i].getName() + ", ";
        }
        authorname += authors[authors.size() - 1 ].getName();
        return authorname;
    }
};
int main() {
	vector<Author> authors;
	authors.push_back(Author("Viet", "VietCV@codelearn.io"));
	authors.push_back(Author("Tuan", "TuanLQ7@codelearn.io"));
	authors.push_back(Author("KienNT", "KienNT@codelearn.io"));

	Book book1("C++ for Beginners", authors, 210000);
	cout << book1.getAuthorNames();	
	return 0;
}