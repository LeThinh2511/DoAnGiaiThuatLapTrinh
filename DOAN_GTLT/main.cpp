#include <iostream>
#include <iomanip>
#include <fstream>
#include "Node.h"
#include "ListCanh.h"
using namespace std;
#define max 10000


void excute(Node&);
int rutGon(Node&);
Canh timCanhPhanNhanh(Node&);
void phanNhanh(Node&);
void doLeft(Node&);
void doRight(Node&);
void timHaiCanhCuoi(Node&, ListCanh&);
void ghiKetQua(ListCanh&);
int timCanhLonNhat(Matrix&);
int sum = max;

int main() {
    ifstream file;
    file.open("maTranTrongSo.txt");
    if (!file.is_open())
    {
        cout << "Khong mo duoc file de doc!" << endl;
        return 0;
    }
    else
    {
        Node root;
        int phanBu;
        initNode(root);
        Matrix maTranTrongSoBanDau;
        file >> root.matrix.n;
        maTranTrongSoBanDau.n = root.matrix.n;
        createMatrix(maTranTrongSoBanDau);
        createMatrix(root.matrix);
        
        // Nhap du lieu tu file vao ma tran
        for (int i = 0; i < root.matrix.n; i++)
        {
            for (int j = 0; j < root.matrix.n; j++)
            {
                file >> maTranTrongSoBanDau.m[i][j];
            }
        }
        cout << "Ma tran nhap vao:\n";
        printMatrix(maTranTrongSoBanDau);
        
        // Tao ma tran bu
        phanBu = timCanhLonNhat(maTranTrongSoBanDau);
        for (int i = 0; i < maTranTrongSoBanDau.n; i++)
        {
            for (int j = 0; j < maTranTrongSoBanDau.n; j++)
            {
                if (maTranTrongSoBanDau.m[i][j] == max)
                {
                    root.matrix.m[i][j] = maTranTrongSoBanDau.m[i][j];
                }
                else
                {
                    root.matrix.m[i][j] = phanBu - maTranTrongSoBanDau.m[i][j];
                }
            }
        }
        cout << "Ma tran bu:" << endl;
        printMatrix(root.matrix);
        excute(root); // Goi ham thuc thi
        detroyMatrix(maTranTrongSoBanDau);
        detroyTree(root);
    }
    file.close();
    return 0;
}

/*     ------------Ket thuc ham main----------------      */

// Ham tim canh co trong so lon nhat trong ma tran trong so
int timCanhLonNhat(Matrix& matrix)
{
    int GTLN = 0;
    for (int i = 0; i < matrix.n; i++)
    {
        for (int j = 0; j < matrix.n; j++)
        {
            if (matrix.m[i][j] == max)
            {
                continue;
            }
            else if (matrix.m[i][j] > GTLN)
            {
                GTLN = matrix.m[i][j];
            }
        }
    }
    return GTLN;
}

// Ham thuc thi
void excute(Node& root)
{
    root.p += rutGon(root);
    root.c = timCanhPhanNhanh(root);
    // Tao node left
    Node left;
    initNode(left);
    copyMatrix(left.matrix, root.matrix);
    copyListCanh(left.listCanh, root.listCanh);
    left.p = root.p;
    root.l = &left;
    // Thuc hien nhanh ben trai
    doLeft(root);
    // Neu can duoi cua nhanh phai be hon sum thi thuc hien nhanh phai
    if (root.p + root.c.d < sum)
    {
        Node right;
        initNode(right);
        copyMatrix(right.matrix, root.matrix);
        copyListCanh(right.listCanh, root.listCanh);
        right.p = root.p;
        root.r = &right;
        doRight(root);
    }
}

// Ham thuc thi nhanh trai

