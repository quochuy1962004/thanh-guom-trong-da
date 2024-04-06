#include "knight2.h"

//hàm kiểm tra số nguyên tố
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

//hàm kiểm tra số pytago
bool pytago (int n) {
    int a, b, c;
    a = n%10;
    b = (n/10)%10;
    c = n/100;
    if(a*a == b*b + c*c || b*b == a*a + c*c || c*c == a*a + b*b) return true;
    return false;
    
}

BaseKnight* BaseKnight::create(int id, int maxhp, int level, int phoenixdownI,  int gil, int antidote) {
        BaseKnight* knight = new BaseKnight();
        knight -> id = id;
        knight -> maxhp = maxhp;
        knight -> hp = maxhp;
        knight -> level = level;
        knight -> gil = gil;
        knight -> antidote = antidote;
        knight -> phoenixdownI = phoenixdownI;
        knight -> bag = new BaseBag;
        if(isPrime(maxhp) == 1) {
            knight -> knightType = PALADIN;
            for(int i = 0; i<phoenixdownI; i++) {
                knight->bag->listItem.insertFirst(phoI);
            }
            for(int i = 0; i<antidote; i++) {
                knight->bag->listItem.insertFirst(anti);
            }
        }else if(maxhp == 888) {
            knight->knightType = LANCELOT;
            knight->maxItem = 16;
            for(int i = 0; i<phoenixdownI; i++) {
                knight->bag->listItem.insertFirst( phoI);
            }
            for(int i = 0; i<antidote; i++) {
                knight->bag->listItem.insertFirst(anti);
            }
            
        }else if(pytago(maxhp) == 1) {
            knight->knightType = DRAGON;
            knight->maxItem = 14;
            for(int i = 0; i<phoenixdownI; i++) {
                knight->bag->listItem.insertFirst(phoI);
            }

        }else {
            knight->knightType = NORMAL;
            knight->maxItem = 19;
            for(int j = 0; j<phoenixdownI; j++) {
                knight->bag->listItem.insertFirst(phoI);
            }
            for(int j = 0; j<antidote; j++) {
                knight->bag->listItem.insertFirst(anti);
            }
        }

        return knight;
    }
//bắt đầu triển khai các lớp con của class BaseItem
class phoenixdownI:public BaseItem{
public:
    ItemType type = phoI;
    bool canUse ( BaseKnight * knight ) {
        return knight->getHp() <= 0;
    }
    virtual void use ( BaseKnight * knight ) {
        knight -> setHP(knight->getMaxHP());
    }
};

class phoenixdownII:public BaseItem{
public:
    ItemType type = phoII;
    bool canUse ( BaseKnight * knight ) {
        return knight->getHp() < (knight->getMaxHP()/4);
    }
    virtual void use ( BaseKnight * knight ) {
        knight -> setHP(knight->getMaxHP());
    }
};

class phoenixdownIII:public BaseItem{
public:
    ItemType type = phoIII ;
    bool canUse ( BaseKnight * knight ) {
        return knight->getHp() < (knight->getMaxHP()/3);
    }
    virtual void use ( BaseKnight * knight ) {
        if(knight->getHp() <= 0) knight -> setHP(knight->getMaxHP()/3);
        else knight->setHP( knight->getHp() + knight->getMaxHP()/4);
    }
};

class phoenixdownIV:public BaseItem{
public:
    ItemType type = phoIV;
    bool canUse ( BaseKnight * knight ) {
        return knight->getHp() < (knight->getMaxHP()/2);
    }
    void use ( BaseKnight * knight ) {
        if(knight->getHp() <= 0) knight -> setHP(knight->getMaxHP()/2);
        if(knight->getHp() < knight->getMaxHP()/2) knight->setHP( knight->getHp() + knight->getMaxHP()/5);
    }
};

