#include "Atoms.hpp"
//Verified that all constructors and the assignment operator work on 5/29/18.

// default constructor
Atoms::Atoms():r(0),v(0),f(0){}

// simple constructor
Atoms::Atoms(const int&n,const int&d):n(n),d(d),r(new double* [n]),v(new double* [n]),f(new double* [n]){
    r[0] = new double[n*d];
    v[0] = new double[n*d];
    f[0] = new double[n*d];
    for (int i=1; i<n; i++) {
        r[i] = r[i-1] + d;
        v[i] = v[i-1] + d;
        f[i] = f[i-1] + d;
    }
}

// copy constructor
Atoms::Atoms(const Atoms &rhs) {
    n = rhs.n;
    d = rhs.d;
    int i,k;
    r = new double *[n];
    r[0] = new double [n*d];
    v = new double *[n];
    v[0] = new double [n*d];
    f = new double *[n];
    f[0] = new double [n*d];
    for(i=1; i<n; i++) {
        r[i] = r[i-1]+d;
        v[i] = v[i-1]+d;
        f[i] = f[i-1]+d;
    }
    for(i=0; i<n; i++)
        for(k=0; k<d; k++) {
            r[i][k] = rhs.r[i][k];
            v[i][k] = rhs.v[i][k];
            f[i][k] = rhs.f[i][k];
        }
}

// assignment operator
Atoms & Atoms::operator = (const Atoms &rhs) {
    int i,k;
    if (this != &rhs) {
        if (r!=0) {
            delete [] r[0];
            delete [] r;
        }
        if (v!=0) {
            delete [] v[0];
            delete [] v;
        }
        if (f!=0) {
            delete [] f[0];
            delete [] f;
        }
        n = rhs.n;
        d = rhs.d;
        r = new double *[n];
        r[0] = new double [n*d];
        v = new double *[n];
        v[0] = new double [n*d];
        f = new double *[n];
        f[0] = new double [n*d];
        for(i=1; i<n; i++) {
            r[i] = r[i-1]+d;
            v[i] = v[i-1]+d;
            f[i] = f[i-1]+d;
        }
        for(i=0; i<n; i++)
            for(k=0; k<d; k++) {
                r[i][k] = rhs.r[i][k];
                v[i][k] = rhs.v[i][k];
                f[i][k] = rhs.f[i][k];
            }
    }
    return *this;
}

// destruction operator
Atoms::~Atoms(){
    if(r != 0) {
        delete [] r[0];
        delete [] r;
    }
    if(v != 0) {
        delete [] v[0];
        delete [] v;
    }
    if(f != 0) {
        delete [] f[0];
        delete [] f;
    }
}

ostream & operator << (ostream &os, const Atoms& rhs){
    for(int i=0;i<rhs.n;i++)
        for(int k=0;k<rhs.d;k++){
            os << rhs.r[i][k] << "\t" << rhs.v[i][k] << "\t" << rhs.f[i][k] << endl;
        }
    return os;
}

