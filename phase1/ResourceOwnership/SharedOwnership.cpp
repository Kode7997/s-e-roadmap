/*
This file explains shared ownership concept

std::shared_ptr<> sh_ptr;

Key points:
1. Copy is allowed
2. Maintains reference count of number of times resource being shared
3. store(copy) v/s use(borrow)
4. move semantics and resource.get() method
5. cyclic reference

problem:
1. Cyclic reference - problem of referential loop. where each object points to next and last object reference to first
    object causing loop.

    This is solved using weak pointer.
*/

#include<iostream>
#include<memory>
#include<string>

class Database {
    public:
        int id_;
        std::string db_name_;


        Database(int id, const std::string& db_name): id_(id), db_name_(db_name){
            std::cout<<"Ctor: DB Created"<<std::endl;
        }

        ~Database(){
            std::cout<<"Dtor DB"<<std::endl;
        }

        void display() {
            std::cout<<"DB id: "<<id_<<" DB name: "<<db_name_<<std::endl;
        }

        void display_ref_count(std::shared_ptr<Database>& db) {
            std::cout<<"Ref Count: "<<db.use_count()<<std::endl;
        }
};

void test_copy() {

    std::shared_ptr<Database> db1(new Database(1, "AdminDB"));  // or auto db1 = std::make_shared<Database>(1, "AdminDB");

    std::cout<<"Ref count before sharing"<<std::endl;
    db1->display_ref_count(db1);

    std::shared_ptr<Database> db1_cpy1 = db1;   // Copy allowed
    std::shared_ptr<Database> db1_cpy2 = db1;

    db1->display();
    db1->display_ref_count(db1);

    std::cout<<"Before scope count"<<std::endl;
    
    {
        std::shared_ptr<Database> db1_cpy_local = db1;
        std::cout<<"With scope count"<<std::endl;
        db1->display();
        db1->display_ref_count(db1);
    
        // owners: db1, db1_cpy1, db1_cpy2, and db1_cpy_local
    }
    std::cout<<"After scope count"<<std::endl;

    std::shared_ptr<Database> db1_cpy3 = db1;

    // owners afer scope: db1, db1_cpy1, db1_cpy2, db1_cpy3

    db1->display();
    db1->display_ref_count(db1);
}   // memory/resource freed/released


void test_cyclic_reference() {

    struct Node{
        int id;
        std::shared_ptr<Node> next;

        Node(int id) :id(id), next(nullptr) {
            std::cout<<"Node Ctor"<<std::endl;
        }

        ~Node() {
            std::cout<<"Node Dtor"<<std::endl;
        }
    };

    auto display = [](std::shared_ptr<Node>& node) {
        std::cout<<"Ref Count of "<<node->id<<" count: "<<node.use_count()<<std::endl;
    };
    // node1->node2->node3->node1

    auto node1 = std::make_shared<Node>(1);
    auto node2 = std::make_shared<Node>(2);
    auto node3 = std::make_shared<Node>(3);

    display(node1);
    display(node2);
    display(node3);

    std::cout<<"Display ref count after cyclic reference"<<std::endl;

    node1->next = node2;
    node2->next = node3;
    node3->next = node1;

    display(node1);
    display(node2);
    display(node3);

}   // destructor is never called because object is shared one another causing referential loop.



int main()
{
    test_copy();

    test_cyclic_reference();

    return 0;
}