class antidote:public BaseItem{
public:
    ItemType type = anti;
    bool isPoison;
    bool canUse ( BaseKnight * knight ) {
        return isPoison;
    }
    virtual void use ( BaseKnight * knight ) {
       isPoison = false;
    }
};
//kết thúc triển khai các lớp con của class BaseItem

//tìm kiếm vật phẩm trả về vị trí của item
int Search(linkList l, ItemType x) {
    int posItem = -1;
	Node* node = l.head;
	while ( node != NULL) {
        if(node->data == x) posItem++;
        node = node->next;
    }
	return posItem;
}
//xóa phần tử chỉ định trước
void RemoveItem(linkList& l, ItemType x) {
	if (l.head != NULL) {
		Node* node = l.head;
	    while (node != NULL && node->data != x) {
            node = node->next;
        }
        swap(node->data, l.head->data);

        Node* p = l.head;
        l.head = p -> next;
        delete p;
	}
}
//xóa phần tử đầu danh sách
void RemoveHead(linkList& l) {
	if (l.head != NULL) {
		Node* node = l.head; 
		l.head = node->next;
		delete node;         // Hủy node head đi
	}
}
//hàm trả về số lượng item hiện có
int Length(linkList listItem) { 
	int count = 0;
	Node* node = listItem.head;
	while (node != NULL) {
		count++;
	    node = node->next;
	}
	return count;
}
//hàm tìm phonixdown khi hp <= 0
bool findPhoenixdown(linkList &listItem, BaseKnight* knight) {
    Node* node = listItem.head;
    while(node != NULL) {
        if(node->data == phoI) {
            phoenixdownI t;
            t.use(knight);
            RemoveItem(knight->bag->listItem, phoI);
            return true;
        }
        if(node->data == phoII) {
            phoenixdownII t;
            t.use(knight);
            RemoveItem(knight->bag->listItem, phoII);
            return true;
        }
        if(node->data == phoIII) {
            phoenixdownIII t;
            t.use(knight);
            RemoveItem(knight->bag->listItem, phoIII);
            return true;
        }
        if(node->data == phoIV) {
            phoenixdownIV t;
            t.use(knight);
            RemoveItem(knight->bag->listItem, phoIV);
            return true;
        }
        node = node->next;
    }
    return false;
}