void doLeft(Node& root)
{
    root.l->c = root.c; // gan canh phan nhanh sang cho nhanh trai
    phanNhanh(*root.l); // Thuc hien phan nhanh
    cout << "Canh phan nhanh:" << "(" << root.c.r + 1<< "," << root.c.s  + 1 << ")" << endl;
    cout << "Ma tran sau khi phan nhanh:\n";
    printMatrix(root.l->matrix);
    cout << endl;
    addCanh(root.l->listCanh, root.c); // Them canh phan nhanh vao
    // Neu so canh bang so dinh - 2 thi thuc hien tim 2 canh cuoi
    if (root.l->listCanh.count == root.matrix.n - 2)
    {
        // Sap xep danh sach canh truoc khi thuc hien chon 2 canh cuoi
        sortListCanh(root.l->listCanh);
        timHaiCanhCuoi(*root.l, root.l->listCanh);
        if (sum > root.l->p)
        {
            sum = root.l->p;
            ghiKetQua(root.l->listCanh);
        }
        else
        {
            // In ra ket qua cuoi cung
            ifstream file;
            file.open("ketQua.txt");
            if (!file.is_open())
            {
                cout << "Khong mo duoc file de doc!" << endl;
                return;
            }
            cout << "Chu trinh trong nhanh nay khong phai chu trinh can tim!\n" << endl;
            while (!file.eof())
            {
                char temp[255];
                file.getline(temp, 255);
                string line = temp;
                cout << line << endl;
            }
            file.close();
        }
        return;
    }
    excute(*root.l);
}

// Ham thuc thi nhanh phai

void doRight(Node& root)
{
    root.r->matrix.m[root.c.r][root.c.s] = max;// Gan canh bang vo cung
    excute(*root.r);
}

// Ham ghi ket qua vao file
void ghiKetQua(ListCanh& l)
{
    ifstream file2;
    Matrix maTranTrongSoBanDau;
    Canh* cur = l.head;
    int luongMatThuDuoc = 0;
    file2.open("maTranTrongSo.txt");
    if (!file2.is_open())
    {
        cout << "Khong mo duoc file de doc!" << endl;
        return;
    }
    file2 >> maTranTrongSoBanDau.n;
    createMatrix(maTranTrongSoBanDau);
    for (int i = 0; i < maTranTrongSoBanDau.n; i++)
    {
        for (int j = 0; j < maTranTrongSoBanDau.n; j++)
        {
            file2 >> maTranTrongSoBanDau.m[i][j];
        }
    }
    // Tinh tong trong so tu ma tran ban dau
    while (cur != NULL)
    {
        luongMatThuDuoc += maTranTrongSoBanDau.m[cur->r][cur->s];
        cur = cur->next;
    }
    // Ghi ket qua vao file
    ofstream file;
    file.open("ketQua.txt");
    
    if (!file.is_open())
    {
        cout << "Khong mo duoc file de ghi ket qua!" << endl;
        return;
    }
    file << "Duong di thu duoc luong mat lon nhat la: \n";
    cout << "Duong di thu duoc luong mat lon nhat la: \n";
    cur = l.head;
    file << cur->r + 1 << "->" << cur->s + 1;
    cout << cur->r + 1 << "->" << cur->s + 1;
    int temp = cur->s;
    int temp2 = cur->r;
    do
    {
        while (cur->r != temp) {
            cur = cur->next;
        }
        temp = cur->s;
        file << "->" << temp + 1;
        cout << "->" << temp + 1;
        cur = l.head;
    }
    while (temp != temp2);
    file << "\nLuong mat thu duoc:\n";
    cout << "\nLuong mat thu duoc:\n";
    cout << luongMatThuDuoc << endl;
    file << luongMatThuDuoc;
    detroyMatrix(maTranTrongSoBanDau);
    file2.close();
    file.close();
}

//Ham phan nhanh(Gan hang vao cot tu canh phan nhanh bang vo cung)

void phanNhanh(Node& root)
{
    root.matrix.m[root.c.s][root.c.r] = max;
    for (int i = 0; i < root.matrix.n; i++)
    {
        root.matrix.m[i][root.c.s] = max;
    }
    for (int j = 0; j < root.matrix.n; j++)
    {
        root.matrix.m[root.c.r][j] = max;
    }
}

