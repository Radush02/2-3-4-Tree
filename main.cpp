#include <iostream>
#include <vector>
#include <algorithm>
#define nrmax 3
using namespace std;

class Node {
public:
    vector<int> val;
    vector<Node*> fii;
    bool frunza;
    Node(bool isfrunza) {
        frunza = isfrunza;
    }
};

class Tree {
public:
    Node* rad;

    Tree() {
        rad = nullptr;
    }

    void insert(int val) {
        if (rad == nullptr){ //evident
            rad = new Node(true);
            rad->val.push_back(val);
        } else {
            if (rad->val.size() == nrmax) {
                //daca radacina e plina, cream un nou nod si dam split
                Node* newRoot = new Node(false); //deoarece vechea radacina o sa fie frunza dupa ce dam split, e clar ca nu poate fi frunza
                newRoot->fii.push_back(rad); //radacina e primul fiu
                split(newRoot, 0, rad); //split la fiu si redistribuim valorile intre fiu si noul nod
                rad = newRoot;
            }
            insertNonFull(rad, val); //apelam recursiv functia pt a gasi pozitia la care sa inseram
        }
    }

    void insertNonFull(Node* aux, int val) {
        int i = aux->val.size() - 1;
        if (aux->frunza) {
            // Daca e frunza, inseram la pozitia corecta
            aux->val.push_back(0);
            while (i >= 0 && val < aux->val[i]) {
                aux->val[i + 1] = aux->val[i];
                i--;
            }
            aux->val[i + 1] = val;
        } else {
            // Daca nu e frunza, cautam fii pt inserare
            while (i >= 0 && val < aux->val[i]) {
                i--;
            }
            i++;
            if (aux->fii[i]->val.size() == nrmax) {
                //Daca e full, dam split si inseram
                split(aux, i, aux->fii[i]);
                if (val > aux->val[i]) {
                    i++;
                }
            }
            insertNonFull(aux->fii[i], val);
        }
    }
    void split(Node* parent, int childIndex, Node* child) {
        Node* newNode = new Node(child->frunza);
        newNode->val.reserve(nrmax - 1); //vrem doar sa alocam, nu sa si initializam.
        newNode->fii.reserve(nrmax);

        // Mutam a doua jumatate din vectorul de elemente din nodul fiu in noul nod
        for (int i=2;i<nrmax;i++)
            newNode->val.push_back(child->val[i]);

        if (!child->frunza)
            for (int i=2;i<=nrmax;i++)
                newNode->fii.push_back(child->fii[nrmax]);


        //Inseram mijlojul in tata
        parent->val.insert(parent->val.begin() + childIndex, child->val[1]);
        parent->fii.insert(parent->fii.begin() + childIndex + 1, newNode);

        //redimensionam
        child->val.resize(nrmax / 2);
        parent->val.resize(parent->val.size());
        parent->fii.resize(parent->fii.size());

    }

    void afis() {
        if (rad != nullptr) {
            inordine(rad);
        }
    }

    void inordine(Node* nod) {
        int i;
        for (i = 0; i < nod->val.size(); i++) {
            if (!nod->frunza)
                inordine(nod->fii[i]);
            cout << nod->val[i] << " ";
        }
        if (!nod->frunza) {
            inordine(nod->fii[i]);
        }
    }
    bool search(int val){
        if(rad==nullptr)
            return false;
        return cautaInordine(rad,val);
    }
    bool cautaInordine(Node *nod,int val){
        int i;
        for(i=0;i<nod->val.size();i++){
            if(!nod->frunza && val<nod->val[i])
                return cautaInordine(nod->fii[i],val);
            if(nod->val[i]==val)
                return true;
        }
        if (!nod->frunza)
            return cautaInordine(nod->fii[i],val);
        return false;
    }
};

int main() {
    Tree tree;
//    tree.insert(10);
//    tree.insert(5);
//    tree.insert(15);
//    tree.insert(3);
//    tree.insert(7);
//    tree.insert(12);
//    tree.insert(20);
//    for(int i=3;i<100;i+=7)
//        tree.insert(i);
     int n,k;
     cout<<"n=";
     cin>>n;
     cout<<"elem:";
     for(int i=0;i<n;i++)
     {
        cin>>k;
        tree.insert(k);
     }
    tree.afis();
    return 0;
}
