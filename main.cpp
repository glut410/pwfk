#include<bits/stdc++.h>
#include<crypt.h>
using namespace std;

int getAsc(char& c) {
    return int(c);
}

char getChar(int c) {
    return char(c);
}

int flag = 0;
char *lastPos = NULL;
class Passwdc {
    private:
        int min, max, size = 0;
        void setSize(int s) {
            size = s;
            // cout<<size<<endl;
        }

        inline void addfunc(char *&pw) {
            
            switch (pw[max - 1]) {
                case '9':
                    pw[max - 1] = 'a';
                    break;
                
                case 'z':
                    pw[max - 1] = 'A';
                    break;
                
                case 'Z':
                    for(int i = max - 1; i >= max - size; i--) {
                        if(pw[i] != 'Z') {
                            switch (pw[i]) {
                                case '9':
                                    pw[i] = 'a';
                                    break;
                
                                case 'z':
                                    pw[i] = 'A';
                                    break;
                
                                default:
                                    pw[i] = getChar(getAsc(pw[i]) + 1);
                                    break;
                            }
                            break;
                        }
                        pw[i] = '0';
                        if(i == max - size) flag = 1;
                    }
                    setSize(size + flag);
                    flag = 0;
                    break;
                
                default:
                    pw[max - 1] = getChar(getAsc(pw[max - 1]) + 1);
                    break;
            }
        }

    public:
        char *psw;
        char *repw;
        Passwdc(int n, int x, char *lastPos) {
            min = n;
            max = x;
            psw = new char[max - 1];
            
            setSize(min);

            repw = new char[max - 1];
            for(int i = max - 1; i >= 0; i--) {
                if(lastPos == NULL) psw[i] = '0';//init
                if(max - i - 1 < size) repw[max - i - 1] = '0';
            }

            if(lastPos != NULL) psw = lastPos;
        }

        Passwdc(char *&npw) {
            psw = npw;
        }

        Passwdc operator++(int) {
            char *pw = psw;
            addfunc(pw);
            for(int i = 0; i < size; i++) repw[i] = pw[max - size + i];
            return Passwdc(pw);
        }
};

void readfile() {
    ifstream data;
    try {
        data.open("/root/data.txt", ios::in);
        data >> lastPos;
        data.close();
    }
    catch(const exception& e) {
        cerr << e.what() << '\n';
    }
}

void savefile() {

}
int main() {
    const string salt = "$6$rKGsWW.B", opasswd = "$6$rKGsWW.B$VCwGJpGfjl8AJtululckb8qP/.KCl6IhCm.Pk4XW9fSR8uNd9bCk/zTK9wPV4szpPsBTF3rWaV2YDQ6.TdSHn1";
    
    readfile();
    Passwdc pw(3, 7, lastPos);
    while(crypt(pw.repw, salt.c_str()) != opasswd) {
        // cout<<pw.repw<<endl;
        pw++;
    }
    cout<<pw.repw<<endl;
    return 0;
}