// Ham rut gon ma tran
int rutGon(Node& root)
{
    int s = 0;
    int min = max;
    
    //Rut gon tren dong
    
    for (int i = 0; i < root.matrix.n; i++)
    {
        for (int j = 0; j < root.matrix.n; j++)
        {
            if (min > root.matrix.m[i][j])
            {
                min = root.matrix.m[i][j];
            }
        }
        if (min == 0)
        {
            min = max;
            continue;
        }
        else if (min != max)
        {
            s += min;
            for (int j = 0; j < root.matrix.n; j++)
            {
                if (root.matrix.m[i][j] == max)
                {
                    continue;
                }
                root.matrix.m[i][j] -= min;
            }
            min = max;
        }
    }
    
    //Rut gon tren cot
    for (int j = 0; j < root.matrix.n; j++)
    {
        for (int i = 0; i < root.matrix.n; i++)
        {
            if (min > root.matrix.m[i][j])
            {
                min = root.matrix.m[i][j];
            }
        }
        
        if (min == 0)
        {
            min = max;
            continue;
        }
        else if (min != max)
        {
            s += min;
            for (int i = 0; i < root.matrix.n; i++)
            {
                if (root.matrix.m[i][j] == max)
                {
                    continue;
                }
                root.matrix.m[i][j] -= min;
            }
            min = max;
        }
    }
    return s;
}

// Ham tim canh phan nhanh

Canh timCanhPhanNhanh(Node& root)
{
    Canh canhPhanNhanh;
    int anpha = -1;
    int minr = max;
    int mins = max;
    for (int i = 0; i < root.matrix.n; i++)
    {
        for (int j = 0; j < root.matrix.n; j++)
        {
            if (root.matrix.m[i][j] != 0)
            {
                continue;
            }
            else
            {
                //tin r be nhat tren hang i
                for (int h = 0; h < root.matrix.n; h++)
                {
                    if (h == j)
                    {
                        continue; //bo qua hang i cot j
                    }
                    else
                    {
                        if (minr > root.matrix.m[i][h])
                        {
                            minr = root.matrix.m[i][h];
                        }
                    }
                }
                //tim s be nhat tren cot j
                for (int h = 0; h < root.matrix.n; h++)
                {
                    if (h == i)
                    {
                        continue; //bo qua hang i cot j
                    }
                    else
                    {
                        if (mins > root.matrix.m[h][j])
                        {
                            mins = root.matrix.m[h][j];
                        }
                    }
                }
            }
            //Tim anpha lon nhat va luu lai canh phan nhanh
            if (anpha < (mins + minr))
            {
                anpha = (mins + minr);
                canhPhanNhanh.d = anpha;
                canhPhanNhanh.r = i;
                canhPhanNhanh.s = j;
            }
            mins = minr = max;
        }
    }
    return canhPhanNhanh;
}

// Ham tim hai canh cuoi, them hai canh cuoi vao danh sach canh
void timHaiCanhCuoi(Node& root, ListCanh& l)
{
    //Tim 2 canh con lai c1, c2.
    Canh c1, c2;
    Canh* cur = l.head;
    int temp1 = 0;
    int temp2 = cur->r;
    while (cur->next != NULL)
    {
        if (cur->s != cur->next->r)
        {
            break;
        }
        cur = cur->next;
    }
    c1.r = cur->s;
    if (cur->next == NULL)
    {
        c2.s = temp2;
        int sum = 0;
        for (int i = 0; i < root.matrix.n; i++)
        {
            sum += i;
        }
        sum -= c2.s;
        cur = l.head;
        while (cur != NULL)
        {
            sum -= cur->s;
            cur = cur->next;
        }
        c1.s = c2.r = sum;
    }
    else
    {
        temp1 = cur->next->r;
        cur = cur->next;
        while (cur->next != NULL)
        {
            if (cur->s != cur->next->r)
            {
                break;
            }
            cur = cur->next;
        }
        if (cur->next != NULL)
        {
            c2.r = cur->s;
            c2.s = cur->next->r;
            c1.s = temp1;
        }
        else if (temp2 != cur->s)
        {
            c1.s = temp1;
            c2.r = cur->s;
            c2.s = temp2;
        }
        else
        {
            c2.s = temp1;
            int sum = 0;
            for (int i = 0; i < root.matrix.n; i++)
            {
                sum += i;
            }
            sum -= c2.s;
            cur = l.head;
            while (cur->next != NULL)
            {
                sum -= cur->s;
                cur = cur->next;
            }
            c1.s = c2.r = sum;
        }
    }
    //Them hai canh tim duoc vao danh sach canh
    addCanh(l, c1);
    addCanh(l, c2);
    //cong trong so o 2 canh vao can duoi
    root.p += root.matrix.m[c1.r][c1.s];
    root.p += root.matrix.m[c2.r][c2.s];
}
