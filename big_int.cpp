#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#define BASE 1000000000 //base size is 10^9
using namespace std;

class BigInt{
    private:
    vector<int> blocks;
    bool negative;

    public:
    BigInt();
    BigInt(string s);
    void display_BigInt() const;
    BigInt addMagnitude(const BigInt&) const;
    BigInt add(const BigInt&) const;
    BigInt subtractMagnitude(const BigInt&) const;
    BigInt subtract(const BigInt&)const;
    BigInt multiplyMagnitude(const BigInt&)const;
    BigInt multiply(const BigInt&)const;
    int comparison(const BigInt&) const;
};


BigInt::BigInt(){
    negative=false;
}

BigInt::BigInt(string s){
    negative=false;
    if(s[0]=='-'){
        negative=true;
        s=s.substr(1);
    }
    
    int i=s.size();

    string sub;
    int block;

    while(i>9){
        
        i=i-9;
        block=0;
        sub=s.substr(i,9);

        for(int j=0; j<sub.size(); j++){
            int d=sub[j]-'0';
            block=block*10 + d;
        }
        blocks.push_back(block);
    }
    sub=s.substr(0,i);
    block=0;
    for(int j=0; j<sub.size(); j++){
            int d=sub[j]-'0';
            block=block*10 + d;
        }
    blocks.push_back(block);
}

int BigInt::comparison(const BigInt& b) const{
    int i,j;
    i=blocks.size();
    j=b.blocks.size();
    if(i>j){
        return 1;
    }
    else if(i<j){
        return -1;
    }
    else{
        int x=i-1;
        while(x>=0 && blocks[x]==b.blocks[x])
        {
            x--;
        }
        if(x==-1) return 0;
        else if(blocks[x]>b.blocks[x]) return 1;
        else return -1;
    }
}


void BigInt::display_BigInt() const{
    if(negative) cout<<"-";
    int n=blocks.size();
    cout<<blocks[n-1];
    for(int i=n-2; i>=0; i--){
        int digits=0;
        int temp=blocks[i];
        if(temp==0){
            digits=1;
        }
        else{
            while(temp!=0){
                temp=temp/10;
                digits++;
            }
        }
        for(int j=0; j<9-digits; j++){
            cout<<"0";
        }
        cout<<blocks[i];
    }
}


BigInt BigInt::addMagnitude(const BigInt& b) const{
    BigInt result;

    long long sum, carry = 0;
    int n = blocks.size();
    int m = b.blocks.size();

    for(int i = 0; i < n || i < m; i++){
        sum = carry;
        if(i < n) sum += blocks[i];
        if(i < m) sum += b.blocks[i];

        carry = sum / BASE;
        sum %= BASE;

        result.blocks.push_back(sum);
    }

    if(carry){
        result.blocks.push_back(carry);
    }

    return result;
}


BigInt BigInt::add(const BigInt& b) const{

    if(negative == b.negative){
        BigInt result = addMagnitude(b);
        result.negative = negative;
        return result;
    }

    int cmp = comparison(b);

    if(cmp == 0){
        return BigInt("0");
    }
    else if(cmp > 0){
        BigInt result = subtractMagnitude(b);
        result.negative = negative;
        return result;
    }
    else{
        BigInt result = b.subtractMagnitude(*this);
        result.negative = b.negative;
        return result;
    }
}



BigInt BigInt::subtract(const BigInt& b) const{
    BigInt temp = b;
    temp.negative = !b.negative;
    return add(temp);
}

BigInt BigInt::subtractMagnitude(const BigInt& b) const{
    BigInt result;

    long long diff, borrow = 0;
    int n = blocks.size();
    int m = b.blocks.size();

    for(int i = 0; i < n; i++){
        diff = blocks[i] - borrow;
        if(i < m) diff -= b.blocks[i];

        if(diff < 0){
            diff += BASE;
            borrow = 1;
        }
        else{
            borrow = 0;
        }

        result.blocks.push_back((int)diff);
    }

    while(result.blocks.size() > 1 && result.blocks.back() == 0){
        result.blocks.pop_back();
    }

    return result;
}

BigInt BigInt::multiplyMagnitude(const BigInt& b) const{
    BigInt result;
    result.blocks.clear();

    int n = blocks.size();
    int m = b.blocks.size();

    result.blocks.resize(n + m, 0);

    for(int i = 0; i < n; i++){
        long long carry = 0;

        for(int j = 0; j < m; j++){
            long long cur =result.blocks[i+j] +(long long)blocks[i] * b.blocks[j] +carry;
            result.blocks[i+j] = cur % BASE;
            carry = cur / BASE;
        }

        result.blocks[i+m] += carry;
    }

    while(result.blocks.size() > 1 && result.blocks.back() == 0){
        result.blocks.pop_back();
    }

    return result;
}

BigInt BigInt::multiply(const BigInt& b) const{
    BigInt result = multiplyMagnitude(b);

    if((negative && !b.negative) ||
       (!negative && b.negative)){
        result.negative = true;
    }
    else{
        result.negative = false;
    }

    if(result.blocks.size() == 1 &&
       result.blocks[0] == 0){
        result.negative = false;
    }

    return result;
}



int main(){
    cout << "1. Add" << endl << "2. Subtract" <<endl<< "3. Multiply"<< endl;
    cout << "Enter your option : ";
    int opt;
    cin >> opt;

    string m,n;
    cout<<"Enter 1st operand : ";
    cin>>m;
    BigInt a(m);

    cout<<"Enter 2nd operand : ";
    cin>>n;
    BigInt b(n);

    if(opt == 1){
        BigInt result = a.add(b);
        result.display_BigInt();
        cout << endl;
    }
    else if(opt == 2){
        BigInt result = a.subtract(b);
        result.display_BigInt();
        cout<<endl;
    }
    else if(opt==3){
        BigInt result = a.multiply(b);
        result.display_BigInt();
        cout<<endl;
    }

    return 0;
}
