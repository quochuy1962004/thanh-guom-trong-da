#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"


enum ItemType {anti = 0, phoI, phoII, phoIII, phoIV};

//tạo danh sách liên kết đơn
struct Node {
    ItemType data;
    Node* next;
};
class linkList {
public:
    Node* head;
    linkList() {
        head = nullptr;
    }
    void insertFirst(ItemType x) {
        Node* node = new Node;
        node->data = x;
        node->next = NULL;
        if(head == NULL) {
            head = node;
            head ->next = NULL;
        } else {
            node->next = head;
            head = node;
        }
    }
};

// #define DEBUG

class Events {
public:
    int numEvent = 0;
    int* arrEvent;
    Events(const string & file_events) {
        ifstream fileEvent(file_events);
        string line1, line2;
        getline(fileEvent, line1);
        getline(fileEvent, line2);
        stringstream n(line1);
        n >> numEvent;
        arrEvent = new int[numEvent];
        stringstream m(line2);
        for (int i = 0; i < numEvent; i++) {
            m >> arrEvent[i];
        }
        fileEvent.close();
    }
    int count() const {
        return numEvent;
    }
    int get(int i) const {
        return arrEvent[i];
    }
    ~Events() {
        delete[] arrEvent;
    }
};


class BaseBag {
public:
    virtual string toString();
    linkList listItem;
    
    ~BaseBag() {
        Node* current = listItem.head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

};

class BaseOpponent;

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };

class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    KnightType knightType;
public:
    BaseBag* bag;
    int maxItem;

    static BaseKnight* create(int id, int maxhp, int level, int phoenixdownI ,int gil, int antidote);
    int getHp() {
         return hp;
    }
    void setHP(int hp) {
        this -> hp = hp;
    }
    int getMaxHP() {
        return maxhp;
    }
    int getLevel() {
        return level;
    }
    void setLevel(int level) {
        this->level = level;
    }
    int getGil() {
        return gil;
    }
    void setGil(int gil) {
        this->gil = gil;
    }
    KnightType getKnightType() {
        return knightType;
    }
    int getId() {
        return id;
    }
    
    string toString() const;
};

class ArmyKnights {
private:
    bool shield=0, spear=0, hair=0, sword=0, isOmega=0, seeHades=0;
    
    
public:
    int numKnight;
    int last = numKnight - 1; //biến lưu vị trí hiệp sĩ cuối
    BaseKnight** arrKnights;
    void addGil(BaseKnight** arrKnights, int numKnight, int gilAdded);

    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    //bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;
public:
    KnightAdventure();
    ~KnightAdventure();

    void loadArmyKnights(const string & file_armyknights) {
        armyKnights = new ArmyKnights(file_armyknights);
    }

    void loadEvents(const string & file_events) {
        events = new Events(file_events);
    }

    void run() {
        armyKnights->adventure(events);
    }
    
};

#endif // __KNIGHT2_H__