/* * * BEGIN implementation of class BaseBag * * */
/*
class PaladinBag:public BaseBag {
    PaladinBag(){};
    PaladinBag(BaseKnight* knight, int phoenixdownI, int antidote) {
        createList(knight->bag->listItem);
        if(phoenixdownI > 0) {
            for(int i = 0; i<phoenixdownI; i++) {
                knight->bag->insertFirst(knight->bag->listItem, phoI);
            }
        }
        if(antidote > 0) {
            for(int i = 0; i<antidote; i++) {
                knight->bag->insertFirst(knight->bag->listItem, anti);
            }
        }
    }
};

class LancelotBag:public BaseBag {
    int maxItem = 16;
    LancelotBag(BaseKnight* knight, int phoenixdownI, int antidote) {
        if(phoenixdownI > 0) {
            for(int i = 0; i<phoenixdownI; i++) {
                knight->bag->insertFirst(knight->bag->listItem, phoI);
            }
        }
        if(antidote > 0) {
            for(int i = 0; i<antidote; i++) {
                knight->bag->insertFirst(knight->bag->listItem, anti);
            }
        }
    }
};

class DragonBag:public BaseBag {
    int maxItem = 14;
    DragonBag(BaseKnight* knight, int phoenixdownI, int antidote) {
        if(phoenixdownI > 0) {
            for(int i = 0; i<phoenixdownI; i++) {
                knight->bag->insertFirst(knight->bag->listItem, phoI);
            }
        }
    }
};

class NormalBag:public BaseBag {
    int maxItem = 19;
    NormalBag(BaseKnight* knight, int phoenixdownI, int antidote) {
        if(phoenixdownI > 0) {
            for(int i = 0; i<phoenixdownI; i++) {
                knight->bag->listItem.insertFirst(phoI);
            }
        }
        if(antidote > 0) {
            for(int i = 0; i<antidote; i++) {
                knight->bag->listItem.insertFirst(anti);
            }
        }
    }
};
*/
/*
BaseItem* BaseBag::get(ItemType itemType){
    Node* node = listItem.head;
    while(node != NULL && node->data != itemType) node = node->next;
    if(node != NULL) {
        if(node == listItem.head) {
            listItem.head = node->next;
            delete node;
            return;
        } else {
            swap(node, listItem.head);
            listItem.head = node->next;
            delete node;
            return;
        }
    };
    return NULL;
}
*/
string BaseBag::toString()  {
    string s(""); 
    s+= "Bag[count=";
    s+= to_string(Length(listItem)) + ";";

    Node* node = new Node;
    node = listItem.head;
    while (node != NULL) {
        if(node->data == 0) s+="Antidote,";
        if(node->data == 1) s+="PhoenixI,";
        if(node->data == 2) s+="PhoenixII,";
        if(node->data == 3) s+="PhoenixIII,";
        if(node->data == 4) s+="PhoenixIV,";
        node = node->next;
    }
    if(Length(listItem) != 0) s.pop_back();
    s+="]";
    return s;
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
    //hàm thêm gil cho hiệp sĩ
void ArmyKnights::addGil(BaseKnight** arrKnights, int last, int gilAdded) {
    if(gilAdded == 0 || last < 0) return;
    if(arrKnights[last]->getGil() + gilAdded > 999) {
        gilAdded = 999 - arrKnights[last]->getGil();
        arrKnights[last]->setGil(999);
    } else {
        arrKnights[last]->setGil(gilAdded + arrKnights[last]->getGil());
        gilAdded = 0;
    }
    return addGil(arrKnights, last-1, gilAdded);
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";"<< lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

ArmyKnights::ArmyKnights(const string & file_armyknights) {
    ifstream fileArmy(file_armyknights);
    string line1;
    getline(fileArmy, line1);
    stringstream temp1(line1);
    temp1 >> numKnight;
    last = numKnight - 1;
    arrKnights = new BaseKnight*[numKnight];
 
    for(int i = 0; i < numKnight; i++) {
        int  a2, a3, a4, a5, a6;
        string str;
        getline(fileArmy, str);
        stringstream temp2(str);
        temp2 >> a2 >> a3 >> a4 >> a5 >> a6;
        arrKnights[i] = BaseKnight::create(i+1, a2, a3 ,a4, a5, a6);
    }
   fileArmy.close();
}

ArmyKnights::~ArmyKnights() {
    for(int i = 0; i < numKnight; i++) {
        delete arrKnights[i];
    }
    delete[] arrKnights;
}

int ArmyKnights::count() const {
    return last+1;
}

BaseKnight * ArmyKnights::lastKnight() const{
    if(last < 0) return NULL;
    return arrKnights[last]; 
}

bool ArmyKnights::hasPaladinShield() const{
    return shield;
}
bool ArmyKnights::hasLancelotSpear() const{
    return spear;
}
bool ArmyKnights::hasGuinevereHair () const {
    return hair;
}
bool ArmyKnights::hasExcaliburSword () const {
    return sword;
}

bool ArmyKnights::adventure(Events* events) {
    for(int i = 0; i < events->count(); i++) {
        if(events->get(i) <= 5) {
            int baseDamage, gilAdded;
            switch (events->get(i)) {
            case 1:
                baseDamage = 10;
                gilAdded = 100;
                break;
            case 2:
                baseDamage = 15;
                gilAdded = 150;
                break;
            case 3:
                baseDamage = 45;
                gilAdded = 450;
                    break;
            case 4:
                baseDamage = 75;
                gilAdded = 750;
                break;
            case 5:
                baseDamage = 95;
                gilAdded = 800;
                break;
            default:
                break;
            }
            if(arrKnights[last]->getKnightType() == LANCELOT || arrKnights[last]->getKnightType() == PALADIN) {//bị đánh bại bơi lancelot hoặc Paladin
                addGil(arrKnights, last, gilAdded);
                printInfo();
                continue;
            }    
            int levelO = 0;
            levelO = (i + events->get(i))%10 + 1;
            if(arrKnights[last] -> getLevel() >= levelO) {
                addGil(arrKnights, last, gilAdded);
            }

            if (arrKnights[last]->getLevel() < levelO) {
                arrKnights[last]->setHP(arrKnights[last]->getHp() - baseDamage * (levelO - arrKnights[last]->getLevel()));
                if(arrKnights[last]->getHp() < arrKnights[last]->getMaxHP()/ 4 && Search(arrKnights[last]->bag->listItem, phoII) != -1) {
                    phoenixdownII t;
                    t.use(arrKnights[last]);
                    RemoveItem(arrKnights[last]->bag->listItem, phoII);
                }
                if(arrKnights[last]->getHp() < arrKnights[last]->getMaxHP()/ 3 && Search(arrKnights[last]->bag->listItem, phoIII) != -1) {
                    phoenixdownIII t;
                    t.use(arrKnights[last]);
                    RemoveItem(arrKnights[last]->bag->listItem, phoIII);
                }
                if(arrKnights[last]->getHp() < arrKnights[last]->getMaxHP()/ 2 && Search(arrKnights[last]->bag->listItem, phoIV) != -1) {
                    phoenixdownIV t;
                    t.use(arrKnights[last]);
                    RemoveItem(arrKnights[last]->bag->listItem, phoIV);
                }

                if(arrKnights[last]->getHp() <= 0) {
                    //bước 1: bắt đầu tìm kiếm và sử dụng loại phoenĩdơn đầu tiên trong túi
                    bool isUsePho = findPhoenixdown(arrKnights[last]->bag->listItem, arrKnights[last]);
                    //bước 2: dùng gil
                    if(isUsePho == 0) {
                        if(arrKnights[last]->getGil() >= 100) {
                            arrKnights[last]->setGil(arrKnights[last]->getGil() - 100);
                            arrKnights[last]->setHP(arrKnights[last]->getMaxHP() / 2);
                        } else {
                            last--;
                            printInfo();
                            if(last < 0) {
                                printResult(false);
                                break;
                            }
                            continue;
                        }
                    } 
                }
            }
            printInfo();
        }

        if(events->get(i) == 6) {
            int levelO = 0;
            levelO = (i + events->get(i))%10 + 1;
            if(arrKnights[last] -> getLevel() >= levelO) { //thắng
                arrKnights[last] -> setLevel(arrKnights[last]->getLevel() + 1);
                if(arrKnights[last] -> getLevel() > 10) arrKnights[last] -> setLevel(10);
            }
            if (arrKnights[last]->getLevel() < levelO) { //thua
                if(arrKnights[last]->getKnightType() == DRAGON) {//hiệp sĩ rồng k bị trúng độc
                    printInfo();
                    continue;
                }
                int posItem = Search(arrKnights[last]->bag->listItem, anti);
                if(posItem > -1) {    
                    RemoveItem(arrKnights[last]->bag->listItem, anti);
                } else {
                    if(Length(arrKnights[last]->bag->listItem) <= 3) {
                        arrKnights[last]->bag->listItem.head = NULL;
                    } else {
                        RemoveHead(arrKnights[last]->bag->listItem);
                        RemoveHead(arrKnights[last]->bag->listItem);
                        RemoveHead(arrKnights[last]->bag->listItem);
                    }
                    arrKnights[last]->setHP(arrKnights[last]->getHp() - 10);
                    if(arrKnights[last]->getHp() <= 0) {
                        //bước 1: bắt đầu tìm kiếm và sử dụng loại phoenĩdơn đầu tiên trong túi
                        bool isUsePho = findPhoenixdown(arrKnights[last]->bag->listItem, arrKnights[last]);
                        //bước 2: dùng gil
                        if(isUsePho == 0) {
                            if(arrKnights[last]->getGil() >= 100) {
                                arrKnights[last]->setGil(arrKnights[last]->getGil() - 100);
                                arrKnights[last]->setHP(arrKnights[last]->getMaxHP() / 2);
                            } else {
                                last--;
                                printInfo();
                                if(last < 0) {
                                    printResult(false);
                                    break;
                                }
                                continue;
                            }
                        } 
                    }
                }
            }
            printInfo();        
        }

        if(events->get(i) == 7) {
            int levelO = (i + events->get(i))%10 + 1;
            if(arrKnights[last]->getLevel() >= levelO) { //thắng
                arrKnights[last]->setGil(arrKnights[last]->getGil()*2);
                if(arrKnights[last]->getGil() > 999) {
                    arrKnights[last]->setGil(999);
                    int gilAdded = arrKnights[last]->getGil()*2 - 999;
                    addGil(arrKnights, last, gilAdded);
                }
            } else {     //thua   
                if(arrKnights[last]->getKnightType() != PALADIN) { //Paladin khong bi giam gil
                    arrKnights[last]->setGil(arrKnights[last]->getGil()/2);
                }
            }
            printInfo();
        }
    
        if(events->get(i) == 8) {
            if(arrKnights[last]->getGil() < 50) {
                if(arrKnights[last]->getKnightType() == PALADIN && arrKnights[last]->getHp() < arrKnights[last]->getMaxHP()/3) {
                    arrKnights[last]->setHP(arrKnights[last]->getMaxHP()/5 + arrKnights[last]->getHp());
                }
            } else {
                if(arrKnights[last]->getHp() < arrKnights[last]->getMaxHP()/3) {
                    arrKnights[last]->setHP(arrKnights[last]->getMaxHP()/5 + arrKnights[last]->getHp());
                    arrKnights[last]->setGil(arrKnights[last]->getGil() - 50);
                }
            }
            printInfo();
        }
    
        if(events->get(i) == 9) {
            arrKnights[last]->setHP(arrKnights[last]->getMaxHP());
            printInfo();
        }
    
        if(events->get(i) == 10) {
            if((arrKnights[last]->getLevel() == 10 && arrKnights[last]->getHp() == arrKnights[last]->getMaxHP()) || arrKnights[last]->getKnightType() == DRAGON) {
                arrKnights[last]->setLevel(10);
                arrKnights[last]->setGil(999);
            } else {
                arrKnights[last]->setHP(0);
                //bước 1: bắt đầu tìm kiếm và sử dụng loại phoenĩdơn đầu tiên trong túi
                bool isUsePho = findPhoenixdown(arrKnights[last]->bag->listItem, arrKnights[last]);
                //bước 2: dùng gil
                if(isUsePho == 0) {
                    if(arrKnights[last]->getGil() >= 100) {
                        arrKnights[last]->setGil(arrKnights[last]->getGil() - 100);
                        arrKnights[last]->setHP(arrKnights[last]->getMaxHP() / 2);
                    } else {
                        last--;
                        printInfo();
                        if(last < 0) {
                            printResult(false);
                            break;
                        }
                        continue;
                    }
                } 
            }
            printInfo();
            //nếu sự kiện cuối cùng
            if(i == events->numEvent) { 
                if(last >= 0){ 
                    printResult(true);
                } else {
                    printResult(false);
                }
            }
        }
        
        if(events->get(i) == 11) {
            //nếu trong sự kiện phía trước có Hades thì sẽ bỏ qua
            for(int j = 0; j<i; j++) {
                if(events->get(j) == 11) {
                    seeHades = 1;
                }
            }
            if(seeHades == 1) {
                printInfo();
                continue;
            }
            if((arrKnights[last]->getKnightType() == PALADIN && arrKnights[last]->getLevel()>=8) || arrKnights[last]->getLevel()==10) {
                shield = 1;
            } else {
                arrKnights[last]->setHP(0);
                //bước 1: bắt đầu tìm kiếm và sử dụng loại phoenĩdơn đầu tiên trong túi va su dung
    
                bool isUsePho = findPhoenixdown(arrKnights[last]->bag->listItem, arrKnights[last]);
                //bước 2: dùng gil
                if(arrKnights[last]->getHp() <= 0) {
                    if(arrKnights[last]->getGil() >= 100) {
                        arrKnights[last]->setGil(arrKnights[last]->getGil() - 100);
                        arrKnights[last]->setHP(arrKnights[last]->getMaxHP() / 2);
                    } else {
                        last--;
                        printInfo();
                        if(last < 0) {
                            printResult(false);
                            break;
                        }
                        continue;
                    }
                } 
            }
            printInfo();
        }
    
        if(events->get(i) == 99) {
            int HPUltimecia = 5000;
            if(sword == 1) { // thang
                printInfo();
                printResult(true);
                return 1;
            }
            if(sword == 0 && (shield == 0 || spear == 0 || hair == 0)) { //thua
                last = -1;
                printInfo();
                printResult(false);
                return 0;
            }
            if(sword == 0 && shield == 1 && spear == 1 && hair == 1) { //giao tranh
                while(last >= 0) {
                    if(arrKnights[last]->getKnightType() != NORMAL) {
                        int knightBaseDamage;
                        if(arrKnights[last]->getKnightType() == LANCELOT) knightBaseDamage = 0.05;
                        if(arrKnights[last]->getKnightType() == PALADIN) knightBaseDamage = 0.06;
                        if(arrKnights[last]->getKnightType() == DRAGON) knightBaseDamage = 0.75;
                        HPUltimecia -= arrKnights[last]->getHp() * arrKnights[last]->getLevel() * knightBaseDamage;
                        if(HPUltimecia <= 0) {
                            printInfo();
                            printResult(true);
                            return 1;
                        }
                    } else last--;
                }
                if(HPUltimecia > 0) {
                    printInfo();
                    printResult(false);
                    return 0;
                }
            } else {
                printInfo();
                printResult(false);
                return 0;
            }
        }
    
        if(events->get(i) == 112) {
            int k = last;
            while (k >= 0) {
                if((Length(arrKnights[k]->bag->listItem) < arrKnights[k]->maxItem) || arrKnights[k]->getKnightType() == PALADIN) {
                    arrKnights[k]->bag->listItem.insertFirst(phoII);
                    break;
                } else {
                    k--;
                } 
            }
            printInfo();  
        }

        if(events->get(i) == 113) {
            int k = last;
            while (k >= 0) {
                if((Length(arrKnights[k]->bag->listItem) < arrKnights[k]->maxItem) || arrKnights[k]->getKnightType() == PALADIN) {
                    arrKnights[k]->bag->listItem.insertFirst(phoIII);
                    break;
                } else {
                    k--;
                } 
            }
            printInfo();
        }

        if(events->get(i) == 114) {
            int k = last;
            while (k >= 0) {
                if((Length(arrKnights[k]->bag->listItem) < arrKnights[k]->maxItem) || arrKnights[k]->getKnightType() == PALADIN) {
                    arrKnights[k]->bag->listItem.insertFirst(phoIV);
                    break;
                } else {
                    k--;
                } 
            }
            printInfo();
        }
    
        if(events->get(i) == 95) {
            shield = 1;
            printInfo();
        }

        if(events->get(i) == 96) {
            spear = 1;
            printInfo();
        }

        if(events->get(i) == 97) {
            hair = 1;
            printInfo();
        }

        if(events->get(i) == 98) {
            if(spear == 1 && shield == 1 && hair == 1) {
                sword = 1;
            } 
            printInfo();
        }
         
    }
    return 1;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
}
/* * * END implementation of class KnightAdventure * * */