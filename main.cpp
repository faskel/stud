#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class CheckFile {
public:
    char mas[100];
    intmax_t CheckSum;
    int size;
    int siz;
    CheckFile *next;

public:
    CheckFile(char *name) {

        size = 0;
        strcpy(mas, name);
        CalcLen();
        SumHash();

    }

    void show() {

        cout << mas << " " << size << endl;


    }

    void CalcLen() {
        char mad[10];
        int fd;
        fd = open(mas, O_RDONLY);
        if (fd < 0) {
            cout << "bad file" << endl;
            size = 0;
            return;
        } else {

            int rez;
            while (rez = read(fd, mad, 1)) {
                if (rez <= 0) {
                    return;
                } else {
                    size++;

                }

            }
            close(fd);
        }

    }


    int SumHash() {
        int sum = 0;
        CheckFile *p = this;
        while (p != NULL) {

            sum += p->size;
            p = p->next;
        }
        return sum;
    }

};

class FooDir {
    CheckFile *head;

public:
    int Sum(){
        return head->SumHash();

    }
    FooDir() {
        head = NULL;
    }

    void push(CheckFile *p) {
        if (head == NULL)
            head = p;
        else {
            CheckFile *t = head;
            head = p;
            p->next = t;

        }
    }

    void show() {
        CheckFile *p;
        p = head;
        if (head == NULL)
            cout << "empty list" << endl;
        while (p != NULL) {
            p->show();
            p = p->next;
        }


    };

};


int main() {

    FooDir q;
    q.show();


    DIR *dfd;
    struct dirent *dp;
    dfd = opendir(".");
    while ((dp = readdir(dfd)) != NULL) {
        //cout << dp -> d_name << endl;
        CheckFile *w;
        w = new CheckFile(dp->d_name);
        q.push(w);


    }
    q.show();
    cout<<q.Sum();

    // cout << "bye bye" << endl;
    closedir(dfd);


}