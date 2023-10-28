#include "queue.hh"
#include <iostream>
// Implement the member functions of Queue here


Queue::Queue(unsigned int cycle)
{
    cycle_ = cycle;
}

Queue::~Queue()
{
    while ( first_ != nullptr ) {
        Vehicle* to_be_deleted = first_;
        first_ = first_->next;

        delete to_be_deleted;
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::enqueue(const string &reg) {
    Vehicle* temp = new Vehicle({reg, nullptr});
    Vehicle* tpr = first_;

    if ( not is_green_ ) {

        if ( first_ == nullptr ) {
            first_ = temp;
        } else {
            while(tpr->next != nullptr) {
                tpr = tpr->next;
            }
            tpr->next = temp;
        }
    } else {
        cout << "GREEN: The vehicle "
             << reg
             << " need not stop to wait" << endl;
    }


}

void Queue::switch_light()
{
    Vehicle* temp = first_;
    unsigned int passed = 0;

    if ( is_green_ ) {
        is_green_ = false;
    } else if ( not is_green_ ) {
        is_green_ = true;
    }

    if ( is_green_ ) {
        if ( temp == nullptr ) {
            cout << "GREEN: No vehicles waiting in traffic lights" << endl;
            return;

        } else {
            cout << "GREEN: Vehicle(s) ";
            while ( passed < cycle_ and temp != nullptr ) {
                cout << temp->reg_num << " ";
                temp = temp->next;
                passed += 1;

                Vehicle* del = first_;
                first_ = first_->next;
                delete(del);
            }
            cout << "can go on" << endl;
            is_green_ = false;
            return;
        }
    }

    if ( not is_green_ and temp == nullptr) {
        cout << "RED: No vehicles waiting in traffic lights" << endl;
    }
}



void Queue::print() const
{
    Vehicle* temp = first_;

    std::string light = "";
    if ( is_green_ ) {
        light = "GREEN";
    } else {
        light = "RED";
    }

    if ( temp == nullptr ) {
        cout << light << ": No vehicles waiting in traffic lights" << endl;

    } else {

        std::cout << light << ": Vehicle(s) ";

        while( temp != nullptr ) {
            std::cout << temp->reg_num << " ";
            temp = temp->next;
        }
        std::cout << "waiting in traffic lights" << endl;
    }
}


