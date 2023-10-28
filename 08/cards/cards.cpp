#include "cards.hh"
#include <iostream>

// TODO: Implement the methods here
Cards::Cards(): top_(nullptr) {
}

Card_data *Cards::get_topmost()
{
    return top_;
}



Cards::~Cards() {
    while ( top_ != nullptr ) {
        Card_data* card_to_be_released = top_;
        top_ = top_->next;

        delete card_to_be_released;
    }
}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{

    int y = 0;
    if ( top->next != nullptr) {
        y = recursive_print(top->next, s);
    }

    y += 1;


    s << y << ": " << top->data << std::endl;

    return y;
}



void Cards::add(int id) {
    Card_data* new_card = new Card_data{id, nullptr};

    new_card->next = top_;
    top_ = new_card;

}

void Cards::print_from_top_to_bottom(std::ostream &s) {
    Card_data* card_to_be_printed = top_;
    int running_number = 1;

    while ( card_to_be_printed != nullptr ) {
        s << running_number << ": "<< card_to_be_printed->data << std::endl;
        ++ running_number;
        card_to_be_printed = card_to_be_printed->next;

    }
}

bool Cards::bottom_to_top() {
    Card_data* temp = top_;

    if ( top_->next == nullptr ) {
        return true;

    } else {
        while ( temp->next->next != nullptr ) {
            temp = temp->next;
        }

        int v = temp->next->data;
        Cards::add(v);

        delete(temp->next);
        temp->next = nullptr;

        return true;
    }

}

bool Cards::remove(int& id) {


    if ( top_ != nullptr) {
        id = top_->data;

        Card_data* temp = top_;
        top_ = top_->next;
        delete(temp);
        return true;
    } else {
        return false;
    }

}

bool Cards::top_to_bottom() {
    int id = top_->data;
    Card_data* temp = new Card_data({id, nullptr});

    if ( top_ == nullptr) {
        return false;

    } else {

        Card_data* ptr = top_;
        while ( ptr->next != nullptr ) {
            ptr = ptr->next;
        }

        ptr->next = temp;

        Card_data* del = top_;
        top_ = top_->next;
        delete(del);

        return true;
    }
}

void Cards::print_from_bottom_to_top(std::ostream &s) {

    if ( top_->next != nullptr ) {
        recursive_print(top_, s);
    } else {
        s << top_->data << std::endl;
    }
}


